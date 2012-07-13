#include <gtest/gtest.h>
#include <test/models/model_test_fixture.hpp>

class Models_BugsExamples_Vol1_SurgicalSimple : 
  public Model_Test_Fixture<Models_BugsExamples_Vol1_SurgicalSimple> {
protected:
  virtual void SetUp() {
  }
public:
  static std::vector<std::string> get_model_path() {
    std::vector<std::string> model_path;
    model_path.push_back("models");
    model_path.push_back("bugs_examples");
    model_path.push_back("vol1");
    model_path.push_back("surgical");
    model_path.push_back("surgical_simple");
    return model_path;
  }

  static bool has_data() {
    return true;
  }

  static bool has_init() {
    return true;
  }

  static size_t num_iterations() {
    return iterations;
  }

  static std::vector<size_t> skip_chains_test() {
    std::vector<size_t> params_to_skip;
    return params_to_skip;
  }

  static void populate_chains() {
    default_populate_chains();
  }

  static std::vector<std::pair<size_t, double> >
  get_expected_values() {
    using std::make_pair;
    std::vector<std::pair<size_t, double> > expected_values;
    
    expected_values.push_back(make_pair( 0U, 0.02009)); // p[1]
    expected_values.push_back(make_pair( 1U, 0.1266));  // p[2]
    expected_values.push_back(make_pair( 2U, 0.07436)); // p[3]
    expected_values.push_back(make_pair( 3U, 0.05789)); // p[4]
    expected_values.push_back(make_pair( 4U, 0.04237)); // p[5]
    expected_values.push_back(make_pair( 5U, 0.07081)); // p[6]
    expected_values.push_back(make_pair( 6U, 0.06686)); // p[7]
    expected_values.push_back(make_pair( 7U, 0.1473));  // p[8]
    expected_values.push_back(make_pair( 8U, 0.07216)); // p[9]
    expected_values.push_back(make_pair( 9U, 0.09078)); // p[10]
    expected_values.push_back(make_pair(10U, 0.1165));  // p[11]
    expected_values.push_back(make_pair(11U, 0.06906)); // p[12]
    
    return expected_values;
  }

};

INSTANTIATE_TYPED_TEST_CASE_P(Models_BugsExamples_Vol1_SurgicalSimple,
			      Model_Test_Fixture,
			      Models_BugsExamples_Vol1_SurgicalSimple);
