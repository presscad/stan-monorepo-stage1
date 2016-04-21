#ifndef STAN_MCMC_HMC_HAMILTONIANS_SOFTABS_METRIC_HPP
#define STAN_MCMC_HMC_HAMILTONIANS_SOFTABS_METRIC_HPP

#include <stan/math/mix/mat.hpp>

// #include <Eigen/Cholesky>
// #include <stan/math/prim/mat/fun/Eigen.hpp>
// #include <stan/math/prim/mat/meta/index_type.hpp>

#include <stan/mcmc/hmc/hamiltonians/base_hamiltonian.hpp>
#include <stan/mcmc/hmc/hamiltonians/softabs_point.hpp>

#include <boost/random/variate_generator.hpp>
#include <boost/random/normal_distribution.hpp>

namespace stan {
  namespace mcmc {

    template <typename Model>
    struct softabs_fun {
      const Model& model_;
      std::ostream* o_;

      softabs_fun(const Model& m, std::ostream* out): model_(m), o_(out) {}

      template <typename T>
      T operator()(Eigen::Matrix<T, Eigen::Dynamic, 1>& x) const {
        return model_.template log_prob<true, true, T>(x, o_);
      }
    };

    // Riemannian manifold with SoftAbs metric
    template <class Model, class BaseRNG>
    class softabs_metric
      : public base_hamiltonian<Model, softabs_point, BaseRNG> {
    private:
      typedef typename stan::math::index_type<Eigen::VectorXd>::type idx_t;
    public:
      explicit softabs_metric(const Model& model)
        : base_hamiltonian<Model, softabs_point, BaseRNG>(model) {}

      ~softabs_metric() {}

      double T(softabs_point& z) {
        return this->tau(z) + 0.5 * z.log_det_metric;
      }

      double tau(softabs_point& z) {
        Eigen::VectorXd Qp = z.eigen_deco.eigenvectors().transpose() * z.p;
        return 0.5 * Qp.transpose() * z.softabs_lambda_inv.cwiseProduct(Qp);
      }

      double phi(softabs_point& z) {
        return this->V(z) + 0.5 * z.log_det_metric;
      }

      double dG_dt(softabs_point& z,
                   interface_callbacks::writer::base_writer& writer) {
        return 2 * T(z) - z.q.dot(dtau_dq(z, writer) + dphi_dq(z, writer));
      }

      const Eigen::VectorXd dtau_dq(
        softabs_point& z, interface_callbacks::writer::base_writer& writer) {
        Eigen::VectorXd a =    z.softabs_lambda_inv.cwiseProduct(
                               z.eigen_deco.eigenvectors().transpose() * z.p);
        Eigen::MatrixXd A =   a.asDiagonal()
                            * z.eigen_deco.eigenvectors().transpose();
        Eigen::MatrixXd B = z.pseudo_j.selfadjointView<Eigen::Lower>() * A;
        Eigen::MatrixXd C = A.transpose() * B;

         Eigen::VectorXd b(z.q.size());
         stan::math::grad_tr_mat_times_hessian(
           softabs_fun<Model>(this->model_, 0), z.q, C, b);

         return 0.5 * b;
      }

      const Eigen::VectorXd dtau_dp(softabs_point& z) {
        return   z.eigen_deco.eigenvectors()
               * z.softabs_lambda_inv.cwiseProduct(
                   z.eigen_deco.eigenvectors().transpose() * z.p);
      }

      const Eigen::VectorXd dphi_dq(softabs_point& z,
        interface_callbacks::writer::base_writer& writer) {
          Eigen::VectorXd a
            = z.softabs_lambda_inv.cwiseProduct(z.pseudo_j.diagonal());
          Eigen::MatrixXd A =  a.asDiagonal()
                             * z.eigen_deco.eigenvectors().transpose();
          Eigen::MatrixXd B = z.eigen_deco.eigenvectors() * A;

          stan::math::grad_tr_mat_times_hessian(
            softabs_fun<Model>(this->model_, 0), z.q, B, a);

          return - 0.5 * a + z.g;
      }

      void sample_p(softabs_point& z, BaseRNG& rng) {
        boost::variate_generator<BaseRNG&, boost::normal_distribution<> >
          rand_unit_gaus(rng, boost::normal_distribution<>());

        Eigen::VectorXd a(z.p.size());

        for (idx_t n = 0; n < z.p.size(); ++n)
          a(n) = sqrt(z.softabs_lambda(n)) * rand_unit_gaus();

        z.p = z.eigen_deco.eigenvectors() * a;
      }

      void init(softabs_point& z,
                interface_callbacks::writer::base_writer& writer) {
        update_metric(z, writer);
        update_metric_gradient(z, writer);
      }

      void update_metric(softabs_point& z,
                         interface_callbacks::writer::base_writer& writer) {
        // Compute the Hessian
        stan::math::hessian<double>(
          softabs_fun<Model>(this->model_, 0), z.q, z.V, z.g, z.hessian);

        z.V *= -1;
        z.g *= -1;
        z.hessian *= -1;

        // Compute the eigen decomposition of the Hessian,
        // then perform the SoftAbs transformation
        z.eigen_deco.compute(z.hessian);

        for (idx_t i = 0; i < z.q.size(); ++i) {
          double lambda = z.eigen_deco.eigenvalues()(i);
          double alpha_lambda = z.alpha * lambda;

          double softabs_lambda = 0;

          // Thresholds defined such that the approximation
          // error is on the same order of double precision
          if (std::fabs(alpha_lambda) < 1e-4) {
           softabs_lambda = (1.0
                             + (1.0 / 3.0) * alpha_lambda * alpha_lambda)
                             / z.alpha;
          } else if (std::fabs(alpha_lambda) > 18) {
           softabs_lambda = std::fabs(lambda);
          } else {
           softabs_lambda = lambda / std::tanh(alpha_lambda);
          }

          z.softabs_lambda(i) = softabs_lambda;
          z.softabs_lambda_inv(i) = 1.0 / softabs_lambda;
        }

        // Compute the log determinant of the metric
        z.log_det_metric = 0;
        for (idx_t i = 0; i < z.q.size(); ++i)
         z.log_det_metric += std::log(z.softabs_lambda(i));
      }

      void update_metric_gradient(
        softabs_point& z, interface_callbacks::writer::base_writer& writer) {
        // Compute the pseudo-Jacobian of the SoftAbs transform
        for (idx_t i = 0; i < z.q.size(); ++i) {
          for (idx_t j = 0; j <= i; ++j) {
            double delta =   z.eigen_deco.eigenvalues()(i)
                           - z.eigen_deco.eigenvalues()(j);

            if (std::fabs(delta) < 1e-10) {
              double lambda = z.eigen_deco.eigenvalues()(i);
              double alpha_lambda = z.alpha * lambda;

              // Thresholds defined such that the approximation
              // error is on the same order of double precision
              if (std::fabs(alpha_lambda) < 1e-4) {
                z.pseudo_j(i, j) =   (2.0 / 3.0) * alpha_lambda
                                   * (1.0 -   (2.0 / 15.0)
                                            * alpha_lambda * alpha_lambda);
              } else if (std::fabs(alpha_lambda) > 18) {
                z.pseudo_j(i, j) = lambda > 0 ? 1 : -1;
              } else {
                double sdx = std::sinh(alpha_lambda) / lambda;
                z.pseudo_j(i, j) = (z.softabs_lambda(i)
                                    - z.alpha / (sdx * sdx) ) / lambda;
              }
            } else {
              z.pseudo_j(i, j) = (z.softabs_lambda(i)
                                  - z.softabs_lambda(j) ) / delta;
            }
          }
        }
      }

      void update_gradients(
        softabs_point& z, interface_callbacks::writer::base_writer& writer) {
        update_metric_gradient(z, writer);
      }
    };
  }  // mcmc
}  // stan
#endif
