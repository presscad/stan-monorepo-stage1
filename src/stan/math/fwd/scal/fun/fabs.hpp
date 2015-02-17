#ifndef STAN__MATH__FWD__SCAL__FUN__FABS_HPP
#define STAN__MATH__FWD__SCAL__FUN__FABS_HPP

#include <stan/math/fwd/core/fvar.hpp>
#include <stan/math/prim/scal/meta/traits.hpp>
#include <stan/math/prim/scal/fun/constants.hpp>
#include <stan/math/prim/scal/fun/value_of.hpp>
#include <math.h>
#include <stan/math/prim/scal/meta/likely.hpp>

namespace stan {

  namespace agrad {

    template<typename T>
    inline
    fvar<T>
    fabs(const fvar<T>& x) {
      using stan::math::NOT_A_NUMBER;
      using ::fabs;
      using stan::math::value_of;

      if (unlikely(boost::math::isnan(value_of(x.val_))))
        return fvar<T>(fabs(x.val_),stan::math::NOT_A_NUMBER);
      else if (x.val_ > 0.0)
        return x;
      else if (x.val_ < 0.0)
        return fvar<T>(-x.val_, -x.d_);
      else
        return fvar<T>(0, 0);
    }
  }
}
#endif
