///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_

#ifdef _MSC_VER
#  define _SCL_SECURE_NO_WARNINGS
#endif

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/mersenne_twister.hpp>
#include "test.hpp"

#if defined(HAS_GMP)
#include <boost/multiprecision/gmp.hpp>
#endif
#if defined(HAS_MPFR)
#include <boost/multiprecision/mpfr.hpp>
#endif
#if defined(HAS_MPFI)
#include <boost/multiprecision/mpfi.hpp>
#endif
#ifdef HAS_TOMMATH
#include <boost/multiprecision/tommath.hpp>
#endif
#ifdef HAS_FLOAT128
#include <boost/multiprecision/float128.hpp>
#endif
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>


using namespace boost::multiprecision;

#ifdef BOOST_MSVC
#pragma warning(disable:4127)
#endif


template <class T>
T generate_random(unsigned bits_wanted)
{
   static boost::random::mt19937 gen;
   typedef boost::random::mt19937::result_type random_type;

   T max_val;
   unsigned digits;
   if(std::numeric_limits<T>::is_bounded && (bits_wanted == (unsigned)std::numeric_limits<T>::digits))
   {
      max_val = (std::numeric_limits<T>::max)();
      digits = std::numeric_limits<T>::digits;
   }
   else
   {
      max_val = T(1) << bits_wanted;
      digits = bits_wanted;
   }

   unsigned bits_per_r_val = std::numeric_limits<random_type>::digits - 1;
   while((random_type(1) << bits_per_r_val) > (gen.max)()) --bits_per_r_val;

   unsigned terms_needed = digits / bits_per_r_val + 1;

   T val = 0;
   for(unsigned i = 0; i < terms_needed; ++i)
   {
      val *= (gen.max)();
      val += gen();
   }
   val %= max_val;
   return val;
}

template <class From, class To>
void test_convert_neg_int(From from, const boost::mpl::true_&)
{
   from = -from;
   To t3(from);
   To t4 = from.template convert_to<To>();
   BOOST_CHECK_EQUAL(from.str(), t3.str());
   BOOST_CHECK_EQUAL(from.str(), t4.str());
}
template <class From, class To>
void test_convert_neg_int(From const&, const boost::mpl::false_&)
{
}

template <class From, class To>
void test_convert_imp(boost::mpl::int_<number_kind_integer> const&, boost::mpl::int_<number_kind_integer> const&)
{
   int bits_wanted = (std::min)((std::min)(std::numeric_limits<From>::digits, std::numeric_limits<To>::digits), 2000);

   for(unsigned i = 0; i < 100; ++i)
   {
      From from = generate_random<From>(bits_wanted);
      To t1(from);
      To t2 = from.template convert_to<To>();
      BOOST_CHECK_EQUAL(from.str(), t1.str());
      BOOST_CHECK_EQUAL(from.str(), t2.str());
      test_convert_neg_int<From, To>(from, boost::mpl::bool_<std::numeric_limits<From>::is_signed && std::numeric_limits<To>::is_signed>());
   }
}

template <class From, class To>
void test_convert_neg_rat(From from, const boost::mpl::true_&)
{
   from = -from;
   To t3(from);
   To t4 = from.template convert_to<To>();
   BOOST_CHECK_EQUAL(from.str(), numerator(t3).str());
   BOOST_CHECK_EQUAL(from.str(), numerator(t4).str());
}
template <class From, class To>
void test_convert_neg_rat(From const&, const boost::mpl::false_&)
{
}

template <class From, class To>
void test_convert_imp(boost::mpl::int_<number_kind_integer> const&, boost::mpl::int_<number_kind_rational> const&)
{
   int bits_wanted = (std::min)((std::min)(std::numeric_limits<From>::digits, std::numeric_limits<To>::digits), 2000);

   for(unsigned i = 0; i < 100; ++i)
   {
      From from = generate_random<From>(bits_wanted);
      To t1(from);
      To t2 = from.template convert_to<To>();
      BOOST_CHECK_EQUAL(from.str(), numerator(t1).str());
      BOOST_CHECK_EQUAL(from.str(), numerator(t2).str());
      test_convert_neg_rat<From, To>(from, boost::mpl::bool_<std::numeric_limits<From>::is_signed && std::numeric_limits<To>::is_signed>());
   }
}

template <class From, class To>
void test_convert_neg_float(From from, const boost::mpl::true_&)
{
   from = -from;
   To t3(from);
   To t4 = from.template convert_to<To>();
   To check(from.str() + ".0");
   BOOST_CHECK_EQUAL(t3, check);
   BOOST_CHECK_EQUAL(t4, check);
}
template <class From, class To>
void test_convert_neg_float(From const&, const boost::mpl::false_&)
{
}

template <class From, class To>
void test_convert_imp(boost::mpl::int_<number_kind_integer> const&, boost::mpl::int_<number_kind_floating_point> const&)
{
   int bits_wanted = (std::min)((std::min)(std::numeric_limits<From>::digits, std::numeric_limits<To>::digits), 2000);

   for(unsigned i = 0; i < 100; ++i)
   {
      From from = generate_random<From>(bits_wanted);
      To t1(from);
      To t2 = from.template convert_to<To>();
      To check(from.str() + ".0");
      BOOST_CHECK_EQUAL(t1, check);
      BOOST_CHECK_EQUAL(t2, check);
      test_convert_neg_float<From, To>(from, boost::mpl::bool_<std::numeric_limits<From>::is_signed && std::numeric_limits<To>::is_signed>());
   }
}


template <class From, class To>
void test_convert()
{
   test_convert_imp<From, To>(typename number_category<From>::type(), typename number_category<To>::type());
}


int main()
{
   test_convert<cpp_int, int128_t>();
   test_convert<int128_t, cpp_int>();

   test_convert<cpp_int, cpp_rational>();
   test_convert<int128_t, cpp_rational>();
   test_convert<uint128_t, cpp_rational>();

   test_convert<cpp_int, cpp_bin_float_50>();
   test_convert<int128_t, cpp_bin_float_50>();
   test_convert<uint128_t, cpp_bin_float_50>();

   test_convert<cpp_int, cpp_dec_float_50>();
   test_convert<int128_t, cpp_dec_float_50>();
   test_convert<uint128_t, cpp_dec_float_50>();

#if defined(HAS_GMP)
   test_convert<cpp_int, mpz_int>();
   test_convert<int128_t, mpz_int>();
   test_convert<uint128_t, mpz_int>();

   test_convert<cpp_int, mpq_rational>();
   test_convert<int128_t, mpq_rational>();
   test_convert<uint128_t, mpq_rational>();

   test_convert<cpp_int, mpf_float_50>();
   test_convert<int128_t, mpf_float_50>();
   test_convert<uint128_t, mpf_float_50>();
#endif
#if defined(HAS_MPFR)
   test_convert<cpp_int, mpfr_float_50>();
   test_convert<int128_t, mpfr_float_50>();
   test_convert<uint128_t, mpfr_float_50>();
#endif
#if defined(HAS_MPFI)
   test_convert<cpp_int, mpfi_float_50>();
   test_convert<int128_t, mpfi_float_50>();
   test_convert<uint128_t, mpfi_float_50>();
#endif
#ifdef HAS_TOMMATH
   test_convert<cpp_int, tom_int>();
   test_convert<int128_t, tom_int>();
   test_convert<uint128_t, tom_int>();

   test_convert<cpp_int, tom_rational>();
   test_convert<int128_t, tom_rational>();
   test_convert<uint128_t, tom_rational>();
#endif
#ifdef HAS_FLOAT128
   test_convert<cpp_int, float128>();
   test_convert<int128_t, float128>();
   test_convert<uint128_t, float128>();
#endif
   return boost::report_errors();
}

