#ifndef STAN__MATH__FUNCTIONS__LOGICAL_LT_HPP
#define STAN__MATH__FUNCTIONS__LOGICAL_LT_HPP

namespace stan {
  namespace math {

    /**
     * Return 1 if the first argument is strictly less than the second.
     * Equivalent to <code>x1 &lt; x2</code>.
     *
     * @tparam T1 Type of first argument.
     * @tparam T2 Type of second argument.
     * @param x1 First argument
     * @param x2 Second argument
     * @return <code>true</code> iff <code>x1 &lt; x2</code>
     */
    template <typename T1, typename T2>
    inline
    int
    logical_lt(T1 x1, T2 x2) {
      return x1 < x2;
    }

  }
}

#endif
