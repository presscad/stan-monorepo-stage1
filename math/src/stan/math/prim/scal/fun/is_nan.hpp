#ifndef STAN__MATH__PRIM__SCAL__FUN__IS_NAN_HPP
#define STAN__MATH__PRIM__SCAL__FUN__IS_NAN_HPP

#include <boost/math/special_functions/fpclassify.hpp>

namespace stan {

  namespace math {

    /**
     * Returns 1 if the input is NaN and 0 otherwise.
     *
     * Delegates to <code>boost::math::isnan</code>.
     *
     * @param x Value to test.
     * @return <code>1</code> if the value is NaN.
     */
    inline bool is_nan(double x) {
      return boost::math::isnan(x);
    }

  }
}

#endif
