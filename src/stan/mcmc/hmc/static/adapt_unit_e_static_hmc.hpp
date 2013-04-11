#ifndef __STAN__MCMC__ADAPT__UNIT__E__STATIC__HMC__BETA__
#define __STAN__MCMC__ADAPT__UNIT__E__STATIC__HMC__BETA__

#include <stan/mcmc/stepsize_adapter.hpp>
#include <stan/mcmc/hmc/static/unit_e_static_hmc.hpp>

namespace stan {
  
  namespace mcmc {
    
    // Hamiltonian Monte Carlo on a 
    // Euclidean manifold with unit metric,
    // static integration time,
    // and adaptive stepsize
    
    template <typename M, class BaseRNG>
    class adapt_unit_e_static_hmc: public unit_e_static_hmc<M, BaseRNG>, public stepsize_adapter {
      
    public:
      
      adapt_unit_e_static_hmc(M &m, BaseRNG& rng): unit_e_static_hmc<M, BaseRNG>(m, rng),
                                                   stepsize_adapter()
      {};
      
      ~adapt_unit_e_static_hmc() {};
      
      sample transition(sample& init_sample) {
        
        sample s = unit_e_static_hmc<M, BaseRNG>::transition(init_sample);
        
        if (this->_adapt_flag) {
          this->learn_stepsize(this->_epsilon, s.accept_stat());
          this->_update_L();
        }
        
        return s;
        
      }
      
    };
    
  } // mcmc
  
} // stan


#endif
