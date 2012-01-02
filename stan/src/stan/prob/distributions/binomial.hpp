#ifndef __STAN__PROB__DISTRIBUTIONS__BINOMIAL_HPP__
#define __STAN__PROB__DISTRIBUTIONS__BINOMIAL_HPP__

#include <stan/prob/traits.hpp>
#include <stan/prob/error_handling.hpp>
#include <stan/prob/constants.hpp>

namespace stan {
  namespace prob {
    using boost::math::tools::promote_args;
    using boost::math::policies::policy;

    // Binomial(n|N,theta)  [N >= 0;  0 <= n <= N;  0 <= theta <= 1]
    template <bool propto = false,
	      typename T_n, typename T_N, typename T_prob, 
	      class Policy = policy<> >
    inline typename promote_args<T_prob>::type
      binomial_log(const T_n& n, const T_N& N, const T_prob& theta, const Policy& = Policy()) {
      // FIXME: domain checks
      typename promote_args<T_prob>::type lp(0.0);
      if (include_summand<propto>::value)
	lp += maths::binomial_coefficient_log<T_N>(N,n);
      if (include_summand<propto,T_n,T_N,T_prob>::value)
	lp += n * log(theta) + (N-n) * log1m (theta);
      return lp;
    }
  }
}
#endif
