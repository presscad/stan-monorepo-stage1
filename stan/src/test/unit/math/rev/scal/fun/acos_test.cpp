#include <stan/math/rev/scal/fun/acos.hpp>
#include <test/unit/math/rev/mat/fun/util.hpp>
#include <gtest/gtest.h>
#include <stan/math/prim/scal/fun/constants.hpp>
#include <stan/math/rev/core.hpp>
#include <test/unit/math/rev/scal/fun/nan_util.hpp>


TEST(AgradRev,acos_var) {
  AVAR a = 0.68;
  AVAR f = acos(a);
  EXPECT_FLOAT_EQ(acos(0.68), f.val());

  AVEC x = createAVEC(a);
  VEC g;
  f.grad(x,g);
  EXPECT_FLOAT_EQ(-1.0/sqrt(1.0 - (0.68 * 0.68)), g[0]);
}

TEST(AgradRev,acos_1) {
  AVAR a = 1;
  AVAR f = acos(a);
  EXPECT_FLOAT_EQ((0.0),f.val());

  AVEC x = createAVEC(a);
  VEC g;
  f.grad(x,g);
  EXPECT_FLOAT_EQ(-1.0/sqrt(1.0 - (1 * 1)), g[0]); 
}

TEST(AgradRev,acos_neg_1) {
  AVAR a = -1;
  AVAR f = acos(a);
  EXPECT_FLOAT_EQ((3.14159265),f.val());

  AVEC x = createAVEC(a);
  VEC g;
  f.grad(x,g);
  EXPECT_FLOAT_EQ(-1.0/sqrt(1.0 - (1 * 1)), g[0]); 
}

TEST(AgradRev,acos_out_of_bounds1) {
  AVAR a = 1.0 + stan::math::EPSILON;
  AVAR f = acos(a);
  AVEC x = createAVEC(a);
  VEC g;
  f.grad(x,g);
  EXPECT_TRUE(std::isnan(acos(a)));
  EXPECT_TRUE(g.size() == 1);
  EXPECT_TRUE(std::isnan(g[0]));
}

TEST(AgradRev,acos_out_of_bounds2) {
  AVAR a = -1.0 - stan::math::EPSILON;
  AVAR f = acos(a);
  AVEC x = createAVEC(a);
  VEC g;
  f.grad(x,g);
  EXPECT_TRUE(std::isnan(acos(a)));
  EXPECT_TRUE(g.size() == 1);
  EXPECT_TRUE(std::isnan(g[0]));
}

struct acos_fun {
  template <typename T0>
  inline T0
  operator()(const T0& arg1) const {
    return acos(arg1);
  }
};

TEST(AgradRev,acos_NaN) {
  acos_fun acos_;
  test_nan(acos_,false,true);
}
