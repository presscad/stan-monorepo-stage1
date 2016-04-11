#ifndef STAN_MCMC_HMC_xhmc_ADAPT_UNIT_E_XHMC_HPP
#define STAN_MCMC_HMC_xhmc_ADAPT_UNIT_E_XHMC_HPP

#include <stan/interface_callbacks/writer/base_writer.hpp>
#include <stan/mcmc/hmc/xhmc/unit_e_xhmc.hpp>
#include <stan/mcmc/stepsize_adapter.hpp>

namespace stan {
  namespace mcmc {
    /**
      * The No-U-Turn sampler (XHMC) with multinomial sampling
      * with a Gaussian-Euclidean disintegration and unit metric
      * and adaptive step size
    */
    template <class Model, class BaseRNG>
    class adapt_unit_e_xhmc: public unit_e_xhmc<Model, BaseRNG>,
                             public stepsize_adapter {
    public:
      adapt_unit_e_xhmc(Model &model, BaseRNG& rng)
        : unit_e_xhmc<Model, BaseRNG>(model, rng) {}

      ~adapt_unit_e_xhmc() {}

      sample transition(sample& init_sample,
                        interface_callbacks::writer::base_writer& writer) {
        sample s = unit_e_xhmc<Model, BaseRNG>::transition(init_sample, writer);

        if (this->adapt_flag_)
          this->stepsize_adaptation_.learn_stepsize(this->nom_epsilon_,
                                                    s.accept_stat());

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
