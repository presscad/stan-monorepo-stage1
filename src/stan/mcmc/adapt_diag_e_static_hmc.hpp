#ifndef __STAN__MCMC__ADAPT__DIAG__E__STATIC__HMC__BETA__
#define __STAN__MCMC__ADAPT__DIAG__E__STATIC__HMC__BETA__

#include <stan/mcmc/var_adapter.hpp>
#include <stan/mcmc/diag_e_static_hmc.hpp>

namespace stan {
  
  namespace mcmc {
    
    // Hamiltonian Monte Carlo on a 
    // Euclidean manifold with diagonal metric,
    // static integration time,
    // and adaptive stepsize
    
    template <typename M, class BaseRNG>
    class adapt_diag_e_static_hmc: public diag_e_static_hmc<M, BaseRNG>, public var_adapter {
      
    public:
      
      adapt_diag_e_static_hmc(M &m, BaseRNG& rng): diag_e_static_hmc<M, BaseRNG>(m, rng),
                                                   stepsize_adapter()
      {};
      
      ~adapt_diag_e_static_hmc() {};
      
      sample transition(sample& init_sample) {
        
        sample s = diag_e_static_hmc<M, BaseRNG>::transition(init_sample);
        
        if (this->_adapt_flag) {
          
          this->_learn_stepsize(this->_epsilon, s.accept_stat());
          this->_update_L();
          
          this->_learn_var(this->_z.mInv, this->_z.q);
          
        }
        
        return s;
        
      }
      
    };
    
  } // mcmc
  
} // stan


#endif
