#ifndef STAN_MCMC_HMC_NUTS_ADAPT_DENSE_E_NUTS_HPP
#define STAN_MCMC_HMC_NUTS_ADAPT_DENSE_E_NUTS_HPP

#include <stan/callbacks/writer.hpp>
#include <stan/mcmc/stepsize_covar_adapter.hpp>
#include <stan/mcmc/hmc/nuts/dense_e_nuts.hpp>

namespace stan {
  namespace mcmc {
    /**
     * The No-U-Turn sampler (NUTS) with multinomial sampling
     * with a Gaussian-Euclidean disintegration and adaptive
     * dense metric and adaptive step size
     */
    template <class Model, class BaseRNG>
    class adapt_dense_e_nuts : public dense_e_nuts<Model, BaseRNG>,
                               public stepsize_covar_adapter {
    public:
      adapt_dense_e_nuts(const Model& model, BaseRNG& rng)
        : dense_e_nuts<Model, BaseRNG>(model, rng),
        stepsize_covar_adapter(model.num_params_r()) {}

      /** 
       * specialized constructor for specified dense mass matrix
       */
      adapt_dense_e_nuts(const Model& model, BaseRNG& rng,
                         Eigen::MatrixXd& inv_e_metric)
        : dense_e_nuts<Model, BaseRNG>(model, rng, inv_e_metric),
        stepsize_covar_adapter(model.num_params_r()) {}

      ~adapt_dense_e_nuts() {}

      sample
      transition(sample& init_sample,
                 callbacks::writer& info_writer,
                 callbacks::writer& error_writer) {
        sample s = dense_e_nuts<Model, BaseRNG>::transition(init_sample,
                                                            info_writer,
                                                            error_writer);

        if (this->adapt_flag_) {
          this->stepsize_adaptation_.learn_stepsize(this->nom_epsilon_,
                                                    s.accept_stat());

          bool update = this->covar_adaptation_.learn_covariance(
                                                this->z_.inv_e_metric_,
                                                this->z_.q);

          if (update) {
            this->init_stepsize(info_writer, error_writer);

            this->stepsize_adaptation_.set_mu(log(10 * this->nom_epsilon_));
            this->stepsize_adaptation_.restart();
          }
        }
        return s;
      }

      void disengage_adaptation() {
        base_adapter::disengage_adaptation();
        this->stepsize_adaptation_.complete_adaptation(this->nom_epsilon_);
      }
    };

  }  // mcmc
}  // stan
#endif
