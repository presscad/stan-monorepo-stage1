// Copyright (C) 2015 Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/lib/optional for documentation.
//
// You are welcome to contact the author at: akrzemi1@gmail.com


#include "boost/optional/optional.hpp"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include "boost/core/addressof.hpp"
#include "boost/core/enable_if.hpp"
#include "boost/core/lightweight_test.hpp"
#include "testable_classes.hpp"
#include "optional_ref_assign_test_defs.hpp"


template <typename T>
void test_all_const_cases()
{
  test_converting_assignment<T, T>();
  test_converting_assignment<const T, const T>();
  test_converting_assignment<T, const T>();
}

int main()
{
  test_all_const_cases<ScopeGuard>();
  test_all_const_cases<Abstract>();
  
  return boost::report_errors();
}
