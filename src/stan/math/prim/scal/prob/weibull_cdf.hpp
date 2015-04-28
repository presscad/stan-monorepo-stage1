#ifndef STAN_MATH_PRIM_SCAL_PROB_WEIBULL_CDF_HPP
#define STAN_MATH_PRIM_SCAL_PROB_WEIBULL_CDF_HPP

#include <boost/random/weibull_distribution.hpp>
#include <boost/random/variate_generator.hpp>
#include <stan/math/prim/scal/meta/OperandsAndPartials.hpp>
#include <stan/math/prim/scal/err/check_consistent_sizes.hpp>
#include <stan/math/prim/scal/err/check_finite.hpp>
#include <stan/math/prim/scal/err/check_nonnegative.hpp>
#include <stan/math/prim/scal/err/check_not_nan.hpp>
#include <stan/math/prim/scal/err/check_positive_finite.hpp>
#include <stan/math/prim/scal/fun/multiply_log.hpp>
#include <stan/math/prim/scal/fun/value_of.hpp>
#include <stan/math/prim/scal/meta/length.hpp>
#include <stan/math/prim/scal/meta/constants.hpp>
#include <stan/math/prim/scal/meta/include_summand.hpp>
#include <stan/math/prim/scal/meta/VectorBuilder.hpp>
#include <stan/math/prim/scal/meta/VectorView.hpp>

namespace stan {

  namespace prob {

    template <typename T_y, typename T_shape, typename T_scale>
    typename return_type<T_y, T_shape, T_scale>::type
    weibull_cdf(const T_y& y, const T_shape& alpha, const T_scale& sigma) {
      typedef typename stan::partials_return_type<T_y, T_shape, T_scale>::type
        T_partials_return;

      static const char* function("stan::prob::weibull_cdf");

      using stan::math::check_positive_finite;
      using stan::math::check_nonnegative;
      using boost::math::tools::promote_args;
      using stan::math::value_of;

      // check if any vectors are zero length
      if (!(stan::length(y)
            && stan::length(alpha)
            && stan::length(sigma)))
        return 1.0;

      T_partials_return cdf(1.0);
      check_nonnegative(function, "Random variable", y);
      check_positive_finite(function, "Shape parameter", alpha);
      check_positive_finite(function, "Scale parameter", sigma);

      agrad::OperandsAndPartials<T_y, T_shape, T_scale>
        operands_and_partials(y, alpha, sigma);

      VectorView<const T_y> y_vec(y);
      VectorView<const T_scale> sigma_vec(sigma);
      VectorView<const T_shape> alpha_vec(alpha);
      size_t N = max_size(y, sigma, alpha);
      for (size_t n = 0; n < N; n++) {
        const T_partials_return y_dbl = value_of(y_vec[n]);
        const T_partials_return sigma_dbl = value_of(sigma_vec[n]);
        const T_partials_return alpha_dbl = value_of(alpha_vec[n]);
        const T_partials_return pow_ = pow(y_dbl / sigma_dbl, alpha_dbl);
        const T_partials_return exp_ = exp(-pow_);
        const T_partials_return cdf_ = 1.0 - exp_;

        // cdf
        cdf *= cdf_;

        // gradients
        const T_partials_return rep_deriv = exp_ * pow_ / cdf_;
        if (!is_constant_struct<T_y>::value)
          operands_and_partials.d_x1[n] += rep_deriv * alpha_dbl / y_dbl;
        if (!is_constant_struct<T_shape>::value)
          operands_and_partials.d_x2[n] += rep_deriv * log(y_dbl / sigma_dbl);
        if (!is_constant_struct<T_scale>::value)
          operands_and_partials.d_x3[n] -= rep_deriv * alpha_dbl / sigma_dbl;
      }

      if (!is_constant_struct<T_y>::value) {
        for (size_t n = 0; n < stan::length(y); ++n)
          operands_and_partials.d_x1[n] *= cdf;
      }
      if (!is_constant_struct<T_shape>::value) {
        for (size_t n = 0; n < stan::length(alpha); ++n)
          operands_and_partials.d_x2[n] *= cdf;
      }
      if (!is_constant_struct<T_scale>::value) {
        for (size_t n = 0; n < stan::length(sigma); ++n)
          operands_and_partials.d_x3[n] *= cdf;
      }

      return operands_and_partials.to_var(cdf, y, alpha, sigma);
    }
  }
}
#endif
