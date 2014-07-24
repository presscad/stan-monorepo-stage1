#include <stan/prob/distributions/univariate/continuous/pareto_type_2.hpp>
#include <gtest/gtest.h>
#include <boost/random/mersenne_twister.hpp>
#include <boost/math/distributions.hpp>


TEST(ProbDistributionsParetoType2, chiSquareGoodnessFitTest) {
  boost::random::mt19937 rng;
  int N = 10000;
  int K = boost::math::round(2 * std::pow(N, 0.4));
  boost::math::chi_squared mydist(K-1);

  double mu = 3.0;
  double lambda = 2.0;
  double alpha = 4.0;

  double loc[K - 1];
  for(int i = 1; i < K; i++)
    loc[i - 1] = (std::pow(1.0 - i * std::pow(K, -1.0),-1.0 
                           / alpha) - 1.0) * lambda + mu;

  int count = 0;
  int bin [K];
  double expect [K];
  for(int i = 0 ; i < K; i++) {
    bin[i] = 0;
    expect[i] = N / K;
  }

  while (count < N) {
    double a = stan::prob::pareto_type_2_rng(mu, lambda, alpha,rng);
    int i = 0;
    while (i < K-1 && a > loc[i]) 
      ++i;
    ++bin[i];
    count++;
   }

  double chi = 0;

  for(int j = 0; j < K; j++)
    chi += ((bin[j] - expect[j]) * (bin[j] - expect[j]) / expect[j]);

  EXPECT_TRUE(chi < quantile(complement(mydist, 1e-6)));
}
