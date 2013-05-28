#ifndef __STAN__AGRAD__FWD__SQRT__HPP__
#define __STAN__AGRAD__FWD__SQRT__HPP__

#include <stan/agrad/fwd/fvar.hpp>
#include <stan/meta/traits.hpp>

namespace stan {

  namespace agrad {

    template <typename T>
    inline 
    fvar<T>
    sqrt(const fvar<T>& x) {
      using std::sqrt;
      return fvar<T>(sqrt(x.val_), 0.5 * x.d_ / sqrt(x.val_));
    }
  }
}
#endif
