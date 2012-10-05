#define _LOG_PROB_ chi_square_log
#include <stan/prob/distributions/univariate/continuous/chi_square.hpp>

#include <test/agrad/distributions/distribution_test_fixture.hpp>
#include <test/agrad/distributions/distribution_tests_2_params.hpp>

using std::vector;
using std::numeric_limits;
using stan::agrad::var;

class AgradDistributionsChiSquare : public AgradDistributionTest {
public:
  void valid_values(vector<vector<double> >& parameters) {
    vector<double> param(2);
	       
    param[0] = 7.9;                 // y
    param[1] = 3.0;                 // nu
    parameters.push_back(param);

    param[0] = 1.9;                 // y
    param[1] = 0.5;                 // nu
    parameters.push_back(param);
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

  template <class T_y, class T_dof>
  var log_prob(const T_y& y, const T_dof& nu) {
    using stan::prob::include_summand;
    using stan::math::multiply_log;
    using boost::math::lgamma;
    using stan::prob::NEG_LOG_TWO_OVER_TWO;
    
    var logp(0);
    if (include_summand<true,T_dof>::value)
      logp += nu * NEG_LOG_TWO_OVER_TWO - lgamma(0.5 * nu);
    if (include_summand<true,T_y,T_dof>::value)
      logp += multiply_log(0.5*nu-1.0, y);
    if (include_summand<true,T_y>::value)
      logp -= 0.5 * y;
    return logp;
  }
};

INSTANTIATE_TYPED_TEST_CASE_P(AgradDistributionsChiSquare,
			      AgradDistributionTestFixture,
			      AgradDistributionsChiSquare);
