#include <stdexcept>
#include <test/test-models/good/lang/print_reject_tdata_block.hpp>
#include <test/unit/lang/reject/reject_helper.hpp>
#include <gtest/gtest.h>

TEST(StanCommon, printRejectTData) {
  typedef 
    print_reject_tdata_block_model_namespace
    ::print_reject_tdata_block_model
    model_t;
  print_reject_test<model_t,std::domain_error>("quitting time");
}
