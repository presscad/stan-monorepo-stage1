#ifndef STAN_MATH_REV_SCAL_FUN_COS_HPP
#define STAN_MATH_REV_SCAL_FUN_COS_HPP

#include <stan/math/rev/core.hpp>
#include <stan/math/rev/mat/functor/triple.hpp>  // TEST
#include <cmath>

namespace stan {
  namespace math {

    namespace {
      class cos_vari : public op_v_vari {
      public:
        explicit cos_vari(vari* avi) :
          op_v_vari(std::cos(avi->val_), avi) {
        }
        void chain() {
          avi_->adj_ -= adj_ * std::sin(avi_->val_);

          // For testing purposes
          Eigen::VectorXd x(3);
          x << 1, 2, 3;
          Eigen::MatrixXd J;
          Eigen::VectorXd fvec;
          triple_functor f;
          jacobian(f, x, fvec, J);
        }
      };
    }

    /**
     * Return the cosine of a radian-scaled variable (cmath).
     *
     * The derivative is defined by
     *
     * \f$\frac{d}{dx} \cos x = - \sin x\f$.
     *
     *
       \f[
       \mbox{cos}(x) =
       \begin{cases}
         \cos(x) & \mbox{if } -\infty\leq x \leq \infty \\[6pt]
         \textrm{NaN} & \mbox{if } x = \textrm{NaN}
       \end{cases}
       \f]

       \f[
       \frac{\partial\, \mbox{cos}(x)}{\partial x} =
       \begin{cases}
         -\sin(x) & \mbox{if } -\infty\leq x\leq \infty \\[6pt]
         \textrm{NaN} & \mbox{if } x = \textrm{NaN}
       \end{cases}
       \f]
     *
     * @param a Variable for radians of angle.
     * @return Cosine of variable.
     */
    inline var cos(const var& a) {
      return var(new cos_vari(a.vi_));
    }

  }
}
#endif
