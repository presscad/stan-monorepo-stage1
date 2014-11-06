#ifndef STAN__AGRAD__REV__FUNCTIONS__LOG_MIX_HPP
#define STAN__AGRAD__REV__FUNCTIONS__LOG_MIX_HPP

#include <cmath>
#include <stan/agrad/rev.hpp>
// #include <stan/agrad/rev/internal/precomp_vvv_vari.hpp>
#include <stan/math/functions/log_mix.hpp>

namespace stan {

  namespace agrad {

    var log_mix(var theta, var lambda1, var lambda2) {
      using stan::math::log_mix;
      using std::exp;
      double theta_d = theta.val();
      double lambda1_d = lambda1.val();
      double lambda2_d = lambda2.val();
      double result = stan::math::log_mix(theta_d, lambda1_d, lambda2_d);

      double d_theta(0);
      double d_lambda1(0);
      double d_lambda2(0);
      if (lambda1_d > lambda2_d) {
        double lam2_m_lam1 = lambda2_d - lambda1_d;
        double exp_lam2_m_lam1 = exp(lam2_m_lam1);
        double one_m_exp_lam2_m_lam1 = 1 - exp_lam2_m_lam1;
        double one_m_t = 1 - theta_d;
        double one_m_t_prod_exp_lam2_m_lam1 = one_m_t * exp_lam2_m_lam1;
        double t_plus_one_m_t_prod_exp_lam2_m_lam1 
          = theta_d + one_m_t_prod_exp_lam2_m_lam1;
        d_theta 
          = one_m_exp_lam2_m_lam1 
          / t_plus_one_m_t_prod_exp_lam2_m_lam1;
        std::cout << "d_theta=" << d_theta << std::endl;
        d_lambda1
          = theta_d
          / t_plus_one_m_t_prod_exp_lam2_m_lam1;
        d_lambda2
          = one_m_t_prod_exp_lam2_m_lam1
          / t_plus_one_m_t_prod_exp_lam2_m_lam1;
      } else {
        
      }
      return var(new precomp_vvv_vari(result, 
                                      theta.vi_, lambda1.vi_, lambda2.vi_,
                                      d_theta, d_lambda1, d_lambda2));
    }


  }

}

#endif
