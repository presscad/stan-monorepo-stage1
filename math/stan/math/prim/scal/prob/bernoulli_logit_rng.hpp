#ifndef STAN_MATH_PRIM_SCAL_PROB_BERNOULLI_LOGIT_RNG_HPP
#define STAN_MATH_PRIM_SCAL_PROB_BERNOULLI_LOGIT_RNG_HPP

#include <boost/random/bernoulli_distribution.hpp>
#include <boost/random/variate_generator.hpp>
#include <stan/math/prim/scal/err/check_consistent_sizes.hpp>
#include <stan/math/prim/scal/err/check_bounded.hpp>
#include <stan/math/prim/scal/err/check_finite.hpp>
#include <stan/math/prim/scal/err/check_not_nan.hpp>
#include <stan/math/prim/scal/fun/constants.hpp>
#include <stan/math/prim/scal/fun/inv_logit.hpp>
#include <stan/math/prim/scal/fun/log1m.hpp>
#include <stan/math/prim/scal/fun/value_of.hpp>
#include <stan/math/prim/scal/meta/include_summand.hpp>

namespace stan {
  namespace math {

    template <class RNG>
    inline int
    bernoulli_logit_rng(const double t,
                  RNG& rng) {
      using boost::variate_generator;
      using boost::bernoulli_distribution;
      using stan::math::inv_logit;

      static const char* function("bernoulli_rng");

      check_finite(function, "Logit transformed probability parameter", t);

      variate_generator<RNG&, bernoulli_distribution<> >
        bernoulli_rng(rng, bernoulli_distribution<>(inv_logit(t)));
      return bernoulli_rng();
    }

  }
}
#endif
