#ifndef __STAN__MATH__SPECIAL_FUNCTIONS_HPP__
#define __STAN__MATH__SPECIAL_FUNCTIONS_HPP__

#include <stdexcept>

#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/special_functions/beta.hpp>
#include <boost/math/tools/promotion.hpp>
#include <boost/throw_exception.hpp>

#include <stan/math/constants.hpp>
#include <stan/math/error_handling.hpp>
#include <stan/meta/traits.hpp>
#include <stan/math/functions/inv_logit.hpp>

namespace stan {

  namespace math {


    // CONSTANTS

    /**
     * Return the value of pi.
     * 
     * @return Pi.
     */
    inline double pi() {
      return boost::math::constants::pi<double>();
    }

    /**
     * Return the base of the natural logarithm.
     *
     * @return Base of natural logarithm.
     */
    inline double e() {
      return E;
    }

    /**
     * Return the square root of two.
     *
     * @return Square root of two. 
     */
    inline double sqrt2() {
      return SQRT_2;
    }


    /**
     * Return natural logarithm of ten.
     *
     * @return Natural logarithm of ten.
     */
    inline double log10() {
      return LOG_10;
    }

    /**
     * Return positive infinity.
     *
     * @return Positive infinity.
     */
    inline double positive_infinity() {
      return INFTY;
    }

    /**
     * Return negative infinity.
     *
     * @return Negative infinity.
     */
    inline double negative_infinity() {
      return NEGATIVE_INFTY;
    }

    /**
     * Return (quiet) not-a-number.
     *
     * @return Quiet not-a-number.
     */
    inline double not_a_number() {
      return NOT_A_NUMBER;
    }

    /**
     * Return minimum positive number representable.
     *
     * @return Minimum positive number.
     */
    inline double epsilon() {
      return EPSILON;
    }

    /**
     * Return maximum negative number (i.e., negative
     * number with smallest absolute value).
     *
     * @return Maximum negative number.
     */
    inline double negative_epsilon() {
      return NEGATIVE_EPSILON;
    }


  }

}

#endif
