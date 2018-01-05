#ifndef STAN_MATH_FWD_SCAL_FUN_GAMMA_P_HPP
#define STAN_MATH_FWD_SCAL_FUN_GAMMA_P_HPP

#include <stan/math/fwd/core.hpp>
#include <stan/math/fwd/scal/fun/value_of_rec.hpp>
#include <stan/math/prim/scal/err/domain_error.hpp>
#include <stan/math/prim/scal/fun/gamma_p.hpp>
#include <stan/math/prim/scal/fun/grad_reg_lower_inc_gamma.hpp>

namespace stan {
  namespace math {

    template <typename T>
    inline
    fvar<T>
    gamma_p(const fvar<T>& x1, const fvar<T>& x2) {
      using std::log;
      using std::exp;
      using std::pow;
      using std::fabs;
      using boost::math::lgamma;
      using boost::math::digamma;



      if (x1.val_ < 0.0)
        domain_error("gamma_p grad, argument", "a", value_of_rec(x1),
          "is ", ", can not be negative.");
      if (x2.val_ < 0.0)
        domain_error("gamma_p grad, argument", "z", value_of_rec(x2),
          "is ", ", can not be negative.");


      T u = gamma_p(x1.val_, x2.val_);
      if (is_inf(x1.val_))
        return fvar<T>(u, std::numeric_limits<double>::quiet_NaN());
      if (is_inf(x2.val_))
        return fvar<T>(u, std::numeric_limits<double>::quiet_NaN());

      T der1 = grad_reg_lower_inc_gamma(x1.val_, x2.val_, 1.0e-10);
      T der2 = exp(-x2.val_ + (x1.val_ - 1.0) * log(x2.val_) - lgamma(x1.val_));

      return fvar<T>(u, x1.d_ * der1 + x2.d_ * der2);
    }

    template <typename T>
    inline
    fvar<T>
    gamma_p(const fvar<T>& x1, double x2) {
      using std::log;
      using std::exp;
      using std::pow;
      using std::fabs;
      using boost::math::digamma;


      if (x1.val_ < 0.0)
        domain_error("gamma_p grad, argument", "a", value_of_rec(x1),
          "is ", ", can not be negative.");
      if (x2 < 0.0)
        domain_error("gamma_p grad, argument", "z", x2,
          "is ", ", can not be negative.");


      T u = gamma_p(x1.val_, x2);
      if (is_inf(x1.val_))
        return fvar<T>(u, std::numeric_limits<double>::quiet_NaN());
      if (is_inf(x2))
        return fvar<T>(u, std::numeric_limits<double>::quiet_NaN());

      T der1 = grad_reg_lower_inc_gamma(x1.val_, x2, 1.0e-10);

      return fvar<T>(u, x1.d_ * der1);
    }

    template <typename T>
    inline
    fvar<T>
    gamma_p(double x1, const fvar<T>& x2) {
      using std::log;
      using std::exp;


      if (x1 < 0.0)
        domain_error("gamma_p grad, argument", "a", x1,
          "is ", ", can not be negative.");
      if (x2 < 0.0)
        domain_error("gamma_p grad, argument", "z", value_of_rec(x2),
          "is ", ", can not be negative.");


      T u = gamma_p(x1, x2.val_);
      if (is_inf(x1))
        return fvar<T>(u, std::numeric_limits<double>::quiet_NaN());
      
      T der2 = exp(-x2.val_ + (x1 - 1.0) * log(x2.val_) 
        - boost::math::lgamma(x1));

      return fvar<T>(u, x2.d_ * der2);
    }
  }
}
#endif
