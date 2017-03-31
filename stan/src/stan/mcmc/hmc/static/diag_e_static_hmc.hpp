#ifndef STAN_MCMC_HMC_STATIC_DIAG_E_STATIC_HMC_HPP
#define STAN_MCMC_HMC_STATIC_DIAG_E_STATIC_HMC_HPP

#include <stan/mcmc/hmc/hamiltonians/diag_e_point.hpp>
#include <stan/mcmc/hmc/hamiltonians/diag_e_metric.hpp>
#include <stan/mcmc/hmc/integrators/expl_leapfrog.hpp>
#include <stan/mcmc/hmc/static/base_static_hmc.hpp>

namespace stan {
  namespace mcmc {
    /**
     * Hamiltonian Monte Carlo implementation using the endpoint
     * of trajectories with a static integration time with a
     * Gaussian-Euclidean disintegration and diagonal metric
     */
    template <class Model, class BaseRNG>
    class diag_e_static_hmc
      : public base_static_hmc<Model, diag_e_metric,
                               expl_leapfrog, BaseRNG> {
    public:
      diag_e_static_hmc(const Model& model, BaseRNG& rng)
        : base_static_hmc<Model, diag_e_metric,
                          expl_leapfrog, BaseRNG>(model, rng) { }

      /** 
       * specialized constructor for specified diag mass matrix
       */
      diag_e_static_hmc(const Model& model, BaseRNG& rng,
                        Eigen::VectorXd& inv_mass_matrix)
        : base_static_hmc<Model, diag_e_metric,
                          expl_leapfrog, BaseRNG>(model, rng,
                                                  inv_mass_matrix) { }
    };

  }  // mcmc
}  // stan
#endif
