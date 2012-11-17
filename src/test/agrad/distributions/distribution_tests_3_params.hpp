#ifndef __TEST__AGRAD__DISTRIBUTIONS__DISTRIBUTION_TESTS_3_PARAMS_HPP___
#define __TEST__AGRAD__DISTRIBUTIONS__DISTRIBUTION_TESTS_3_PARAMS_HPP___

// v: var
// d: double
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
  ASSERT_EQ(parameters.size(), 3U);

  var param1, param2, param3;
  var logprob;
  param1 = parameters[0];
  param2 = parameters[1];
  param3 = parameters[2];
  
  EXPECT_NO_THROW(logprob = _LOG_PROB_<true>(param1, param2, param3));
  EXPECT_NO_THROW(logprob = _LOG_PROB_<false>(param1, param2, param3));
  EXPECT_NO_THROW(logprob = _LOG_PROB_<true>(param1, param2, param3, errno_policy()));
  EXPECT_NO_THROW(logprob = _LOG_PROB_<false>(param1, param2, param3, errno_policy()));
  EXPECT_NO_THROW(logprob = _LOG_PROB_(param1, param2, param3));
  EXPECT_NO_THROW(logprob = _LOG_PROB_(param1, param2, param3, errno_policy()));
}

TYPED_TEST_P(AgradDistributionTestFixture, check_valid_ddd) {
  test_valid<TypeParam, double, double, double >();
}
TYPED_TEST_P(AgradDistributionTestFixture, check_valid_ddv) {
  test_valid<TypeParam, double, double, var >();
}
TYPED_TEST_P(AgradDistributionTestFixture, check_valid_dvd) {
  test_valid<TypeParam, double, var, double >();
}
TYPED_TEST_P(AgradDistributionTestFixture, check_valid_dvv) {
  test_valid<TypeParam, double, var, var >();
}
TYPED_TEST_P(AgradDistributionTestFixture, check_valid_vdd) {
  test_valid<TypeParam, var, double, double >();
}
TYPED_TEST_P(AgradDistributionTestFixture, check_valid_vdv) {
  test_valid<TypeParam, var, double, var >();
}
TYPED_TEST_P(AgradDistributionTestFixture, check_valid_vvd) {
  test_valid<TypeParam, var, var, double >();
}
TYPED_TEST_P(AgradDistributionTestFixture, check_valid_vvv) {
  test_valid<TypeParam, var, var, var >();
}
TYPED_TEST_P(AgradDistributionTestFixture, check_invalid_ddd) {
  test_invalid<TypeParam, double, double, double>();
}
TYPED_TEST_P(AgradDistributionTestFixture, check_invalid_ddv) {
  test_invalid<TypeParam, double, double, var>();
}
TYPED_TEST_P(AgradDistributionTestFixture, check_invalid_dvd) {  
  test_invalid<TypeParam, double, var, double>();
}
TYPED_TEST_P(AgradDistributionTestFixture, check_invalid_dvv) {  
  test_invalid<TypeParam, double, var, var>();
}
TYPED_TEST_P(AgradDistributionTestFixture, check_invalid_vdd) {
  test_invalid<TypeParam, var, double, double>();
}
TYPED_TEST_P(AgradDistributionTestFixture, check_invalid_vdv) {  
  test_invalid<TypeParam, var, double, var>();
}
TYPED_TEST_P(AgradDistributionTestFixture, check_invalid_vvd) {
  test_invalid<TypeParam, var, var, double>();
}
TYPED_TEST_P(AgradDistributionTestFixture, check_invalid_vvv) {
  test_invalid<TypeParam, var, var, var>();
}
TYPED_TEST_P(AgradDistributionTestFixture, logprob_propto_ddd) {
  test_propto<TypeParam, double, double, double>();
}
TYPED_TEST_P(AgradDistributionTestFixture, logprob_propto_ddv) {
  test_propto<TypeParam, double, double, var>();
}
TYPED_TEST_P(AgradDistributionTestFixture, logprob_propto_dvd) {
  test_propto<TypeParam, double, var, double>();
}
TYPED_TEST_P(AgradDistributionTestFixture, logprob_propto_dvv) { 
  test_propto<TypeParam, double, var, var>();
}
TYPED_TEST_P(AgradDistributionTestFixture, logprob_propto_vdd) { 
  test_propto<TypeParam, var, double, double>();
}
TYPED_TEST_P(AgradDistributionTestFixture, logprob_propto_vdv) {
  test_propto<TypeParam, var, double, var>();
}
TYPED_TEST_P(AgradDistributionTestFixture, logprob_propto_vvd) { 
  test_propto<TypeParam, var, var, double>();
}
TYPED_TEST_P(AgradDistributionTestFixture, logprob_propto_vvv) { 
  test_propto<TypeParam, var, var, var>();
}
TYPED_TEST_P(AgradDistributionTestFixture, gradient_finite_diff_ddd) {
  SUCCEED() << "No op for all double" << std::endl;
}
TYPED_TEST_P(AgradDistributionTestFixture, gradient_finite_diff_ddv) {
  vector<vector<double> > parameters;
  TypeParam().valid_values(parameters);
  ASSERT_GT(parameters.size(), 0U);
  double e = this->e();
  double e_times_2 = (2.0 * e);
  for (size_t n = 0; n < parameters.size(); n++) {
    vector<double> p(parameters[n]);
    double diff_g2 = (_LOG_PROB_<false>(p[0], p[1], p[2]+e) - _LOG_PROB_<false>(p[0], p[1], p[2]-e)) / e_times_2;
      
    var p2(p[2]);
    var lp = _LOG_PROB_<true>(p[0], p[1], p2);
    vector<var> v_params(1);
    v_params[0] = p2;
    vector<double> gradients;
    lp.grad(v_params, gradients);

    EXPECT_NEAR(diff_g2,
		gradients[0],
		1e-4)
      << "Index: " << n << " - Finite diff test failed for parameter 2" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;


  }
}
TYPED_TEST_P(AgradDistributionTestFixture, gradient_finite_diff_dvd) {
  vector<vector<double> > parameters;
  TypeParam().valid_values(parameters);
  ASSERT_GT(parameters.size(), 0U);
  double e = this->e();
  double e_times_2 = (2.0 * e);
  for (size_t n = 0; n < parameters.size(); n++) {
    vector<double> p(parameters[n]);
    double diff_g1 = (_LOG_PROB_<false>(p[0], p[1]+e, p[2]) - _LOG_PROB_<false>(p[0], p[1]-e, p[2])) / e_times_2;
      
    var p1(p[1]);
    var lp = _LOG_PROB_<true>(p[0], p1, p[2]);
    vector<var> v_params(1);
    v_params[0] = p1;
    vector<double> gradients;
    lp.grad(v_params, gradients);

    EXPECT_NEAR(diff_g1,
		gradients[0],
		1e-4)
      << "Index: " << n << " - Finite diff test failed for parameter 1" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
    
  }
}
TYPED_TEST_P(AgradDistributionTestFixture, gradient_finite_diff_dvv) {
  vector<vector<double> > parameters;
  TypeParam().valid_values(parameters);
  ASSERT_GT(parameters.size(), 0U);
  double e = this->e();
  double e_times_2 = (2.0 * e);
  for (size_t n = 0; n < parameters.size(); n++) {
    vector<double> p(parameters[n]);
    double diff_g1 = (_LOG_PROB_<false>(p[0], p[1]+e, p[2]) - _LOG_PROB_<false>(p[0], p[1]-e, p[2])) / e_times_2;
    double diff_g2 = (_LOG_PROB_<false>(p[0], p[1], p[2]+e) - _LOG_PROB_<false>(p[0], p[1], p[2]-e)) / e_times_2;
      
    var p1(p[1]);
    var p2(p[2]);
    
    var lp = _LOG_PROB_<true>(p[0], p1, p2);
    vector<var> v_params(2);
    v_params[0] = p1;
    v_params[1] = p2;
    vector<double> gradients;
    lp.grad(v_params, gradients);

    EXPECT_NEAR(diff_g1,
		gradients[0],
		1e-4)
      << "Index: " << n << " - Finite diff test failed for parameter 1" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
    EXPECT_NEAR(diff_g2,
		gradients[1],
		1e-4)
      << "Index: " << n << " - Finite diff test failed for parameter 2" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
  }
}
TYPED_TEST_P(AgradDistributionTestFixture, gradient_finite_diff_vdd) {  
  vector<vector<double> > parameters;
  TypeParam().valid_values(parameters);
  ASSERT_GT(parameters.size(), 0U);
  double e = this->e();
  double e_times_2 = (2.0 * e);
  for (size_t n = 0; n < parameters.size(); n++) {
    vector<double> p(parameters[n]);
    double diff_g0 = (_LOG_PROB_<false>(p[0]+e, p[1], p[2]) - _LOG_PROB_<false>(p[0]-e, p[1], p[2])) / e_times_2;
      
    var p0(p[0]);
    var lp = _LOG_PROB_<true>(p0, p[1], p[2]);
    vector<var> v_params(1);
    v_params[0] = p0;
    vector<double> gradients;
    lp.grad(v_params, gradients);

    EXPECT_NEAR(diff_g0,
		gradients[0],
		1e-4)
      << "Index: " << n << " - Finite diff test failed for parameter 0" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
  }
}
TYPED_TEST_P(AgradDistributionTestFixture, gradient_finite_diff_vdv) {
  vector<vector<double> > parameters;
  TypeParam().valid_values(parameters);
  ASSERT_GT(parameters.size(), 0U);
  double e = this->e();
  double e_times_2 = (2.0 * e);
  for (size_t n = 0; n < parameters.size(); n++) {
    vector<double> p(parameters[n]);
    double diff_g0 = (_LOG_PROB_<false>(p[0]+e, p[1], p[2]) - _LOG_PROB_<false>(p[0]-e, p[1], p[2])) / e_times_2;
    double diff_g2 = (_LOG_PROB_<false>(p[0], p[1], p[2]+e) - _LOG_PROB_<false>(p[0], p[1], p[2]-e)) / e_times_2;
      
    var p0(p[0]);
    var p2(p[2]);
    
    var lp = _LOG_PROB_<true>(p0, p[1], p2);
    vector<var> v_params(2);
    v_params[0] = p0;
    v_params[1] = p2;
    vector<double> gradients;
    lp.grad(v_params, gradients);

    EXPECT_NEAR(diff_g0,
		gradients[0],
		1e-4)
      << "Index: " << n << " - Finite diff test failed for parameter 0" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
    EXPECT_NEAR(diff_g2,
		gradients[1],
		1e-4)
      << "Index: " << n << " - Finite diff test failed for parameter 2" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
  }
}
TYPED_TEST_P(AgradDistributionTestFixture, gradient_finite_diff_vvd) {
  vector<vector<double> > parameters;
  TypeParam().valid_values(parameters);
  ASSERT_GT(parameters.size(), 0U);
  double e = this->e();
  double e_times_2 = (2.0 * e);
  for (size_t n = 0; n < parameters.size(); n++) {
    vector<double> p(parameters[n]);
    double diff_g0 = (_LOG_PROB_<false>(p[0]+e, p[1], p[2]) - _LOG_PROB_<false>(p[0]-e, p[1], p[2])) / e_times_2;
    double diff_g1 = (_LOG_PROB_<false>(p[0], p[1]+e, p[2]) - _LOG_PROB_<false>(p[0], p[1]-e, p[2])) / e_times_2;
      
    var p0(p[0]);
    var p1(p[1]);
    double p2(p[2]);
    
    var lp = _LOG_PROB_<true>(p0, p1, p2);
    vector<var> v_params(2);
    v_params[0] = p0;
    v_params[1] = p1;
    vector<double> gradients;
    lp.grad(v_params, gradients);

    EXPECT_NEAR(diff_g0,
		gradients[0],
		1e-4)
      << "Index: " << n << " - Finite diff test failed for parameter 0" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
    EXPECT_NEAR(diff_g1,
		gradients[1],
		1e-4)
      << "Index: " << n << " - Finite diff test failed for parameter 1" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
  }
}
TYPED_TEST_P(AgradDistributionTestFixture, gradient_finite_diff_vvv) {
  vector<vector<double> > parameters;
  TypeParam().valid_values(parameters);
  ASSERT_GT(parameters.size(), 0U);
  double e = this->e();
  double e_times_2 = (2.0 * e);
  for (size_t n = 0; n < parameters.size(); n++) {
    vector<double> p(parameters[n]);
    double diff_g0 = (_LOG_PROB_<false>(p[0]+e, p[1], p[2]) - _LOG_PROB_<false>(p[0]-e, p[1], p[2])) / e_times_2;
    double diff_g1 = (_LOG_PROB_<false>(p[0], p[1]+e, p[2]) - _LOG_PROB_<false>(p[0], p[1]-e, p[2])) / e_times_2;
    double diff_g2 = (_LOG_PROB_<false>(p[0], p[1], p[2]+e) - _LOG_PROB_<false>(p[0], p[1], p[2]-e)) / e_times_2;
      
    var p0(p[0]);
    var p1(p[1]);
    var p2(p[2]);
    
    var lp = _LOG_PROB_<true>(p0, p1, p2);
    vector<var> v_params(3);
    v_params[0] = p0;
    v_params[1] = p1;
    v_params[2] = p2;
    vector<double> gradients;
    lp.grad(v_params, gradients);

    EXPECT_NEAR(diff_g0,
		gradients[0],
		1e-4)
      << "Index: " << n << " - Finite diff test failed for parameter 0" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
    EXPECT_NEAR(diff_g1,
		gradients[1],
		1e-4)
      << "Index: " << n << " - Finite diff test failed for parameter 1" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
    EXPECT_NEAR(diff_g2,
		gradients[2],
		1e-4)
      << "Index: " << n << " - Finite diff test failed for parameter 2" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
  }
}
TYPED_TEST_P(AgradDistributionTestFixture, gradient_function_ddd) {
  SUCCEED() << "No op for (d,d,d) input" << std::endl;
}

TYPED_TEST_P(AgradDistributionTestFixture, gradient_function_ddv) {
  vector<vector<double> > parameters;
  TypeParam().valid_values(parameters);
  ASSERT_GT(parameters.size(), 0U);
  for (size_t n = 0; n < parameters.size(); n++) {
    vector<double> p(parameters[n]);
    var p2(p[2]);
    
    var lp = _LOG_PROB_<true>(p[0], p[1], p2);
    var expected_lp = TypeParam().log_prob(p[0], p[1], p2);
    vector<var> v_params(1);
    v_params[0] = p2;
    
    vector<double> gradients;
    lp.grad(v_params, gradients);
    vector<double> expected_gradients;
    expected_lp.grad(v_params, expected_gradients);
    
    EXPECT_FLOAT_EQ(expected_lp.val(),
		    lp.val())
      << "Index: " << n << " - function value test failed" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
    EXPECT_FLOAT_EQ(expected_gradients[0],
		    gradients[0])
      << "Index: " << n << " - hand-coded gradient test failed for parameter 2" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
  }
}
TYPED_TEST_P(AgradDistributionTestFixture, gradient_function_dvd) {  
  vector<vector<double> > parameters;
  TypeParam().valid_values(parameters);
  ASSERT_GT(parameters.size(), 0U);
  for (size_t n = 0; n < parameters.size(); n++) {
    vector<double> p(parameters[n]);
    var p1(p[1]);
    
    var lp = _LOG_PROB_<true>(p[0], p1, p[2]);
    var expected_lp = TypeParam().log_prob(p[0], p1, p[2]);
    vector<var> v_params(1);
    v_params[0] = p1;
    
    vector<double> gradients;
    lp.grad(v_params, gradients);
    vector<double> expected_gradients;
    expected_lp.grad(v_params, expected_gradients);
    
    EXPECT_FLOAT_EQ(expected_lp.val(),
		    lp.val())
      << "Index: " << n << " - function value test failed" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
    EXPECT_FLOAT_EQ(expected_gradients[0],
		    gradients[0])
      << "Index: " << n << " - hand-coded gradient test failed for parameter 1" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
  }
}
TYPED_TEST_P(AgradDistributionTestFixture, gradient_function_dvv) {  
  vector<vector<double> > parameters;
  TypeParam().valid_values(parameters);
  ASSERT_GT(parameters.size(), 0U);
  for (size_t n = 0; n < parameters.size(); n++) {
    vector<double> p(parameters[n]);
    var p1(p[1]);
    var p2(p[2]);
    
    var lp = _LOG_PROB_<true>(p[0], p1, p2);
    var expected_lp = TypeParam().log_prob(p[0], p1, p2);
    vector<var> v_params(2);
    v_params[0] = p1;
    v_params[1] = p2;
    
    vector<double> gradients;
    lp.grad(v_params, gradients);
    vector<double> expected_gradients;
    expected_lp.grad(v_params, expected_gradients);
    
    EXPECT_FLOAT_EQ(expected_lp.val(),
		    lp.val())
      << "Index: " << n << " - function value test failed" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
    EXPECT_FLOAT_EQ(expected_gradients[0],
		    gradients[0])
      << "Index: " << n << " - hand-coded gradient test failed for parameter 1" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
    EXPECT_FLOAT_EQ(expected_gradients[1],
		    gradients[1])
      << "Index: " << n << " - hand-coded gradient test failed for parameter 2" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
  }
}
TYPED_TEST_P(AgradDistributionTestFixture, gradient_function_vdd) {  
  vector<vector<double> > parameters;
  TypeParam().valid_values(parameters);
  ASSERT_GT(parameters.size(), 0U);
  for (size_t n = 0; n < parameters.size(); n++) {
    vector<double> p(parameters[n]);
    var p0(p[0]);
    
    var lp = _LOG_PROB_<true>(p0, p[1], p[2]);
    var expected_lp = TypeParam().log_prob(p0, p[1], p[2]);
    vector<var> v_params(1);
    v_params[0] = p0;
    
    vector<double> gradients;
    lp.grad(v_params, gradients);
    vector<double> expected_gradients;
    expected_lp.grad(v_params, expected_gradients);
    
    EXPECT_FLOAT_EQ(expected_lp.val(),
		    lp.val())
      << "Index: " << n << " - function value test failed" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
    EXPECT_FLOAT_EQ(expected_gradients[0],
		    gradients[0])
      << "Index: " << n << " - hand-coded gradient test failed for parameter 0" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
  }
}
TYPED_TEST_P(AgradDistributionTestFixture, gradient_function_vdv) {
  vector<vector<double> > parameters;
  TypeParam().valid_values(parameters);
  ASSERT_GT(parameters.size(), 0U);
  for (size_t n = 0; n < parameters.size(); n++) {
    vector<double> p(parameters[n]);
    var p0(p[0]);
    var p2(p[2]);
    
    var lp = _LOG_PROB_<true>(p0, p[1], p2);
    var expected_lp = TypeParam().log_prob(p0, p[1], p2);
    vector<var> v_params(2);
    v_params[0] = p0;
    v_params[1] = p2;
    
    vector<double> gradients;
    lp.grad(v_params, gradients);
    vector<double> expected_gradients;
    expected_lp.grad(v_params, expected_gradients);
    
    EXPECT_FLOAT_EQ(expected_lp.val(),
		    lp.val())
      << "Index: " << n << " - function value test failed" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
    EXPECT_FLOAT_EQ(expected_gradients[0],
		    gradients[0])
      << "Index: " << n << " - hand-coded gradient test failed for parameter 0" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
    EXPECT_FLOAT_EQ(expected_gradients[1],
		    gradients[1])
      << "Index: " << n << " - hand-coded gradient test failed for parameter 2" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
  }
}
TYPED_TEST_P(AgradDistributionTestFixture, gradient_function_vvd) {  
  vector<vector<double> > parameters;
  TypeParam().valid_values(parameters);
  ASSERT_GT(parameters.size(), 0U);
  for (size_t n = 0; n < parameters.size(); n++) {
    vector<double> p(parameters[n]);
    var p0(p[0]);
    var p1(p[1]);
    
    var lp = _LOG_PROB_<true>(p0, p1, p[2]);
    var expected_lp = TypeParam().log_prob(p0, p1, p[2]);
    vector<var> v_params(2);
    v_params[0] = p0;
    v_params[1] = p1;
    
    vector<double> gradients;
    lp.grad(v_params, gradients);
    vector<double> expected_gradients;
    expected_lp.grad(v_params, expected_gradients);
    
    EXPECT_FLOAT_EQ(expected_lp.val(),
		    lp.val())
      << "Index: " << n << " - function value test failed" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
    EXPECT_FLOAT_EQ(expected_gradients[0],
		    gradients[0])
      << "Index: " << n << " - hand-coded gradient test failed for parameter 0" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
    EXPECT_FLOAT_EQ(expected_gradients[1],
		    gradients[1])
      << "Index: " << n << " - hand-coded gradient test failed for parameter 1" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
  }
}
TYPED_TEST_P(AgradDistributionTestFixture, gradient_function_vvv) {
  vector<vector<double> > parameters;
  TypeParam().valid_values(parameters);
  ASSERT_GT(parameters.size(), 0U);
  for (size_t n = 0; n < parameters.size(); n++) {
    vector<double> p(parameters[n]);
    var p0(p[0]);
    var p1(p[1]);
    var p2(p[2]);
    
    var lp = _LOG_PROB_<true>(p0, p1, p2);
    var expected_lp = TypeParam().log_prob(p0, p1, p2);
    vector<var> v_params(3);
    v_params[0] = p0;
    v_params[1] = p1;
    v_params[2] = p2;
    
    vector<double> gradients;
    lp.grad(v_params, gradients);
    vector<double> expected_gradients;
    expected_lp.grad(v_params, expected_gradients);
    
    EXPECT_FLOAT_EQ(expected_lp.val(),
		    lp.val())
      << "Index: " << n << " - function value test failed" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
    EXPECT_FLOAT_EQ(expected_gradients[0],
		    gradients[0])
      << "Index: " << n << " - hand-coded gradient test failed for parameter 0" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
    EXPECT_FLOAT_EQ(expected_gradients[1],
		    gradients[1])
      << "Index: " << n << " - hand-coded gradient test failed for parameter 1" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
    EXPECT_FLOAT_EQ(expected_gradients[2],
		    gradients[2])
      << "Index: " << n << " - hand-coded test failed for parameter 2" << std::endl
      << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
  }
}

TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_ddd) {
  test_vectorized<TypeParam, double, double, double >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_ddD) {
  test_vectorized<TypeParam, double, double, vector<double> >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_ddv) {
  test_vectorized<TypeParam, double, double, var >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_ddV) {
  test_vectorized<TypeParam, double, double, vector<var> >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_dDd) {
 test_vectorized<TypeParam, double, vector<double>, double >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_dDD) {
  test_vectorized<TypeParam, double, vector<double>, vector<double> >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_dDv) {
  test_vectorized<TypeParam, double, vector<double>, var >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_dDV) {
  test_vectorized<TypeParam, double, vector<double>, vector<var> >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_dvd) {
  test_vectorized<TypeParam, double, var, double >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_dvD) {
  test_vectorized<TypeParam, double, var, vector<double> >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_dvv) {
  test_vectorized<TypeParam, double, var, var >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_dvV) {
  test_vectorized<TypeParam, double, var, vector<var> >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_dVd) {
  test_vectorized<TypeParam, double, vector<var>, double >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_dVD) {
  test_vectorized<TypeParam, double, vector<var>, vector<double> >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_dVv) {
  test_vectorized<TypeParam, double, vector<var>, var >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_dVV) {
  test_vectorized<TypeParam, double, vector<var>, vector<var> >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_Ddd) {
  test_vectorized<TypeParam, vector<double>, double, double >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_DdD) {
  test_vectorized<TypeParam, vector<double>, double, vector<double> >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_Ddv) {
  test_vectorized<TypeParam, vector<double>, double, var >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_DdV) {
  test_vectorized<TypeParam, vector<double>, double, vector<var> >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_DDd) {
  test_vectorized<TypeParam, vector<double>, vector<double>, double >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_DDD) {
  test_vectorized<TypeParam, vector<double>, vector<double>, vector<double> >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_DDv) {
  test_vectorized<TypeParam, vector<double>, vector<double>, var >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_DDV) {
  test_vectorized<TypeParam, vector<double>, vector<double>, vector<var> >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_Dvd) {
  test_vectorized<TypeParam, vector<double>, var, double >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_DvD) {
  test_vectorized<TypeParam, vector<double>, var, vector<double> >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_Dvv) {
  test_vectorized<TypeParam, vector<double>, var, var >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_DvV) {
  test_vectorized<TypeParam, vector<double>, var, vector<var> >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_DVd) {
  test_vectorized<TypeParam, vector<double>, vector<var>, double >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_DVD) {
  test_vectorized<TypeParam, vector<double>, vector<var>, vector<double> >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_DVv) {
  test_vectorized<TypeParam, vector<double>, vector<var>, var >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_DVV) {
  test_vectorized<TypeParam, vector<double>, vector<var>, vector<var> >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_Vdd) {
  test_vectorized<TypeParam, vector<double>, double, double >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_VdD) {
  test_vectorized<TypeParam, vector<double>, double, vector<double> >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_Vdv) {
  test_vectorized<TypeParam, vector<double>, double, var >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_VdV) {
  test_vectorized<TypeParam, vector<double>, double, vector<var> >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_VDd) {
  test_vectorized<TypeParam, vector<double>, vector<double>, double >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_VDD) {
  test_vectorized<TypeParam, vector<double>, vector<double>, vector<double> >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_VDv) {
  test_vectorized<TypeParam, vector<double>, vector<double>, var >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_VDV) {
  test_vectorized<TypeParam, vector<double>, vector<double>, vector<var> >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_Vvd) {
  test_vectorized<TypeParam, vector<double>, var, double >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_VvD) {
  test_vectorized<TypeParam, vector<double>, var, vector<double> >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_Vvv) {
  test_vectorized<TypeParam, vector<double>, var, var >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_VvV) {
  test_vectorized<TypeParam, vector<double>, var, vector<var> >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_VVd) {
  test_vectorized<TypeParam, vector<double>, vector<var>, double >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_VVD) {
  test_vectorized<TypeParam, vector<double>, vector<var>, vector<double> >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_VVv) {
  test_vectorized<TypeParam, vector<double>, vector<var>, var >();
}
TYPED_TEST_P(AgradDistributionTestFixture2, vectorized_VVV) {
  test_vectorized<TypeParam, vector<double>, vector<var>, vector<var> >();
}

// This has a limit of 50 tests.
REGISTER_TYPED_TEST_CASE_P(AgradDistributionTestFixture,
			   call_all_versions,
			   check_valid_ddd,
			   check_valid_ddv,
			   check_valid_dvd,
			   check_valid_dvv,
			   check_valid_vdd,
			   check_valid_vdv,
			   check_valid_vvd,
			   check_valid_vvv,
			   check_invalid_ddd,
			   check_invalid_ddv,
			   check_invalid_dvd,
			   check_invalid_dvv,
			   check_invalid_vdd,
			   check_invalid_vdv,
			   check_invalid_vvd,
			   check_invalid_vvv,
			   logprob_propto_ddd,
			   logprob_propto_ddv,
			   logprob_propto_dvd,
			   logprob_propto_dvv,
			   logprob_propto_vdd,
			   logprob_propto_vdv,
			   logprob_propto_vvd,
			   logprob_propto_vvv,
			   gradient_finite_diff_ddd,
			   gradient_finite_diff_ddv,
			   gradient_finite_diff_dvd,
			   gradient_finite_diff_dvv,
			   gradient_finite_diff_vdd,
			   gradient_finite_diff_vdv,
			   gradient_finite_diff_vvd,
			   gradient_finite_diff_vvv,
			   gradient_function_ddd,
			   gradient_function_ddv,
			   gradient_function_dvd,
			   gradient_function_dvv,
			   gradient_function_vdd,
			   gradient_function_vdv,
			   gradient_function_vvd,
			   gradient_function_vvv);
REGISTER_TYPED_TEST_CASE_P(AgradDistributionTestFixture2,
			   vectorized_ddd,
			   vectorized_ddD,
			   vectorized_ddv,
			   vectorized_ddV,
			   vectorized_dDd,
			   vectorized_dDD,
			   vectorized_dDv,
			   vectorized_dDV,
			   vectorized_dvd,
			   vectorized_dvD,
			   vectorized_dvv,
			   vectorized_dvV,
			   vectorized_dVd,
			   vectorized_dVD,
			   vectorized_dVv,
			   vectorized_dVV,
			   vectorized_Ddd,
			   vectorized_DdD,
			   vectorized_Ddv,
			   vectorized_DdV,
			   vectorized_DDd,
			   vectorized_DDD,
			   vectorized_DDv,
			   vectorized_DDV,
			   vectorized_Dvd,
			   vectorized_DvD,
			   vectorized_Dvv,
			   vectorized_DvV,
			   vectorized_DVd,
			   vectorized_DVD,
			   vectorized_DVv,
			   vectorized_DVV,
			   vectorized_Vdd,
			   vectorized_VdD,
			   vectorized_Vdv,
			   vectorized_VdV,
			   vectorized_VDd,
			   vectorized_VDD,
			   vectorized_VDv,
			   vectorized_VDV,
			   vectorized_Vvd,
			   vectorized_VvD,
			   vectorized_Vvv,
			   vectorized_VvV,
			   vectorized_VVd,
			   vectorized_VVD,
			   vectorized_VVv,
			   vectorized_VVV);
#endif
