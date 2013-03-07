#include <gtest/gtest.h>
#include <stan/prob/distributions/multivariate/continuous/dirichlet.hpp>
#include <boost/random/mersenne_twister.hpp>
#include<boost/math/distributions.hpp>

using Eigen::Dynamic;
using Eigen::Matrix;

TEST(ProbDistributions,Dirichlet) {
  Matrix<double,Dynamic,1> theta(3,1);
  theta << 0.2, 0.3, 0.5;
  Matrix<double,Dynamic,1> alpha(3,1);
  alpha << 1.0, 1.0, 1.0;
  EXPECT_FLOAT_EQ(0.6931472, stan::prob::dirichlet_log(theta,alpha));
  
  Matrix<double,Dynamic,1> theta2(4,1);
  theta2 << 0.01, 0.01, 0.8, 0.18;
  Matrix<double,Dynamic,1> alpha2(4,1);
  alpha2 << 10.5, 11.5, 19.3, 5.1;
  EXPECT_FLOAT_EQ(-43.40045, stan::prob::dirichlet_log(theta2,alpha2));
}

TEST(ProbDistributions,DirichletPropto) {
  Matrix<double,Dynamic,1> theta(3,1);
  theta << 0.2, 0.3, 0.5;
  Matrix<double,Dynamic,1> alpha(3,1);
  alpha << 1.0, 1.0, 1.0;
  EXPECT_FLOAT_EQ(0.0, stan::prob::dirichlet_log<true>(theta,alpha));
  
  Matrix<double,Dynamic,1> theta2(4,1);
  theta2 << 0.01, 0.01, 0.8, 0.18;
  Matrix<double,Dynamic,1> alpha2(4,1);
  alpha2 << 10.5, 11.5, 19.3, 5.1;
  EXPECT_FLOAT_EQ(0.0, stan::prob::dirichlet_log<true>(theta2,alpha2));
}

TEST(ProbDistributionsDirichlet, random) {
  boost::random::mt19937 rng;
  Matrix<double,Dynamic,Dynamic> alpha(3,1);
  alpha << 2.0, 
    3.0,
    11.0;

  EXPECT_NO_THROW(stan::prob::dirichlet_rng(alpha,rng));
}

//more extensive test could entail testing each set of values in position i as if it were a gamma distribution but you have to scale by dividing by sum of i's first.
