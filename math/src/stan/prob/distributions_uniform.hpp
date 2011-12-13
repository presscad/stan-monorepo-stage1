#ifndef __STAN__PROB__DISTRIBUTIONS_UNIFORM_HPP__
#define __STAN__PROB__DISTRIBUTIONS_UNIFORM_HPP__

#include "stan/prob/distributions_error_handling.hpp"
#include "stan/prob/distributions_constants.hpp"

#include <stan/meta/traits.hpp>

namespace stan {
  namespace prob {
    using boost::math::tools::promote_args;
    using boost::math::policies::policy;
    
    // CONTINUOUS, UNIVARIATE DENSITIES
    /**
     * The log of a uniform density for the given 
     * y, lower, and upper bound. 
     *
     \f{eqnarray*}{
     y &\sim& \mbox{\sf{U}}(\alpha, \beta) \\
     \log (p (y \,|\, \alpha, \beta)) &=& \log \left( \frac{1}{\beta-\alpha} \right) \\
     &=& \log (1) - \log (\beta - \alpha) \\
     &=& -\log (\beta - \alpha) \\
     & & \mathrm{ where } \; y \in [\alpha, \beta], \log(0) \; \mathrm{otherwise}
     \f}
     * 
     * @param y A scalar variable.
     * @param alpha Lower bound.
     * @param beta Upper bound.
     * @throw std::invalid_argument if the lower bound is greater than 
     *    or equal to the lower bound
     * @tparam T_y Type of scalar.
     * @tparam T_low Type of lower bound.
     * @tparam T_high Type of upper bound.
     */
    template <bool propto = false, 
      typename T_y, typename T_low, typename T_high, 
      class Policy = policy<> >
    inline typename boost::math::tools::promote_args<T_y,T_low,T_high>::type
    uniform_log(const T_y& y, const T_low& alpha, const T_high& beta, const Policy& = Policy()) {
      static const char* function = "stan::prob::uniform_log<%1%>(%1%)";
      
      double result;
      if(!stan::prob::check_x(function, y, &result, Policy()))
	return result;
      if(!stan::prob::check_bounds(function, alpha, beta, &result, Policy()))
	return result;
      
      if (y < alpha || y > beta)
	return LOG_ZERO;
      
      if (!propto
          || !stan::is_constant<T_low>::value
          || !stan::is_constant<T_high>::value)
        return -log(beta - alpha);
      return 0.0;
    }
     
  }
}

#endif
