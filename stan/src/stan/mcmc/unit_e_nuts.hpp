#ifndef __STAN__MCMC__UNIT__E__NUTS__BETA__
#define __STAN__MCMC__UNIT__E__NUTS__BETA__

#include <stan/mcmc/base_nuts.hpp>
#include <stan/mcmc/unit_e_point.hpp>
#include <stan/mcmc/unit_e_metric.hpp>
#include <stan/mcmc/expl_leapfrog.hpp>

namespace stan {

  namespace mcmc {

    // The No-U-Turn Sampler (NUTS) on a
    // Euclidean manifold with unit metric
    
    template <typename M, class BaseRNG>
    class unit_e_nuts: public base_nuts<M,
                                        unit_e_point,
                                        unit_e_metric,
                                        expl_leapfrog,
                                        BaseRNG> {
      
    public:
      
    unit_e_nuts(M &m, BaseRNG& rng): base_nuts<M, unit_e_point, unit_e_metric,
                                               expl_leapfrog, BaseRNG>(m, rng)
    {};
      
    private:
      
      bool _compute_criterion(ps_point& start, 
                              unit_e_point& finish, 
                              Eigen::VectorXd& rho) {
        return rho.dot(finish.p) > 0
            && rho.dot(start.p)  > 0;
      }
                                          
    };
    
  } // mcmc
    
} // stan

#endif
