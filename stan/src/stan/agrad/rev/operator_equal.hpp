#ifndef __STAN__AGRAD__REV__OPERATOR_EQUAL_HPP__
#define __STAN__AGRAD__REV__OPERATOR_EQUAL_HPP__

#include <stan/agrad/rev/var.hpp>

namespace stan {
  namespace agrad {

    /**
     * Equality operator comparing two variables' values (C++).
     *
     * @param a First variable.  
     * @param b Second variable. 
     * @return True if the first variable's value is the same as the
     * second's.
     */
    inline bool operator==(const var& a, const var& b) {
      return a.val() == b.val();
    }

    /**
     * Equality operator comparing a variable's value and a double
     * (C++).
     *
     * @param a First variable.  
     * @param b Second value.
     * @return True if the first variable's value is the same as the
     * second value.
     */
    inline bool operator==(const var& a, const double b) {
      return a.val() == b;
    }
  
    /**
     * Equality operator comparing a scalar and a variable's value
     * (C++).
     *
     * @param a First scalar.
     * @param b Second variable.
     * @return True if the variable's value is equal to the scalar.
     */
    inline bool operator==(const double a, const var& b) {
      return a == b.val();
    }

  }
}
#endif
