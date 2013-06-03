#ifndef __STAN__AGRAD__FWD__HYPOT__HPP__
#define __STAN__AGRAD__FWD__HYPOT__HPP__

#include <stan/agrad/fwd/fvar.hpp>
#include <stan/meta/traits.hpp>
#include <boost/math/special_functions/hypot.hpp>
#include <stan/math/functions/inv.hpp>

namespace stan {

  namespace agrad {

    template <typename T>
    inline
    fvar<T>
    hypot(const fvar<T>& x1, const fvar<T>& x2) {
      using boost::math::hypot;
      using std::sqrt;
      using stan::math::inv;
      T u = hypot(x1.val_, x2.val_);
      return fvar<T>(u, (x1.d_ * x1.val_ + x2.d_ * x2.val_) * inv(u));
    }

    template <typename T>
    inline
    fvar<typename stan::return_type<T,double>::type>
    hypot(const fvar<T>& x1, double x2) {
      using boost::math::hypot;
      using std::sqrt;
      typename stan::return_type<T,double>::type u = hypot(x1.val_, x2);
      return fvar<typename stan::return_type<T,double>::type>(u, 
                                              (x1.d_ * x1.val_) * inv(u));
    }

    template <typename T>
    inline
    fvar<typename stan::return_type<T,double>::type>
    hypot(double x1, const fvar<T>& x2) {
      using boost::math::hypot;
      using std::sqrt;
      using stan::math::inv;
      typename stan::return_type<T,double>::type u = hypot(x1, x2.val_);
      return fvar<typename 
                  stan::return_type<T,double>::type>(u, 
                                                  (x2.d_ * x2.val_) * inv(u));
    }

  }
}
#endif
