#include <gtest/gtest.h>
#include <test/models/model_test_fixture.hpp>

class Models_BasicDistributions_Wishart :
  public Model_Test_Fixture<Models_BasicDistributions_Wishart> {
protected:
  virtual void SetUp() {
  }
public:
  static std::vector<std::string> get_model_path() {
    std::vector<std::string> model_path;
    model_path.push_back("models");
    model_path.push_back("basic_distributions");
    model_path.push_back("wishart");
    return model_path;
  }
  static bool has_data() {
    return false;
  }

  static size_t num_iterations() {
    return iterations;
  }

  static std::vector<std::pair<size_t, double> >
  get_expected_values() {
    using std::make_pair;
    std::vector<std::pair<size_t, double> > expected_values;
    
    expected_values.push_back(make_pair(0U, 2.0 * 4.0));
    expected_values.push_back(make_pair(1U, 0.0));
    expected_values.push_back(make_pair(2U, 0.0));
    expected_values.push_back(make_pair(3U, 0.5 * 4.0));
    
    return expected_values;
  }

};

INSTANTIATE_TYPED_TEST_CASE_P(Models_BasicDistributions_Wishart,
			      Model_Test_Fixture,
			      Models_BasicDistributions_Wishart);
