#ifndef __TEST__AGRAD__DISTRIBUTIONS__DISTRIBUTION_TESTS_2_DISCRETE_1_PARAM_HPP___
#define __TEST__AGRAD__DISTRIBUTIONS__DISTRIBUTION_TESTS_2_DISCRETE_1_PARAM_HPP___

// i: int
// v: var
// d: double
// I: vector<int>
// V: vector<var>
// D: vector<double>

template<class T0, class T1, class T2, class T3,
	 class T4, class T5, class T6,
	 class T7, class T8, class T9>
class CALL_LOG_PROB {
public:
  var call(T0& p0, T1& p1, T2& p2, T3&, T4&, T5&, T6&, T7&, T8&, T9&) {
    return _LOG_PROB_<true>(p0, p1, p2);
  }
  var call_nopropto(T0& p0, T1& p1, T2& p2, T3&, T4&, T5&, T6&, T7&, T8&, T9&) {
    return _LOG_PROB_<false>(p0, p1, p2);
  }
};

TYPED_TEST_P(AgradDistributionTestFixture, call_all_versions) {
  vector<double> parameters = this->first_valid_params();

  int param0, param1;
  var param2;
  var logprob;
  param0 = parameters[0];
  param1 = parameters[1];
  param2 = parameters[2];
  
  EXPECT_NO_THROW(logprob = _LOG_PROB_<true>(param0, param1, param2));
  EXPECT_NO_THROW(logprob = _LOG_PROB_<false>(param0, param1, param2));
  EXPECT_NO_THROW(logprob = _LOG_PROB_<true>(param0, param1, param2, errno_policy()));
  EXPECT_NO_THROW(logprob = _LOG_PROB_<false>(param0, param1, param2, errno_policy()));
  EXPECT_NO_THROW(logprob = _LOG_PROB_(param0, param1, param2));
  EXPECT_NO_THROW(logprob = _LOG_PROB_(param0, param1, param2, errno_policy()));
}

TYPED_TEST_P(AgradDistributionTestFixture, check_valid_iid) {
  test_valid<TypeParam, int, int, double>();
}
TYPED_TEST_P(AgradDistributionTestFixture, check_valid_iiv) {
  test_valid<TypeParam, int, int, var>();
}
TYPED_TEST_P(AgradDistributionTestFixture, check_invalid_iid) {
  test_invalid<TypeParam, int, int, double>();
}
TYPED_TEST_P(AgradDistributionTestFixture, check_invalid_iiv) {
  test_invalid<TypeParam, int, int, var>();
}
TYPED_TEST_P(AgradDistributionTestFixture, logprob_propto_iid) {
  test_propto<TypeParam, int, int, double>();
}
TYPED_TEST_P(AgradDistributionTestFixture, logprob_propto_iiv) {
  test_propto<TypeParam, int, int, var>();
}
TYPED_TEST_P(AgradDistributionTestFixture, gradient_finite_diff_iid) {
  test_finite_diff<TypeParam, int, int, double>();
}
TYPED_TEST_P(AgradDistributionTestFixture, gradient_finite_diff_iiv) {
  test_finite_diff<TypeParam, int, int, var>();
}
TYPED_TEST_P(AgradDistributionTestFixture, gradient_function_iid) {
  test_gradient_function<TypeParam, int, int, double>();
}
TYPED_TEST_P(AgradDistributionTestFixture, gradient_function_iiv) {
  test_gradient_function<TypeParam, int, int, var>();
}
TYPED_TEST_P(AgradDistributionTestFixture, vectorized_iid) {
  test_vectorized<TypeParam, int, int, double>();
}
TYPED_TEST_P(AgradDistributionTestFixture, vectorized_iiv) {
  test_vectorized<TypeParam, int, int, var>();
}
TYPED_TEST_P(AgradDistributionTestFixture, vectorized_iiD) {
  test_vectorized<TypeParam, int, int, vector<double> >();
}
TYPED_TEST_P(AgradDistributionTestFixture, vectorized_iiV) {
  test_vectorized<TypeParam, int, int, vector<var> >();
}
TYPED_TEST_P(AgradDistributionTestFixture, vectorized_iId) {
  test_vectorized<TypeParam, int, vector<int>, double>();
}
TYPED_TEST_P(AgradDistributionTestFixture, vectorized_iIv) {
  test_vectorized<TypeParam, int, vector<int>, var>();
}
TYPED_TEST_P(AgradDistributionTestFixture, vectorized_iID) {
  test_vectorized<TypeParam, int, vector<int>, vector<double> >();
}
TYPED_TEST_P(AgradDistributionTestFixture, vectorized_iIV) {
  test_vectorized<TypeParam, int, vector<int>, vector<var> >();
}
TYPED_TEST_P(AgradDistributionTestFixture, vectorized_Iid) {
  test_vectorized<TypeParam, vector<int>, int, double>();
}
TYPED_TEST_P(AgradDistributionTestFixture, vectorized_Iiv) {
  test_vectorized<TypeParam, vector<int>, int, var>();
}
TYPED_TEST_P(AgradDistributionTestFixture, vectorized_IiD) {
  test_vectorized<TypeParam, vector<int>, int, vector<double> >();
}
TYPED_TEST_P(AgradDistributionTestFixture, vectorized_IiV) {
  test_vectorized<TypeParam, vector<int>, int, vector<var> >();
}
TYPED_TEST_P(AgradDistributionTestFixture, vectorized_IId) {
  test_vectorized<TypeParam, vector<int>, vector<int>, double>();
}
TYPED_TEST_P(AgradDistributionTestFixture, vectorized_IIv) {
  test_vectorized<TypeParam, vector<int>, vector<int>, var>();
}
TYPED_TEST_P(AgradDistributionTestFixture, vectorized_IID) {
  test_vectorized<TypeParam, vector<int>, vector<int>, vector<double> >();
}
TYPED_TEST_P(AgradDistributionTestFixture, vectorized_IIV) {
  test_vectorized<TypeParam, vector<int>, vector<int>, vector<var> >();
}

REGISTER_TYPED_TEST_CASE_P(AgradDistributionTestFixture,
			   call_all_versions,
			   check_valid_iid,
			   check_valid_iiv,
			   check_invalid_iid,
			   check_invalid_iiv,
			   logprob_propto_iid,
			   logprob_propto_iiv,
			   gradient_finite_diff_iid,
			   gradient_finite_diff_iiv,
			   gradient_function_iid,
			   gradient_function_iiv,
			   vectorized_iid,
			   vectorized_iiv,
			   vectorized_iiD,
			   vectorized_iiV,
			   vectorized_iId,
			   vectorized_iIv,
			   vectorized_iID,
			   vectorized_iIV,
			   vectorized_Iid,
			   vectorized_Iiv,
			   vectorized_IiD,
			   vectorized_IiV,
			   vectorized_IId,			   
			   vectorized_IIv,
			   vectorized_IID,
			   vectorized_IIV);
#endif
