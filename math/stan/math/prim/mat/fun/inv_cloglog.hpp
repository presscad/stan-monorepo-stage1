#ifndef STAN_MATH_PRIM_MAT_FUN_INV_CLOGLOG_HPP
#define STAN_MATH_PRIM_MAT_FUN_INV_CLOGLOG_HPP

#include <stan/math/prim/mat/vectorize/apply_scalar_unary.hpp>
#include <stan/math/prim/scal/fun/inv_cloglog.hpp>

namespace stan {
  namespace math {

    /**
     * Example of how to define a functor for a vectorized function.
     * The example includes a constrained version of inv_cloglog().
     */
    struct inv_cloglog_fun {
      template <typename T>
      static inline T fun(const T& x) {
        using stan::math::inv_cloglog;
        return inv_cloglog(x);
      }
    };

    template <typename T>
    inline typename apply_scalar_unary<inv_cloglog_fun, T>::return_t
    inv_cloglog(const T& x) {
      return apply_scalar_unary<inv_cloglog_fun, T>::apply(x);
    }

  }
}

#endif
