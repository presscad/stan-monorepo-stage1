#ifndef STAN_MATH_REV_MAT_FUNCTOR_ALGEBRA_SOLVER_HPP
#define STAN_MATH_REV_MAT_FUNCTOR_ALGEBRA_SOLVER_HPP

#include <stan/math/prim/mat/fun/Eigen.hpp>
#include <stan/math/prim/mat/fun/dogleg.hpp>
#include <stan/math/rev/mat/functor/jacobian.hpp>
#include <stan/math/rev/core.hpp>
#include <stan/math/prim/mat/fun/mdivide_left.hpp>
#include <stan/math/prim/scal/err/check_finite.hpp>
#include <stan/math/prim/scal/err/check_consistent_size.hpp>
#include <stan/math/prim/arr/err/check_nonzero_size.hpp>
#include <unsupported/Eigen/NonLinearOptimization>
#include <iostream>

namespace stan {
  namespace math {

    /**
     * A functor that allows us to treat either x or y as
     * the independent variable. This allows us to
     * call Jacobian() on a function with more than one
     * argument and choose with respect to which variable
     * it gets computed.
     */
    template <typename F, typename T0, typename T1>
    struct system_functor {
    private:
      F f_;
      Eigen::Matrix<T0, Eigen::Dynamic, 1> x_;
      Eigen::Matrix<T1, Eigen::Dynamic, 1> y_;
      std::vector<double> dat_;
      std::vector<int> dat_int_;
      bool x_is_dv_;

    public:
      system_functor() { };

      system_functor(const F f,
                     const Eigen::Matrix<T0, Eigen::Dynamic, 1>& x,
                     const Eigen::Matrix<T1, Eigen::Dynamic, 1>& y,
                     const std::vector<double>& dat,
                     const std::vector<int>& dat_int,
                     const bool& x_is_dv)
        : f_() {
        x_ = x;
        y_ = y;
        dat_ = dat;
        dat_int_ = dat_int;
        x_is_dv_ = x_is_dv;
      }

      template <typename T>
      inline
      Eigen::Matrix<T, Eigen::Dynamic, 1>
      operator()(const Eigen::Matrix<T, Eigen::Dynamic, 1> x) const {
        if (x_is_dv_)
          return f_(x, y_, dat_, dat_int_, 0);
        else
          return f_(x_, x, dat_, dat_int_, 0);
      }
    };

    /**
     * This functor has the structure required to call Eigen's solver.
     */
    template <typename FS, typename F, typename T0, typename T1>
    struct hybrj_functor_solver : stan::math::NLOFunctor<double> {
    private:
      FS fs_;
      int x_size_;
      Eigen::MatrixXd J_;

    public:
      hybrj_functor_solver(const FS& fs,
                           const F& f,
                           const Eigen::Matrix<T0, Eigen::Dynamic, 1> x,
                           const Eigen::Matrix<T1, Eigen::Dynamic, 1> y,
                           const std::vector<double> dat,
                           const std::vector<int> dat_int,
                           const bool x_is_dv)
        : fs_(f, x, y, dat, dat_int, x_is_dv),
          x_size_(x.size()) { }

      int operator()(const Eigen::VectorXd &dv, Eigen::VectorXd &fvec) {
        stan::math::jacobian(fs_, dv, fvec, J_);
        return 0;
      }

      int df(const Eigen::VectorXd &dv, Eigen::MatrixXd &fjac) {
        fjac = J_;
        return 0;
      }

      Eigen::MatrixXd get_jacobian(const Eigen::VectorXd &dv) {
        Eigen::VectorXd fvec;
        stan::math::jacobian(fs_, dv, fvec, J_);
        return J_;
      }

      Eigen::VectorXd get_value(const Eigen::VectorXd dv) {
        return fs_(dv);
      }
    };

    /**
     * The vari class for the algebraic solver. We compute the  Jacobian of
     * the solutions with respect to the parameters using the implicit
     * function theorem. The call to Jacobian() occurs outside the call to
     * chain() -- this prevents malloc issues.
     *
     * @member y_ the vector of parameters
     * @member y_size_ the number of parameters
     * @member x_size_ the number of unknowns
     * @member theta_ the vector of solution
     * @member Jx_y_ the Jacobian of the solution with respect to the parameters.
     */
    template <typename FS, typename F, typename T, typename FX>
    struct algebra_solver_vari : public vari {
      vari** y_;
      int y_size_;
      int x_size_;
      vari** theta_;
      Eigen::MatrixXd Jx_y_;

      algebra_solver_vari(const FS& fs,
                          const F& f,
                          const Eigen::VectorXd x,
                          const Eigen::Matrix<T, Eigen::Dynamic, 1> y,
                          const std::vector<double> dat,
                          const std::vector<int> dat_int,
                          const Eigen::VectorXd theta_dbl,
                          FX& fx)
        : vari(theta_dbl(0)),
          y_(ChainableStack::memalloc_.alloc_array<vari*>(y.size())),
          y_size_(y.size()),
          x_size_(x.size()),
          theta_(ChainableStack::memalloc_.alloc_array<vari*>(x.size())) {
        for (int i = 0; i < y.size(); ++i)
          y_[i] = y(i).vi_;

        theta_[0] = this;
        for (int i = 1; i < x.size(); ++i)
          theta_[i] = new vari(theta_dbl(i), false);

        // Compute the Jacobian
        Eigen::MatrixXd Jf_x = fx.get_jacobian(theta_dbl);
        hybrj_functor_solver<FS, F, double, double>
          fy(fs, f, theta_dbl, value_of(y), dat, dat_int, false);
        Eigen::MatrixXd Jf_y = fy.get_jacobian(value_of(y));

        Jx_y_ = - stan::math::mdivide_left(Jf_x, Jf_y);
      }

      void chain() {
        for (int i = 0; i < x_size_; i++)
          for (int j = 0; j < y_size_; j++)
            y_[j]->adj_ += theta_[i]->adj_ * Jx_y_(i, j);
      }
    };

    /**
     * Return the solutions for the specified system of algebraic
     * equations given an initial guess, and  parameters and data,
     * which get passed into the algebraic system. The user can
     * also specify the relative tolerance (xtol in Eigen's code),
     * the absolute tolerance, and the maximum number of steps
     * (maxfev in Eigen's code).
     *
     * Throw an exception if the norm of f(x), where f is the
     * output of the algebraic system and x the proposed solution,
     * is greater than the absolute tolerance. We here use the
     * norm as a metric of how far we are from the 0.
     *
     * @tparam F1 type of equation system function.
     * @tparam T type of scalars for parms.
     * @param[in] F1 Functor that evaluates the system of equations.
     * @param[in] x Vector of starting values.
     * @param[in] y parameter vector for the equation system.
     * @param[in] dat continuous data vector for the equation system.
     * @param[in] dat_int integer data vector for the equation system.
     * @param[in] relative_tolerance determines the convergence criteria for the solution.
     * @param[in] absolute_tolerance determines whether roots are acceptable.
     * @param[in] max_num_steps  maximum number of function evaluations.
     * @return theta Vector of solutions to the system of equations.
     */
    template <typename F, typename T>
    Eigen::Matrix<T, Eigen::Dynamic, 1>
    algebra_solver(const F& f,
                   const Eigen::VectorXd& x,
                   const Eigen::Matrix<T, Eigen::Dynamic, 1>& y,
                   const std::vector<double>& dat,
                   const std::vector<int>& dat_int,
                   double relative_tolerance = 1e-10,
                   double absolute_tolerance = 1e-6,
                   long int max_num_steps = 1e+3) {  // NOLINT(runtime/int)
      // Check that arguments are valid
      check_nonzero_size("algebra_solver", "initial guess", x);
      check_nonzero_size("algebra_solver", "parameter vector", y);
      for (int i = 0; i < x.size(); i++) // FIX ME - do these w/o for loop?
        check_finite("algebra_solver", "initial guess", x(i));
      for (int i = 0; i < y.size(); i++)
        check_finite("algebra_solver", "parameter vector", y(i));
      for (size_t i = 0; i < dat.size(); i++)
        check_finite("algebra_solver", "continuous data", dat[i]);

      if (relative_tolerance <= 0)
        invalid_argument("algebra_solver",
                         "relative_tolerance,", relative_tolerance,
                         "", ", must be greater than 0");
      if (absolute_tolerance <= 0)
        invalid_argument("algebra_solver",
                         "absolute_tolerance,", absolute_tolerance,
                         "", ", must be greater than 0");
      if (max_num_steps <= 0)
        invalid_argument("algebra_solver",
                         "max_num_steps,", max_num_steps,
                         "", ", must be greater than 0");

      // Create functor for algebraic system
      typedef system_functor<F, double, double> FS;
      typedef hybrj_functor_solver<FS, F, double, double> FX;
      FX fx(FS(), f, x, value_of(y), dat, dat_int, true);
      Eigen::HybridNonLinearSolver<FX> solver(fx);

      // Check dimension unknowns equals dimension of system output
      int z_size = fx.get_value(x).size();   // FIX ME: do this w/o computing fx?
      if (z_size != x.size()) {
        std::stringstream msg;
        msg << ", but should have the same dimension as x "
            << "(the vector of unknowns), which is: "
            << x.size();
        std::string msg_str(msg.str());
        invalid_argument("algebra_solver", "the ouput of the algebraic system",
                         z_size, "has dimension = ", msg_str.c_str());
      }

      // Compute theta_dbl
      Eigen::VectorXd theta_dbl = x;
      solver.parameters.xtol = relative_tolerance;
      solver.parameters.maxfev = max_num_steps;
      solver.solve(theta_dbl);

      // Check solution is a root
      Eigen::VectorXd system = fx.get_value(theta_dbl);
      if (system.stableNorm() > absolute_tolerance) {
          std::stringstream msg_index;
          std::stringstream msg_f;
          msg_f << " but should be lower than the absolute tolerance: "
                << absolute_tolerance
                << ". Consider increasing the relative tolerance and the"
                << " max_num_steps.";
          std::string msg_str_f(msg_f.str());

          invalid_argument("algebra_solver",
                           "the norm of the algebraic function is:",
                           system.stableNorm(), "", msg_str_f.c_str());
      }

      // Construct vari
      algebra_solver_vari<FS, F,  T, FX>* vi0
        = new algebra_solver_vari<FS, F, T, FX>(FS(), f, x, y, dat,
                                                dat_int, theta_dbl, fx);
      Eigen::Matrix<T, Eigen::Dynamic, 1> theta(x.size());
      theta(0) = var(vi0);
      for (int i = 1; i < x.size(); ++i)
      theta(i) = var(vi0->theta_[i]);

      return theta;
     }
  }
}

#endif
