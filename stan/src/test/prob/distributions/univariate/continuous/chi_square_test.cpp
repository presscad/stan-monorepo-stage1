#define _LOG_PROB_ chi_square_log
#include <stan/prob/distributions/univariate/continuous/chi_square.hpp>

#include <test/prob/distributions/distribution_test_fixture.hpp>
#include <test/prob/distributions/distribution_tests_2_params.hpp>

using std::vector;
using std::numeric_limits;

class ProbDistributionsChiSquare : public DistributionTest {
public:
  void valid_values(vector<vector<double> >& parameters,
		    vector<double>& log_prob) {
    vector<double> param(2);

    param[0] = 7.9;                 // y
    param[1] = 3.0;                 // nu
    parameters.push_back(param);
    log_prob.push_back(-3.835507);  // expected log_prob

    param[0] = 1.9;                 // y
    param[1] = 0.5;                 // nu
    parameters.push_back(param);
    log_prob.push_back(-2.8927);    // expected log_prob
  }
 
  void invalid_values(vector<size_t>& index, 
		      vector<double>& value) {
    // y
    
    // nu
    index.push_back(1U);
    value.push_back(0.0);

    index.push_back(1U);
    value.push_back(-1.0);

    index.push_back(1U);
    value.push_back(numeric_limits<double>::infinity());
  }
};

INSTANTIATE_TYPED_TEST_CASE_P(ProbDistributionsChiSquare,
			      DistributionTestFixture,
			      ProbDistributionsChiSquare);

/*
// FIXME: include when chi_square_cdf is implemented
TEST(ProbDistributionsChiSquare,Cumulative) {
  using stan::prob::chi_square_cdf;
  EXPECT_FLOAT_EQ(0.9518757, chi_square_cdf(7.9,3.0));
  EXPECT_FLOAT_EQ(0.9267752, chi_square_cdf(1.9,0.5));
  }
*/
