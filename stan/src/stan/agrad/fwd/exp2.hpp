#ifndef __STAN__AGRAD__FWD__EXP2__HPP__
#define __STAN__AGRAD__FWD__EXP2__HPP__

#include <stan/agrad/fwd/fvar.hpp>
#include <stan/meta/traits.hpp>
#include <stan/math/special_functions.hpp>

namespace stan{

  namespace agrad{

    template <typename T>
    inline
    fvar<T>
    exp2(const fvar<T>& x) {
      using stan::math::exp2;
      using std::log;
      return fvar<T>(exp2(x.val_), x.d_ * exp2(x.val_) * log(2));
    }
  }
}
#endif
