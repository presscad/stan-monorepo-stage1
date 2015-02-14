#ifndef STAN__MATH__REV__SCAL__FUN__INV_LOGIT_HPP
#define STAN__MATH__REV__SCAL__FUN__INV_LOGIT_HPP

#include <stan/math/rev/arr/meta/var.hpp>
#include <stan/math/prim/scal/fun/inv_logit.hpp>
#include <stan/math/rev/scal/fun/v_vari.hpp>

namespace stan {
  namespace agrad {

    namespace {
      class inv_logit_vari : public op_v_vari {
      public:
        inv_logit_vari(vari* avi) :
          op_v_vari(stan::math::inv_logit(avi->val_),avi) {
        }
        void chain() {
          avi_->adj_ +=  adj_ * val_ * (1.0 - val_);
        }
      };
    }

    /**
     * The inverse logit function for variables (stan).
     *
     * See stan::math::inv_logit() for the double-based version.
     *
     * The derivative of inverse logit is
     *
     * \f$\frac{d}{dx} \mbox{logit}^{-1}(x) = \mbox{logit}^{-1}(x) (1 - \mbox{logit}^{-1}(x))\f$.
     *
     * @param a Argument variable.
     * @return Inverse logit of argument.
     */
    inline var inv_logit(const stan::agrad::var& a) {
      return var(new inv_logit_vari(a.vi_));
    }

  }
}
#endif
