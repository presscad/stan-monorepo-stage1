#ifndef STAN_MATH_FWD_SCAL_FUN_FLOOR_HPP
#define STAN_MATH_FWD_SCAL_FUN_FLOOR_HPP

#include <stan/math/fwd/core.hpp>

#include <math.h>

namespace stan {

  namespace math {

    template <typename T>
    inline
    fvar<T>
    floor(const fvar<T>& x) {
      using ::floor;
        return fvar<T>(floor(x.val_), 0);
    }
  }
}
#endif
