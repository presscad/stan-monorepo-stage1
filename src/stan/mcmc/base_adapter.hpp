#ifndef __STAN__MCMC__BASE__ADAPTER__BETA__
#define __STAN__MCMC__BASE__ADAPTER__BETA__

#include <stan/math/matrix/Eigen.hpp>

namespace stan {
  
  namespace mcmc {
    
    class base_adapter {
      
    public:
      
      base_adapter(): _adapt_flag(true) {};
      
      void engage_adaptation()    { _adapt_flag = true; }
      void disengage_adaptation() { _adapt_flag = false; }
      
      bool adapting() { return _adapt_flag; }
      
    protected:
      
      bool _adapt_flag;
      
    };
    
  } // mcmc
  
} // stan

#endif