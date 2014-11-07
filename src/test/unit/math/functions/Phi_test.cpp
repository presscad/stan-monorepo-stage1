#include <boost/math/special_functions/fpclassify.hpp>
#include <stan/math/functions/Phi.hpp>
#include <gtest/gtest.h>

TEST(MathFunctions, Phi) {
  EXPECT_EQ(0.5 + 0.5 * boost::math::erf(0.0), stan::math::Phi(0.0));
  EXPECT_FLOAT_EQ(0.5 + 0.5 * boost::math::erf(0.9/std::sqrt(2.0)), stan::math::Phi(0.9));
  EXPECT_EQ(0.5 + 0.5 * boost::math::erf(-5.0/std::sqrt(2.0)), stan::math::Phi(-5.0));
}

// tests calculating using R 3.0.2 Snow Leopard build (6558)
TEST(MathFunctions, PhiTails) {
  using stan::math::Phi;

  EXPECT_EQ(0, Phi(-40));

  EXPECT_FLOAT_EQ(1, 4.60535300958196e-308 / Phi(-37.5));
  EXPECT_FLOAT_EQ(1, 5.72557122252458e-300 / Phi(-37));
  EXPECT_FLOAT_EQ(1, 5.54472571307484e-292 / Phi(-36.5));
  EXPECT_FLOAT_EQ(1, 4.18262406579728e-284 / Phi(-36));
  EXPECT_FLOAT_EQ(1, 2.45769154066194e-276 / Phi(-35.5));
  EXPECT_FLOAT_EQ(1, 1.12491070647241e-268 / Phi(-35));
  EXPECT_FLOAT_EQ(1, 4.01072896657726e-261 / Phi(-34.5));
  EXPECT_FLOAT_EQ(1, 1.11389878557438e-253 / Phi(-34));
  EXPECT_FLOAT_EQ(1, 2.40983869512039e-246 / Phi(-33.5));
  EXPECT_FLOAT_EQ(1, 4.06118562091586e-239 / Phi(-33));
  EXPECT_FLOAT_EQ(1, 5.33142435967881e-232 / Phi(-32.5));
  EXPECT_FLOAT_EQ(1, 5.4520806035124e-225 / Phi(-32));
  EXPECT_FLOAT_EQ(1, 4.34323260103177e-218 / Phi(-31.5));
  EXPECT_FLOAT_EQ(1, 2.6952500812005e-211 / Phi(-31));
  EXPECT_FLOAT_EQ(1, 1.30293791317808e-204 / Phi(-30.5));
  EXPECT_FLOAT_EQ(1, 4.90671392714819e-198 / Phi(-30));
  EXPECT_FLOAT_EQ(1, 1.43947455222918e-191 / Phi(-29.5));
  EXPECT_FLOAT_EQ(1, 3.28978526670438e-185 / Phi(-29));
  EXPECT_FLOAT_EQ(1, 5.85714125380634e-179 / Phi(-28.5));
  EXPECT_FLOAT_EQ(1, 8.12386946965943e-173 / Phi(-28));
  EXPECT_FLOAT_EQ(1, 8.77817055687808e-167 / Phi(-27.5));
  EXPECT_FLOAT_EQ(1, 7.38948100688502e-161 / Phi(-27));
  EXPECT_FLOAT_EQ(1, 4.84616266030332e-155 / Phi(-26.5));
  EXPECT_FLOAT_EQ(1, 2.47606331550339e-149 / Phi(-26));
  EXPECT_FLOAT_EQ(1, 9.85623651896393e-144 / Phi(-25.5));
  EXPECT_FLOAT_EQ(1, 3.05669670638256e-138 / Phi(-25));
  EXPECT_FLOAT_EQ(1, 7.38570686148941e-133 / Phi(-24.5));
  EXPECT_FLOAT_EQ(1, 1.3903921185497e-127 / Phi(-24));
  EXPECT_FLOAT_EQ(1, 2.03936756324998e-122 / Phi(-23.5));
  EXPECT_FLOAT_EQ(1, 2.33063700622065e-117 / Phi(-23));
  EXPECT_FLOAT_EQ(1, 2.07531079906636e-112 / Phi(-22.5));
  EXPECT_FLOAT_EQ(1, 1.43989243514508e-107 / Phi(-22));
  EXPECT_FLOAT_EQ(1, 7.78439707718263e-103 / Phi(-21.5));
  EXPECT_FLOAT_EQ(1, 3.27927801897904e-98 / Phi(-21));
  EXPECT_FLOAT_EQ(1, 1.0764673258791e-93 / Phi(-20.5));
  EXPECT_FLOAT_EQ(1, 2.75362411860623e-89 / Phi(-20));
  EXPECT_FLOAT_EQ(1, 5.48911547566041e-85 / Phi(-19.5));
  EXPECT_FLOAT_EQ(1, 8.52722395263098e-81 / Phi(-19));
  EXPECT_FLOAT_EQ(1, 1.03236986895633e-76 / Phi(-18.5));
  EXPECT_FLOAT_EQ(1, 9.74094891893715e-73 / Phi(-18));
  EXPECT_FLOAT_EQ(1, 7.16345876623504e-69 / Phi(-17.5));
  EXPECT_FLOAT_EQ(1, 4.10599620209891e-65 / Phi(-17));
  EXPECT_FLOAT_EQ(1, 1.83446300316473e-61 / Phi(-16.5));
  EXPECT_FLOAT_EQ(1, 6.38875440053809e-58 / Phi(-16));
  EXPECT_FLOAT_EQ(1, 1.73446079179387e-54 / Phi(-15.5));
  EXPECT_FLOAT_EQ(1, 3.67096619931275e-51 / Phi(-15));
  EXPECT_FLOAT_EQ(1, 6.05749476441522e-48 / Phi(-14.5));
  EXPECT_FLOAT_EQ(1, 7.7935368191928e-45 / Phi(-14));
  EXPECT_FLOAT_EQ(1, 7.81880730565789e-42 / Phi(-13.5));
  EXPECT_FLOAT_EQ(1, 6.11716439954988e-39 / Phi(-13));
  EXPECT_FLOAT_EQ(1, 3.73256429887771e-36 / Phi(-12.5));
  EXPECT_FLOAT_EQ(1, 1.77648211207768e-33 / Phi(-12));
  EXPECT_FLOAT_EQ(1, 6.59577144611367e-31 / Phi(-11.5));
  EXPECT_FLOAT_EQ(1, 1.91065957449868e-28 / Phi(-11));
  EXPECT_FLOAT_EQ(1, 4.31900631780923e-26 / Phi(-10.5));
  EXPECT_FLOAT_EQ(1, 7.61985302416053e-24 / Phi(-10));
  EXPECT_FLOAT_EQ(1, 1.04945150753626e-21 / Phi(-9.5));
  EXPECT_FLOAT_EQ(1, 1.12858840595384e-19 / Phi(-9));
  EXPECT_FLOAT_EQ(1, 9.47953482220332e-18 / Phi(-8.5));
  EXPECT_FLOAT_EQ(1, 6.22096057427178e-16 / Phi(-8));
  EXPECT_FLOAT_EQ(1, 3.1908916729109e-14 / Phi(-7.5));
  EXPECT_FLOAT_EQ(1, 1.27981254388584e-12 / Phi(-7));
  EXPECT_FLOAT_EQ(1, 4.01600058385912e-11 / Phi(-6.5));
  EXPECT_FLOAT_EQ(1, 9.86587645037698e-10 / Phi(-6));
  EXPECT_FLOAT_EQ(1, 1.89895624658877e-08 / Phi(-5.5));
  EXPECT_FLOAT_EQ(1, 2.86651571879194e-07 / Phi(-5));
  EXPECT_FLOAT_EQ(1, 3.39767312473006e-06 / Phi(-4.5));
  EXPECT_FLOAT_EQ(1, 3.16712418331199e-05 / Phi(-4));
  EXPECT_FLOAT_EQ(1, 0.000232629079035525 / Phi(-3.5));
  EXPECT_FLOAT_EQ(1, 0.00134989803163009 / Phi(-3));
  EXPECT_FLOAT_EQ(1, 0.00620966532577613 / Phi(-2.5));
  EXPECT_FLOAT_EQ(1, 0.0227501319481792 / Phi(-2));
  EXPECT_FLOAT_EQ(1, 0.0668072012688581 / Phi(-1.5));
  EXPECT_FLOAT_EQ(1, 0.158655253931457 / Phi(-1));
  EXPECT_FLOAT_EQ(1, 0.308537538725987 / Phi(-0.5));
  EXPECT_FLOAT_EQ(1, 0.5 / Phi(0));
  EXPECT_FLOAT_EQ(1, 0.691462461274013 / Phi(0.5));
  EXPECT_FLOAT_EQ(1, 0.841344746068543 / Phi(1));
  EXPECT_FLOAT_EQ(1, 0.933192798731142 / Phi(1.5));
  EXPECT_FLOAT_EQ(1, 0.977249868051821 / Phi(2));
  EXPECT_FLOAT_EQ(1, 0.993790334674224 / Phi(2.5));
  EXPECT_FLOAT_EQ(1, 0.99865010196837 / Phi(3));
  EXPECT_FLOAT_EQ(1, 0.999767370920964 / Phi(3.5));
  EXPECT_FLOAT_EQ(1, 0.999968328758167 / Phi(4));
  EXPECT_FLOAT_EQ(1, 0.999996602326875 / Phi(4.5));
  EXPECT_FLOAT_EQ(1, 0.999999713348428 / Phi(5));
  EXPECT_FLOAT_EQ(1, 0.999999981010438 / Phi(5.5));
  EXPECT_FLOAT_EQ(1, 0.999999999013412 / Phi(6));
  EXPECT_FLOAT_EQ(1, 0.99999999995984 / Phi(6.5));
  EXPECT_FLOAT_EQ(1, 0.99999999999872 / Phi(7));
  EXPECT_FLOAT_EQ(1, 0.999999999999968 / Phi(7.5));
  EXPECT_FLOAT_EQ(1, 0.999999999999999 / Phi(8));
  EXPECT_FLOAT_EQ(1, 1 / Phi(8.5));
  EXPECT_FLOAT_EQ(1, 1 / Phi(9));
  EXPECT_FLOAT_EQ(1, 1 / Phi(9.5));
  EXPECT_FLOAT_EQ(1, 1 / Phi(10));
}

TEST(MathFunctions, Phi_nan) {
  double nan = std::numeric_limits<double>::quiet_NaN();
  EXPECT_THROW(stan::math::Phi(nan),
               std::domain_error);
}
