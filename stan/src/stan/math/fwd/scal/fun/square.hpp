#ifndef STAN_MATH_FWD_SCAL_FUN_SQUARE_HPP
#define STAN_MATH_FWD_SCAL_FUN_SQUARE_HPP

#include <stan/math/fwd/core.hpp>

#include <stan/math/prim/scal/fun/square.hpp>

namespace stan {

  namespace agrad {

    template <typename T>
    inline
    fvar<T>
    square(const fvar<T>& x) {
      using stan::math::square;
      return fvar<T>(square(x.val_),
                     x.d_ * 2 * x.val_);
    }
  }
}
#endif
