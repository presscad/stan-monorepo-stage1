#ifndef STAN_MATH_PRIM_SCAL_FUN_GRAD_REG_INC_BETA_HPP
#define STAN_MATH_PRIM_SCAL_FUN_GRAD_REG_INC_BETA_HPP

#include <stan/math/prim/scal/fun/grad_inc_beta.hpp>
#include <stan/math/prim/scal/fun/inc_beta.hpp>
#include <stan/math/prim/scal/fun/lbeta.hpp>
#include <cmath>

namespace stan {
  namespace math {

    /**
     * Computes the gradients of the regularized incomplete beta function.
     *
     * This function computes gradients of <code>ibeta</code>, with
     * respect to the arguments <code>a</code> and <code>b</code>.
     *
     * @tparam T type of arguments
     * @param[out] g1 gradient with respect to a: $\frac{d \mathrm{ibeta}(a, b, z)}{d a}$
     * @param[out] g2 gradient with respect to b: $\frac{d \mathrm{ibeta}(a, b, z)}{d b}$
     * @param[in] a a
     * @param[in] b b
     * @param[in] z z
     * @param[in] digammaA the value of <code>digamma(a)</code>
     * @param[in] digammaB the value of <code>digamma(b)</code>
     * @param[in] digammaSum the value of <code>digamma(a + b)</code>
     * @param[in] betaAB the value of <code>beta(a, b)</code>
     */
    template<typename T>
    void grad_reg_inc_beta(T& g1, T& g2, T a, T b, T z,
                           T digammaA, T digammaB, T digammaSum, T betaAB) {
      using std::exp;

      T dBda = 0;
      T dBdb = 0;
      grad_inc_beta(dBda, dBdb, a, b, z);
      T b1 = exp(lbeta(a, b)) * inc_beta(a, b, z);
      g1 = (dBda - b1 * (digammaA - digammaSum)) / betaAB;
      g2 = (dBdb - b1 * (digammaB - digammaSum)) / betaAB;
    }

  }
}
#endif
