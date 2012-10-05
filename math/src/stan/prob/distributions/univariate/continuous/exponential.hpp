#ifndef __STAN__PROB__DISTRIBUTIONS__UNIVARIATE__CONTINUOUS__EXPONENTIAL_HPP__
#define __STAN__PROB__DISTRIBUTIONS__UNIVARIATE__CONTINUOUS__EXPONENTIAL_HPP__

#include <stan/agrad.hpp>
#include <stan/math/error_handling.hpp>
#include <stan/math/special_functions.hpp>
#include <stan/meta/traits.hpp>
#include <stan/prob/constants.hpp>
#include <stan/prob/traits.hpp>

namespace stan {
  
  namespace prob {

    /**
     * The log of an exponential density for y with the specified
     * inverse scale parameter.
     * Inverse scale parameter must be greater than 0.
     * y must be greater than or equal to 0.
     * 
     \f{eqnarray*}{
       y 
       &\sim& 
       \mbox{\sf{Expon}}(\beta) \\
       \log (p (y \,|\, \beta) )
       &=& 
       \log \left( \beta \exp^{-\beta y} \right) \\
       &=& 
       \log (\beta) - \beta y \\
       & & 
       \mathrm{where} \; y > 0
     \f}
     *
     * @param y A scalar variable.
     * @param beta Inverse scale parameter.
     * @throw std::domain_error if beta is not greater than 0.
     * @throw std::domain_error if y is not greater than or equal to 0.
     * @tparam T_y Type of scalar.
     * @tparam T_inv_scale Type of inverse scale.
     */
    template <bool propto,
              typename T_y, typename T_inv_scale, 
              class Policy>
    typename return_type<T_y,T_inv_scale>::type
    exponential_log(const T_y& y, const T_inv_scale& beta, 
                    const Policy&) {
      static const char* function = "stan::prob::exponential_log(%1%)";

      // check if any vectors are zero length
      if (!(stan::length(y) 
            && stan::length(beta)))
	return 0.0;
      
      using stan::math::check_finite;
      using stan::math::check_positive;
      using stan::math::check_not_nan;
      using stan::math::check_consistent_sizes;
      
      typename return_type<T_y,T_inv_scale>::type logp(0.0);
      if(!check_not_nan(function, y, "Random variable", &logp, Policy()))
        return logp;
      if(!check_finite(function, beta, "Inverse scale parameter", &logp, Policy()))
        return logp;
      if(!check_positive(function, beta, "Inverse scale parameter", &logp, Policy()))
        return logp;

      if (!(check_consistent_sizes(function,
                                   y,beta,
				   "Random variable","Inverse scale parameter",
                                   &logp, Policy())))
        return logp;
      
      
      // set up template expressions wrapping scalars into vector views
      VectorView<const T_y> y_vec(y);
      VectorView<const T_inv_scale> beta_vec(beta);
      size_t N = max_size(y, beta);
      
      for (size_t n = 0; n < N; n++) {
	if (include_summand<propto,T_inv_scale>::value)
	  logp += log(beta_vec[n]);
	if (include_summand<propto,T_y,T_inv_scale>::value)
	  logp -= beta_vec[n] * y_vec[n];
      }
      return logp;
    }
    
    template <bool propto,
              typename T_y, typename T_inv_scale>
    inline
    typename return_type<T_y,T_inv_scale>::type
    exponential_log(const T_y& y, const T_inv_scale& beta) {
      return exponential_log<propto>(y,beta,stan::math::default_policy());
    }

    template <typename T_y, typename T_inv_scale,
              class Policy>
    inline
    typename return_type<T_y,T_inv_scale>::type
    exponential_log(const T_y& y, const T_inv_scale& beta, const Policy&) {
      return exponential_log<false>(y,beta,Policy());
    }

    template <typename T_y, typename T_inv_scale>
    inline
    typename return_type<T_y,T_inv_scale>::type
    exponential_log(const T_y& y, const T_inv_scale& beta) {
      return exponential_log<false>(y,beta,stan::math::default_policy());
    }



    /**
     * Calculates the exponential cumulative distribution function for
     * the given y and beta.
     *
     * Inverse scale parameter must be greater than 0.
     * y must be greater than or equal to 0.
     * 
     * @param y A scalar variable.
     * @param beta Inverse scale parameter.
     * @tparam T_y Type of scalar.
     * @tparam T_inv_scale Type of inverse scale.
     * @tparam Policy Error-handling policy.
     */
    template <typename T_y, 
              typename T_inv_scale, 
              class Policy>
    typename boost::math::tools::promote_args<T_y,T_inv_scale>::type
    exponential_cdf(const T_y& y, 
                  const T_inv_scale& beta, 
                  const Policy&) {

      static const char* function = "stan::prob::exponential_cdf(%1%)";

      using stan::math::check_finite;
      using stan::math::check_positive;
      using stan::math::check_not_nan;
      using boost::math::tools::promote_args;

      typename promote_args<T_y,T_inv_scale>::type lp;
      if(!check_not_nan(function, y, "Random variable", &lp, Policy()))
        return lp;
      if(!check_finite(function, beta, "Inverse scale parameter", &lp, Policy()))
        return lp;
      if(!check_positive(function, beta, "Inverse scale parameter", &lp, Policy()))
        return lp;
      
      if (y < 0)
        return 1.0;

      return 1.0 - exp(-beta * y);
    }

    template <typename T_y, 
              typename T_inv_scale>
    inline
    typename boost::math::tools::promote_args<T_y,T_inv_scale>::type
    exponential_cdf(const T_y& y, 
                  const T_inv_scale& beta) {
      return exponential_cdf(y,beta,stan::math::default_policy());
    }
    


  }
}

#endif
