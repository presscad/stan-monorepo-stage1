#ifndef STAN_MATH_REV_SCAL_FUN_ATANH_HPP
#define STAN_MATH_REV_SCAL_FUN_ATANH_HPP

#include <math.h>
#include <stan/math/rev/core.hpp>
#include <cmath>
#include <limits>

#ifdef _MSC_VER
#include <boost/math/special_functions/atanh.hpp>
using boost::math::atanh;
#endif

namespace stan {
  namespace math {

    namespace {
      class atanh_vari : public op_v_vari {
      public:
        atanh_vari(double val, vari* avi) :
          op_v_vari(val, avi) {
        }
        void chain() {
          avi_->adj_ += adj_ / (1.0 - avi_->val_ * avi_->val_);
        }
      };
    }

    /**
     * The inverse hyperbolic tangent function for variables (C99).
     *
     * For non-variable function, see ::atanh().
     *
     * The derivative is defined by
     *
     * \f$\frac{d}{dx} \mbox{atanh}(x) = \frac{1}{1 - x^2}\f$.
     *
       \f[
       \mbox{atanh}(x) =
       \begin{cases}
         \textrm{NaN} & \mbox{if } x < -1\\
         \tanh^{-1}(x) & \mbox{if } -1\leq x \leq 1 \\
         \textrm{NaN} & \mbox{if } x > 1\\[6pt]
         \textrm{NaN} & \mbox{if } x = \textrm{NaN}
       \end{cases}
       \f]

       \f[
       \frac{\partial\, \mbox{atanh}(x)}{\partial x} =
       \begin{cases}
         \textrm{NaN} & \mbox{if } x < -1\\
         \frac{\partial\, \tanh^{-1}(x)}{\partial x} & \mbox{if } -1\leq x\leq 1 \\
         \textrm{NaN} & \mbox{if } x > 1\\[6pt]
         \textrm{NaN} & \mbox{if } x = \textrm{NaN}
       \end{cases}
       \f]

       \f[
       \tanh^{-1}(x)=\frac{1}{2}\ln\left(\frac{1+x}{1-x}\right)
       \f]

       \f[
       \frac{\partial \, \tanh^{-1}(x)}{\partial x} = \frac{1}{1-x^2}
       \f]
    *
     * @param a The variable.
     * @return Inverse hyperbolic tangent of the variable.
     */
    inline var atanh(const var& a) {
      if (a == 1.0)
        return var(new atanh_vari(std::numeric_limits<double>::infinity(),
                                  a.vi_));
      if (a == -1.0)
        return var(new atanh_vari(-std::numeric_limits<double>::infinity(),
                                  a.vi_));
      return var(new atanh_vari(::atanh(a.val()), a.vi_));
    }

  }
}
#endif
