#ifndef __STAN__MCMC__ADAPT__DIAG__E__NUTS__BETA__
#define __STAN__MCMC__ADAPT__DIAG__E__NUTS__BETA__

#include <stan/mcmc/var_adapter.hpp>
#include <stan/mcmc/diag_e_nuts.hpp>

namespace stan {
  
  namespace mcmc {
    
    // The No-U-Turn Sampler (NUTS) on a
    // Euclidean manifold with diagonal metric
    // and adaptive stepsize
    
    template <typename M, class BaseRNG>
    class adapt_diag_e_nuts: public diag_e_nuts<M, BaseRNG>, public var_adapter {
      
    public:
      
      adapt_diag_e_nuts(M &m, BaseRNG& rng): diag_e_nuts<M, BaseRNG>(m, rng),
                                             var_adapter(m.num_params_r())
      {};
      
      ~adapt_diag_e_nuts() {};
      
      sample transition(sample& init_sample) {
        
        sample s = diag_e_nuts<M, BaseRNG>::transition(init_sample);
        
        if (this->_adapt_flag) {
          
          this->_learn_stepsize(this->_epsilon, s.accept_stat());
          
          this->_learn_variance(this->_z.mInv, this->_z.q);
          
        }
        
        return s;
        
      }
      
    };
    
  } // mcmc
  
} // stan


#endif
