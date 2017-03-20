#ifndef STAN_MATH_PRIM_SCAL_ERR_CHECK_3F2_CONVERGES_HPP
#define STAN_MATH_PRIM_SCAL_ERR_CHECK_3F2_CONVERGES_HPP

#include <stdexcept>
#include <sstream>
#include <cmath>

namespace stan {
  namespace math {

    /**
     * Check if the hypergeometric function (3F2) called with 
     * supplied arguments will converge, assuming arguments are
     * finite values.
     *
     * @tparam T_a1 Type of a1
     * @tparam T_a2 Type of a2
     * @tparam T_a3 Type of a3
     * @tparam T_b1 Type of b1
     * @tparam T_b2 Type of b2
     * @tparam T_z Type of z
     *
     * @param function Name of function ultimately relying on 3F2 (for error 
     &   messages)
     * @param a1 Variable to check
     * @param a2 Variable to check
     * @param a3 Variable to check
     * @param b1 Variable to check
     * @param b2 Variable to check
     * @param z Variable to check
     *
     * @throw <code>domain_error</code> if 3F2(a1, a2, a3, b1, b2, z)
     *   does not meet convergence conditions, or if any coefficient is NaN. 
     */
    template <typename T_a1, typename T_a2, typename T_a3, typename T_b1, 
      typename T_b2, typename T_z>
    inline void check_3F2_converges(const char* function, 
      const T_a1& a1, const T_a2& a2, const T_a3& a3, const T_b1& b1, 
      const T_b2& b2, const T_z& z
    ) {
      using std::fabs;
      if (fabs(z) < 1.0) return;
      if (fabs(z) == 1.0) {
        if (b1 + b2 > a1 + a2 + a3) return;
      }     
      std::stringstream msg;
      msg << "called from function '" << function << "', "
          << "hypergeometric function 3F2 does not meet convergence " 
          << "conditions with given arguments. " 
          << "a1: " << a1 << ", a2: " << a2 << ", a3: " << a3
          << "b1: " << b1 << ", b2: " << b2 << ", z: " << z;
      throw std::domain_error(msg.str());
    }

  }
}
#endif
