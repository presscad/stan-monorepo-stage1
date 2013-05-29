#ifndef __STAN__AGRAD__FWD__FALLING_FACTORIAL__HPP__
#define __STAN__AGRAD__FWD__FALLING_FACTORIAL__HPP__

#include <stan/agrad/fwd/fvar.hpp>
#include <stan/meta/traits.hpp>
#include <stan/math/functions/falling_factorial.hpp>
#include <boost/math/special_functions/digamma.hpp>

namespace stan{

  namespace agrad{

    template <typename T>
    inline
    fvar<T>
    falling_factorial(const fvar<T> x, const int & n) {
      using stan::math::falling_factorial;
      using boost::math::digamma;

      T falling_fact(falling_factorial(x.val_,n));
      return fvar<T>(falling_fact, falling_fact * digamma(x.val_ + 1) * x.d_);
    }
  }
}
#endif
