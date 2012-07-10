#include <gtest/gtest.h>
#include <test/models/model_test_fixture.hpp>

class Models_BugsExamples_Vol1_Dyes : 
  public Model_Test_Fixture<Models_BugsExamples_Vol1_Dyes> {
protected:
  virtual void SetUp() {
  }
public:
  static std::vector<std::string> get_model_path() {
    std::vector<std::string> model_path;
    model_path.push_back("models");
    model_path.push_back("bugs_examples");
    model_path.push_back("vol1");
    model_path.push_back("dyes");
    model_path.push_back("dyes");
    return model_path;
  }

  static bool has_data() {
    return true;
  }

  static bool has_init() {
    return true;
  }

  static size_t num_iterations() {
    return 4000U;
  }

  static void populate_chains() {
    default_populate_chains();
  }

  static std::vector<std::pair<size_t, double> >
  get_expected_values() {
    using std::make_pair;
    std::vector<std::pair<size_t, double> > expected_values;

    expected_values.push_back(make_pair(0U, 2207)); // sigma2.btw
    expected_values.push_back(make_pair(1U, 3034)); // sigma2.with
    expected_values.push_back(make_pair(2U, 1528)); // theta

    return expected_values;
  }

};

INSTANTIATE_TYPED_TEST_CASE_P(Models_BugsExamples_Vol1_Dyes,
			      Model_Test_Fixture,
			      Models_BugsExamples_Vol1_Dyes);
