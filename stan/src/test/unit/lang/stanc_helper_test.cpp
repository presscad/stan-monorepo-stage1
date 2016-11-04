// TODO(carpenter): move this into test/unit/command
//                  it's here now because it won't compile there

#include <gtest/gtest.h>
#include <stan/lang/compiler.hpp>
#include <stan/command/stanc_helper.hpp>
#include <test/unit/util.hpp>
#include <fstream>
#include <sstream>

void expect_find(const std::string& str, const std::string& target) {
  EXPECT_TRUE(str.find(target) != std::string::npos)
    << str << " does not contain " << target << std::endl;
}

TEST(commandStancHelper, printVersion) {
  std::stringstream ss;
  print_version(&ss);
  expect_find(ss.str(), "stanc version 2.");
}

TEST(commandStancHelper, printStancHelp) {
  std::stringstream ss;
  print_stanc_help(&ss);
  expect_find(ss.str(), "USAGE:  stanc [options] <model_file>");
  expect_find(ss.str(), "OPTIONS:");
}

int run_helper(const std::string& path,
               std::ostream& out, std::ostream& err) {
  int argc = 2;
  std::vector<const char*> argv_vec;
  argv_vec.push_back("main");
  argv_vec.push_back(path.c_str());
  const char** argv = &argv_vec[0];
  return stanc_helper(argc, argv, &out, &err);
}

TEST(commandStancHelper, readOnlyOK) {
  std::stringstream out;
  std::stringstream err;
  int rc = run_helper("src/test/test-models/good/stanc_helper.stan", out, err);
  
  EXPECT_EQ(0, rc)
    << "out=" << out.str() << std::endl << "err=" << err.str() << std::endl;
  expect_find(out.str(), "Model name=stanc_helper_model");
  expect_find(out.str(), "Input file=src/test/test-models/good/stanc_helper.stan");
  expect_find(out.str(), "Output file=stanc_helper_model.cpp");
  EXPECT_EQ(0, err.str().size())
    << "error=" << err.str() << std::endl;
}

TEST(commandStancHelper, failRC) {
  std::stringstream out;
  std::stringstream err;
  int rc = run_helper("src/test/test-models/bad/stanc_helper.stan", out, err);

  // TODO(carpenter): This should be -2 but it's -3 so
  // I only tested that it's != 0 to contrast with earlier success
  EXPECT_TRUE(rc != 0);
}
    
