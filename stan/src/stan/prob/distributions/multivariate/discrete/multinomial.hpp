#ifndef __STAN__PROB__DISTRIBUTIONS__MULTIVARIATE__DISCRETE__MULTINOMIAL_HPP__
#define __STAN__PROB__DISTRIBUTIONS__MULTIVARIATE__DISCRETE__MULTINOMIAL_HPP__

#include <boost/random/uniform_01.hpp>
#include <boost/random/variate_generator.hpp>

#include <stan/prob/traits.hpp>
#include <stan/math/error_handling.hpp>
#include <stan/math/matrix_error_handling.hpp>
#include <stan/math/error_handling.hpp>
#include <stan/prob/constants.hpp>
#include <stan/math/special_functions.hpp>


namespace stan {

  namespace prob {
    // Multinomial(ns|N,theta)   [0 <= n <= N;  SUM ns = N;   
    //                            0 <= theta[n] <= 1;  SUM theta = 1]
    template <bool propto,
              typename T_prob, 
              class Policy>
    typename boost::math::tools::promote_args<T_prob>::type
    multinomial_log(const std::vector<int>& ns,
                    const Eigen::Matrix<T_prob,Eigen::Dynamic,1>& theta, 
                    const Policy&) {
      static const char* function = "stan::prob::multinomial_log(%1%)";

      using stan::math::check_nonnegative;
      using stan::math::check_simplex;
      using stan::math::check_size_match;
      using boost::math::tools::promote_args;

      typename promote_args<T_prob>::type lp(0.0);
      if (!check_nonnegative(function, ns, "Number of trials variable", &lp, Policy()))
        return lp;
      if (!check_simplex(function, theta, "Probabilites parameter", 
                         &lp, Policy()))
        return lp;
      if (!check_size_match(function, 
          ns.size(), "Size of number of trials variable",
          theta.rows(), "rows of probabilities parameter",
          &lp, Policy()))
        return lp;
      using stan::math::multiply_log;

      if (include_summand<propto>::value) {     
        double sum = 1.0;
        for (unsigned int i = 0; i < ns.size(); ++i) 
          sum += ns[i];
        lp += lgamma(sum);
        for (unsigned int i = 0; i < ns.size(); ++i)
          lp -= lgamma(ns[i] + 1.0);
      }
      if (include_summand<propto,T_prob>::value)
        for (unsigned int i = 0; i < ns.size(); ++i)
          lp += multiply_log(ns[i], theta[i]);
      return lp;
    }


    template <bool propto,
              typename T_prob>
    typename boost::math::tools::promote_args<T_prob>::type
    multinomial_log(const std::vector<int>& ns,
                    const Eigen::Matrix<T_prob,Eigen::Dynamic,1>& theta) {
      return multinomial_log<propto>(ns,theta,stan::math::default_policy());
    }

    template <typename T_prob, 
              class Policy>
    typename boost::math::tools::promote_args<T_prob>::type
    multinomial_log(const std::vector<int>& ns,
                    const Eigen::Matrix<T_prob,Eigen::Dynamic,1>& theta, 
                    const Policy&) {
      return multinomial_log<false>(ns,theta,Policy());
    }

    template <typename T_prob>
    typename boost::math::tools::promote_args<T_prob>::type
    multinomial_log(const std::vector<int>& ns,
                    const Eigen::Matrix<T_prob,Eigen::Dynamic,1>& theta) {
      return multinomial_log<false>(ns,theta,stan::math::default_policy());
    }

    template <class RNG>
    inline Eigen::VectorXd
    multinomial_rng(const Eigen::Matrix<double,Eigen::Dynamic,1>& theta,
		    int N,
		    RNG& rng) {
      using boost::variate_generator;
      using boost::uniform_01;
      variate_generator<RNG&, uniform_01<> >
	uniform01_rng(rng, uniform_01<>());
      
     Eigen::VectorXd index(theta.rows());
     Eigen::VectorXd result(theta.rows());
     for(int i = 0; i < theta.rows(); i++)
       {
	 index(i) = 0;
	 result(i) = 0;
       }

      for(int i = 0; i < theta.rows(); i++)
	{
	  for(int j = i; j < theta.rows(); j++)
	    index(j) += theta(i,0);
	}

      int count = 0;
      while(count < N)
	{
	  double c = uniform01_rng();
	  int b = 0;
	  while(c > index(b,0))
	    b++;
	  result[b]++;
	  count++;
	}
      return result;
    }
  }
}
#endif
