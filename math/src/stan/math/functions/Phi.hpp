#ifndef __STAN__MATH__FUNCTIONS__PHI_HPP__
#define __STAN__MATH__FUNCTIONS__PHI_HPP__

#include <boost/math/tools/promotion.hpp>
#include <boost/math/special_functions/erf.hpp>
#include <stan/math/constants.hpp>

namespace stan {
  namespace math {

    /**
     * The unit normal cumulative distribution function.  
     *
     * The return value for a specified input is the probability that
     * a random unit normal variate is less than or equal to the
     * specified value, defined by
     *
     * \f$\Phi(x) = \int_{-\infty}^x \mbox{\sf Norm}(x|0,1) \ dx\f$
     *
     * This function can be used to implement the inverse link function
     * for probit regression.  
     *
     * @param x Argument.
     * @return Probability random sample is less than or equal to argument. 
     */
    template <typename T>
    inline typename boost::math::tools::promote_args<T>::type
    Phi(const T x) {
      return 0.5 * (1.0 + boost::math::erf(INV_SQRT_2 * x));
    }

  }
}

#endif
