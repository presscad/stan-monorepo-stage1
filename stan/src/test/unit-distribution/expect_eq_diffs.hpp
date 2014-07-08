#ifndef __TEST__UNIT_DISTRIBUTION__EXPECT_EQ_DIFFS_HPP__
#define __TEST__UNIT_DISTRIBUTION__EXPECT_EQ_DIFFS_HPP__

#include <stan/agrad/rev.hpp>

void expect_eq_diffs(double x1, double x2, 
                     double y1, double y2,
                     std::string message="") {
  if (std::isnan(x1-x2))
    EXPECT_TRUE(std::isnan(y1-y2)) << message;
  else
    EXPECT_FLOAT_EQ(x1-x2,y1-y2) << message;
}

void expect_eq_diffs(const stan::agrad::var& x1, 
                     const stan::agrad::var& x2,
                     const stan::agrad::var& y1, 
                     const stan::agrad::var& y2,
                     std::string message="") {
  expect_eq_diffs(x1.val(), x2.val(), 
                  y1.val(), y2.val(), message);
}

#endif
