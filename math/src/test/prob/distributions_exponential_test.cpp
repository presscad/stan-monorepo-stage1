// These tests should not have reference to stan::agrad::var. Distribution tests 
// with stan::agrad::var should be placed in src/test/agrad/distributions_test.cpp

#include <cmath>
#include <gtest/gtest.h>
#include "stan/prob/distributions_exponential.hpp"

TEST(ProbDistributions,Exponential) {
  EXPECT_FLOAT_EQ(-2.594535, stan::prob::exponential_log(2.0,1.5));
  EXPECT_FLOAT_EQ(-57.13902, stan::prob::exponential_log(15.0,3.9));
}


TEST(ProbDistributionsCumulative,Exponential) {
  // values from R
  EXPECT_FLOAT_EQ(0.95021293, stan::prob::exponential_p(2.0,1.5));
  EXPECT_FLOAT_EQ(0.0, stan::prob::exponential_p(0,1.5));
  EXPECT_FLOAT_EQ(1.0, stan::prob::exponential_p(15.0,3.9));
  EXPECT_FLOAT_EQ(0.62280765, stan::prob::exponential_p(0.25,3.9));
}

/*TEST(ProbDistributionsTruncated,ExponentialLowHigh) {

  FAIL();
  }*/

TEST(ProbDistributionsTruncated,ExponentialLow) {
  double x, beta, low;
  
  x = 1.0;
  beta = 1.5;
  low = 2.0;
  EXPECT_FLOAT_EQ(log(0.0), stan::prob::exponential_trunc_l_log(x, beta, low));
  
  x = 1.5;
  EXPECT_FLOAT_EQ(log(0.0), stan::prob::exponential_trunc_l_log(x, beta, low));

  x = 2.0;
  EXPECT_FLOAT_EQ(0.4054651, stan::prob::exponential_trunc_l_log(x, beta, low));

  x = 3.0;
  EXPECT_FLOAT_EQ(-1.094535, stan::prob::exponential_trunc_l_log(x, beta, low));
  
  x = 5.0;
  EXPECT_FLOAT_EQ(-4.094535, stan::prob::exponential_trunc_l_log(x, beta, low));
}
TEST(ProbDistributionsTruncated,ExponentialLowDefaultPolicyX) {
  double x, beta, low;
  x = 1.0;
  beta = 1.5;
  low = 2.0;
  EXPECT_NO_THROW(stan::prob::exponential_trunc_l_log(x, beta, low));
  x = 0.0;
  EXPECT_NO_THROW(stan::prob::exponential_trunc_l_log(x, beta, low));
  x = -10.0;
  EXPECT_NO_THROW(stan::prob::exponential_trunc_l_log(x, beta, low));
  
  x = std::numeric_limits<double>::quiet_NaN();
  EXPECT_THROW(stan::prob::exponential_trunc_l_log(x, beta, low), std::domain_error);
  
  x = std::numeric_limits<double>::infinity();
  EXPECT_THROW(stan::prob::exponential_trunc_l_log(x, beta, low), std::domain_error);
  
  x = -std::numeric_limits<double>::infinity();
  EXPECT_THROW(stan::prob::exponential_trunc_l_log(x, beta, low), std::domain_error);
}
TEST(ProbDistributionsTruncated,ExponentialLowDefaultPolicyBeta) {
  double x, beta, low;
  x = 1.0;
  beta = 1.5;
  low = 2.0;
  EXPECT_NO_THROW(stan::prob::exponential_trunc_l_log(x, beta, low));
  beta = 0.1;
  EXPECT_NO_THROW(stan::prob::exponential_trunc_l_log(x, beta, low));
  
  beta = 0.0;
  EXPECT_THROW(stan::prob::exponential_trunc_l_log(x, beta, low), std::domain_error) <<
    "beta = 0 should throw error";
  
  beta = -1.0;
  EXPECT_THROW(stan::prob::exponential_trunc_l_log(x, beta, low), std::domain_error) <<
    "beta < 0 should throw error";

  beta = std::numeric_limits<double>::quiet_NaN();
  EXPECT_THROW(stan::prob::exponential_trunc_l_log(x, beta, low), std::domain_error);
  
  beta = std::numeric_limits<double>::infinity();
  EXPECT_THROW(stan::prob::exponential_trunc_l_log(x, beta, low), std::domain_error);
  
  beta = -std::numeric_limits<double>::infinity();
  EXPECT_THROW(stan::prob::exponential_trunc_l_log(x, beta, low), std::domain_error);
}
TEST(ProbDistributionsTruncated,ExponentialLowDefaultPolicyLow) {
  double x, beta, low;
  x = 1.0;
  beta = 1.5;
  low = 2.0;
  EXPECT_NO_THROW(stan::prob::exponential_trunc_l_log(x, beta, low));
  low = 0.1;
  EXPECT_NO_THROW(stan::prob::exponential_trunc_l_log(x, beta, low));
  low = 0.0;
  EXPECT_NO_THROW(stan::prob::exponential_trunc_l_log(x, beta, low)) <<
    "low = 0 should not throw an error";

  low = -1.0;
  EXPECT_THROW(stan::prob::exponential_trunc_l_log(x, beta, low), std::domain_error) <<
    "low < 0 should throw error";
  low = std::numeric_limits<double>::quiet_NaN();
  EXPECT_THROW(stan::prob::exponential_trunc_l_log(x, beta, low), std::domain_error);
  low = std::numeric_limits<double>::infinity();
  EXPECT_THROW(stan::prob::exponential_trunc_l_log(x, beta, low), std::domain_error);
  low = -std::numeric_limits<double>::infinity();
  EXPECT_THROW(stan::prob::exponential_trunc_l_log(x, beta, low), std::domain_error);
}  

/*TEST(ProbDistributionsTruncated,ExponentialHigh) {
  FAIL();
  }*/

