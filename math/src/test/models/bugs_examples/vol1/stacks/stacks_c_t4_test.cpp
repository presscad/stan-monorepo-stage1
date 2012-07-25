#include <gtest/gtest.h>
#include <test/models/model_test_fixture.hpp>

class Models_BugsExamples_Vol1_Stacks_C_T4 : 
  public Model_Test_Fixture<Models_BugsExamples_Vol1_Stacks_C_T4> {
protected:
  virtual void SetUp() {
  }
public:
  static std::vector<std::string> get_model_path() {
    std::vector<std::string> model_path;
    model_path.push_back("models");
    model_path.push_back("bugs_examples");
    model_path.push_back("vol1");
    model_path.push_back("stacks");
    model_path.push_back("stacks_c_t4");
    return model_path;
  }

  static bool has_data() {
    return true;
  }

  static bool has_init() {
    return true;
  }

  static size_t num_iterations() {
    return 8000U;
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
    size_t index;
    std::vector<size_t> dims;
    dims.push_back(0);

    std::vector<std::pair<size_t, double> > expected_values;

    index = chains->get_total_param_index(chains->param_name_to_index("b"),
					  dims);
    expected_values.push_back(make_pair(index + 0U, 0.8361));
    expected_values.push_back(make_pair(index + 1U, 0.8565));
    expected_values.push_back(make_pair(index + 2U, -0.1254));

    index = chains->get_total_param_index(chains->param_name_to_index("b0"),
					  dims);
    expected_values.push_back(make_pair(index, -40.22));

    index = chains->get_total_param_index(chains->param_name_to_index("sigma"),
					  dims);
    expected_values.push_back(make_pair(index, 3.378));

    index = chains->get_total_param_index(chains->param_name_to_index("outlier_3"),
					  dims);
    expected_values.push_back(make_pair(index, 0.0334));

    index = chains->get_total_param_index(chains->param_name_to_index("outlier_4"),
					  dims);
    expected_values.push_back(make_pair(index, 0.2343));

    index = chains->get_total_param_index(chains->param_name_to_index("outlier_21"),
					  dims);
    expected_values.push_back(make_pair(index, 0.5904));

    return expected_values;
  }

};

INSTANTIATE_TYPED_TEST_CASE_P(Models_BugsExamples_Vol1_Stacks_C_T4,
			      Model_Test_Fixture,
			      Models_BugsExamples_Vol1_Stacks_C_T4);
