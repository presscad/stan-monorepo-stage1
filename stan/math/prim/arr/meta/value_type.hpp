#ifndef STAN_MATH_PRIM_ARR_META_VALUE_TYPE_HPP
#define STAN_MATH_PRIM_ARR_META_VALUE_TYPE_HPP

#include <vector>

namespace stan {
  namespace math {

    /**
     * Template metaprogram class to compute the type of values stored
     * in a standard vector.
     *
     * @tparam T type of elements in standard vector.
     */
    template <typename T>
    struct value_type<std::vector<T> > {
      /**
       * Type of value stored in a standard vector with type
       * <code>T</code> entries.
       */
      typedef typename std::vector<T>::value_type type;
    };

  }
}
#endif
