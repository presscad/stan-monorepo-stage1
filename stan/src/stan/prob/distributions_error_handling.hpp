#ifndef __STAN__PROB__DISTRIBUTIONS_ERROR_HANDLING_HPP__
#define __STAN__PROB__DISTRIBUTIONS_ERROR_HANDLING_HPP__

#include <limits>
#include <boost/math/policies/policy.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>
#include <Eigen/Dense>
#include "stan/prob/transform.hpp"

namespace stan { 

  namespace prob {

    using boost::math::policies::raise_domain_error;


    /**
     * Note that this test catches both infinity and NaN.
     * Some special cases permit x to be infinite, so these must be tested 1st,
     * leaving this test to catch any NaNs.  see Normal and cauchy for example.
     */
    template <typename T_x, typename T_result, class Policy>
    inline bool check_x(const char* function,
			const T_x& x,
			T_result* result,
			const Policy& pol) {
      if (!boost::math::isfinite(x)) {
	*result = raise_domain_error<T_x>(function,
					  "Random variate x is %1%, but must be finite!",
					  x, pol);
	return false;
      }
      return true;
    }

    /**
     * Note that this test catches both infinity and NaN.
     * Some special cases permit x to be infinite, so these must be tested 1st,
     * leaving this test to catch any NaNs.  see Normal and cauchy for example.
     */
    template <typename T_x, typename T_result, class Policy>
    inline bool check_x(const char* function,
			const std::vector<T_x>& x,
			T_result* result,
			const Policy& pol) {
      for (int i = 0; i < x.size(); i++) {
	if (!boost::math::isfinite(x[i])) {
	  *result = raise_domain_error<T_x>(function,
					    "Random variate x is %1%, but must be finite!",
					    x[i], pol);
	  return false;
	}
      }
      return true;
    }
    
    template <typename T_x, typename T_result, class Policy>
    inline bool check_x(const char* function,
			const Eigen::Matrix<T_x,Eigen::Dynamic,1>& x,
			T_result* result,
			const Policy& pol) {
      for (int i = 0; i < x.rows(); i++) {
	if (!boost::math::isfinite(x[i])) {
	  *result = raise_domain_error<T_x>(function,
					    "Random variate x is %1%, but must be finite!",
					    x[i], pol);
	  return false;
	}
      }
      return true;
      // Note that this test catches both infinity and NaN.
      // Some special cases permit x to be infinite, so these must be tested 1st,
      // leaving this test to catch any NaNs.  see Normal and cauchy for example.
    }

    template <typename T_x, typename T_low, typename T_high, typename T_result, class Policy>
    inline bool check_bounded_x(
			const char* function,
			const T_x& x,
			const T_low& low,
			const T_high& high,
			T_result* result,
			const Policy& pol) {
      if (!boost::math::isfinite(x) || !(low <= x && x <= high)) {
	std::ostringstream msg;
	msg << "Random variate x is %1%, but must be finite and between "
	    << low
	    << " and "
	    << high;
	*result = raise_domain_error<T_x>(function,
					     msg.str().c_str(),
					     x, pol);
	return false;
      }
      return true;
      // Note that this test catches both infinity and NaN.
      // Some special cases permit x to be infinite, so these must be tested 1st,
      // leaving this test to catch any NaNs.  see Normal and cauchy for example.
    }
    

    template <typename T_scale, typename T_result, class Policy>
    inline bool check_scale(const char* function,
			    const T_scale& scale,
			    T_result* result,
			    const Policy& pol) {
      if(!(scale > 0) || !boost::math::isfinite(scale)) { // Assume scale == 0 is NOT valid for any distribution.
	*result = raise_domain_error<T_scale>(function,
					      "Scale parameter is %1%, but must be > 0 !", scale, pol);
	return false;
      }
      return true;
    }

    template <typename T_inv_scale, typename T_result, class Policy>
    inline bool check_inv_scale(
			    const char* function,
			    const T_inv_scale& invScale,
			    T_result* result,
			    const Policy& pol) {
      if(!(invScale > 0) || !boost::math::isfinite(invScale)) { // Assume scale == 0 is NOT valid for any distribution.
	*result = raise_domain_error<T_inv_scale>(function,
						  "Inverse scale parameter is %1%, but must be > 0 !", invScale, pol);
	return false;
      }
      return true;
    }


    template <typename T_x, typename T_result, class Policy>
    inline bool check_nonnegative(
				  const char* function,
				  const T_x& x,
				  const char* name,
				  T_result* result,
				  const Policy& pol) {
      if(!boost::math::isfinite(x) || !(x >= 0)) {
	std::string message(name);
	message += " is %1%, but must be finite and >= 0!";
	*result = raise_domain_error<T_x>(function,
					  message.c_str(), x, pol);
	return false;
      }
      return true;
    }

    template <typename T_result, class Policy>
    inline bool check_nonnegative(
				  const char* function,
				  const unsigned int& x,
				  const char* name,
				  T_result* result,
				  const Policy& pol) {
      if (std::numeric_limits<unsigned int>::has_infinity &&
	  x == std::numeric_limits<unsigned int>::infinity() ) {
	std::string message(name);
	message += " is %1%, but must be finite and >= 0!";
	*result = raise_domain_error<unsigned int>(function,
						   message.c_str(), x, pol);
	return false;
      }
      return true;
    }


    template <typename T_x, typename T_result, class Policy>
    inline bool check_positive(
				  const char* function,
				  const T_x& x,
				  const char* name,
				  T_result* result,
				  const Policy& pol) {
      if(!boost::math::isfinite(x) || !(x > 0)) {
	std::string message(name);
	message += " is %1%, but must be finite and > 0!";
	*result = raise_domain_error<T_x>(function,
					  message.c_str(), x, pol);
	return false;
      }
      return true;
    }

    template <typename T_location, typename T_result, class Policy>
    inline bool check_location(
			       const char* function,
			       const T_location& location,
			       T_result* result,
			       const Policy& pol) {
      if(!boost::math::isfinite(location)) {
	*result = raise_domain_error<T_location>(
						 function,
						 "Location parameter is %1%, but must be finite!", location, pol);
	return false;
      }
      return true;
    }

    template <typename T_bound, typename T_result, class Policy>
    inline bool check_lower_bound(
				  const char* function,
				  const T_bound& lb,
				  T_result* result,
				  const Policy& pol) {
      if(!boost::math::isfinite(lb)) {
	*result = raise_domain_error<T_bound>(function,
					      "Lower bound is %1%, but must be finite!", 
					      lb, pol);
	return false;
      }
      return true;
    }


    template <typename T_bound, typename T_result, class Policy>
    inline bool check_upper_bound(
				  const char* function,
				  const T_bound& ub,
				  T_result* result,
				  const Policy& pol) {
      if(!boost::math::isfinite(ub)) {
	*result = raise_domain_error<T_bound>(function,
					      "Upper bound is %1%, but must be finite!", ub, pol);
	return false;
      }
      return true;
    }

    template <typename T_lb, typename T_ub, typename T_result, class Policy>
    inline bool check_bounds(
			     const char* function,
			     const T_lb& lower,
			     const T_ub& upper,
			     T_result* result,
			     const Policy& pol) {
      if (false == check_lower_bound(function, lower, result, pol))
	return false;
      if (false == check_upper_bound(function, upper, result, pol))
	return false;
      if (lower >= upper) {
	*result = raise_domain_error<T_lb>(function,
					   "lower parameter is %1%, but must be less than upper!", 
					   lower, pol);
	return false;
      }
      return true;
    }

    
    template <typename T_covar, typename T_result, class Policy>
    inline bool check_cov_matrix(
				 const char* function,
				 const Eigen::Matrix<T_covar,Eigen::Dynamic,Eigen::Dynamic>& Sigma,
				 T_result* result,
				 const Policy& pol) {
      if (!stan::prob::cov_matrix_validate(Sigma)) {
	std::ostringstream stream;
	stream << "Sigma is not a valid covariance matrix. Sigma must be symmetric and positive semi-definite. Sigma: \n" 
	       << Sigma
	       << "\nSigma(0,0): %1%";
	*result = raise_domain_error<T_covar>(function,
					     stream.str().c_str(), 
					     Sigma(0,0),
					     pol);
	return false;
      }
      return true;
    }


  }
}
#endif
