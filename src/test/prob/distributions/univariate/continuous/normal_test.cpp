#include <test/prob/distributions/distribution_test_fixture.hpp>
#include <stan/prob/distributions/univariate/continuous/normal.hpp>

using std::vector;
using std::numeric_limits;

/*template <typename... Args>
double log_prob(Args&&... args) {
  return stan::prob::normal_log<false>(args...);
  }*/



template <typename T1, typename T2, typename T3, class Policy>
double log_prob(const T1& y,
		const T2& mu, 
		const T3& sigma,
		Policy&) {
  return stan::prob::normal_log<false>(y, mu, sigma, Policy());
}


class ProbDistributionsNormal : public DistributionTest {
public:
  // need this to resolve functions
  //using DistributionTest::log_prob;
  

  void valid_values(vector<vector<double> >& parameters,
		    vector<double>& log_prob) {
    vector<double> param(3);

    param[0] = 0;           // y
    param[1] = 0;           // mu
    param[2] = 1;           // sigma
    parameters.push_back(param);
    log_prob.push_back(-0.9189385); // expected log_prob

    param[0] = 1;           // y
    param[1] = 0;           // mu
    param[2] = 1;           // sigma
    parameters.push_back(param);
    log_prob.push_back(-1.418939); // expected log_prob

    param[0] = -2;          // y
    param[1] = 0;           // mu
    param[2] = 1;           // sigma
    parameters.push_back(param);
    log_prob.push_back(-2.918939); // expected log_prob

    param[0] = -3.5;          // y
    param[1] = 1.9;           // mu
    param[2] = 7.2;           // sigma
    parameters.push_back(param);
    log_prob.push_back(-3.174270); // expected log_prob
  }
 
  void invalid_values(vector<size_t>& index, 
		      vector<double>& value) {
    // y
    
    // mu
    index.push_back(1U);
    value.push_back(numeric_limits<double>::infinity());

    index.push_back(1U);
    value.push_back(-numeric_limits<double>::infinity());

    // sigma
    index.push_back(2U);
    value.push_back(0.0);

    index.push_back(2U);
    value.push_back(-1.0);
  }

};

INSTANTIATE_TYPED_TEST_CASE_P(ProbDistributionsNormal,
			      DistributionTestFixture,
			      ProbDistributionsNormal);
