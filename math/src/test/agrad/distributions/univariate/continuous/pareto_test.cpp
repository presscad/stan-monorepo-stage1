#define _LOG_PROB_ pareto_log
#include <stan/prob/distributions/univariate/continuous/pareto.hpp>

#include <test/agrad/distributions/distribution_test_fixture.hpp>
#include <test/agrad/distributions/distribution_tests_3_params.hpp>

using std::vector;
using std::numeric_limits;
using stan::agrad::var;

class AgradDistributionsPareto : public AgradDistributionTest {
public:
  void valid_values(vector<vector<double> >& parameters) {
    vector<double> param(3);

    param[0] = 1.5;           // y
    param[1] = 0.5;           // y_min
    param[2] = 2.0;           // alpha
    parameters.push_back(param);

    param[0] = 19.5;          // y
    param[1] = 0.15;          // y_min
    param[2] = 5.0;           // alpha
    parameters.push_back(param);
  }
 
  void invalid_values(vector<size_t>& index, 
		      vector<double>& value) {
    // y
    
    // y_min
    index.push_back(1U);
    value.push_back(0.0);

    index.push_back(1U);
    value.push_back(-1.0);

    index.push_back(1U);
    value.push_back(numeric_limits<double>::infinity());

    index.push_back(1U);
    value.push_back(-numeric_limits<double>::infinity());

    // alpha
    index.push_back(2U);
    value.push_back(0.0);

    index.push_back(2U);
    value.push_back(-1.0);

    index.push_back(2U);
    value.push_back(numeric_limits<double>::infinity());

    index.push_back(2U);
    value.push_back(-numeric_limits<double>::infinity());
  }

  template <class T_y, class T_scale, class T_shape,
	    typename T3, typename T4, typename T5, 
	    typename T6, typename T7, typename T8, typename T9>
  var log_prob(const T_y& y, const T_scale& y_min, const T_shape& alpha,
	       const T3&, const T4&, const T5&, 
	       const T6&, const T7&, const T8&, const T9&) {
      using stan::math::multiply_log;
      using stan::prob::include_summand;
      using stan::prob::LOG_ZERO;

      var logp(0);
      if (include_summand<true,T_y,T_scale>::value)
	if (y < y_min)
	  return LOG_ZERO;
      if (include_summand<true,T_shape>::value)
	logp += log(alpha);
      if (include_summand<true,T_scale,T_shape>::value)
	logp += multiply_log(alpha, y_min);
      if (include_summand<true,T_y,T_shape>::value)
	logp -= multiply_log(alpha+1.0, y);
      return logp;
  }

};

INSTANTIATE_TYPED_TEST_CASE_P(AgradDistributionsPareto,
			      AgradDistributionTestFixture,
			      AgradDistributionsPareto);
INSTANTIATE_TYPED_TEST_CASE_P(AgradDistributionsPareto,
			      AgradDistributionTestFixture2,
			      AgradDistributionsPareto);
