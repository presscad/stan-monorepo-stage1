#ifndef __STAN__MATH__FUNCTIONS__INV_SQUARE_HPP__
#define __STAN__MATH__FUNCTIONS__INV_SQUARE_HPP__

#include <boost/math/tools/promotion.hpp>

namespace stan {
  namespace math {
    
    template <typename T>
    inline 
    typename boost::math::tools::promote_args<T>::type
    inv_square(const T x) {
      return 1.0 / (x * x);
    }
  }
}

#endif
