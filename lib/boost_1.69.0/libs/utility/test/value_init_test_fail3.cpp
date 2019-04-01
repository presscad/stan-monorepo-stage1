// Copyright 2002, Fernando Luis Cacciola Carballal.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Test program for "boost/utility/value_init.hpp"
//
// Initial: 21 Agu 2002

#include <iostream>
#include <string>

#include "boost/utility/value_init.hpp"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

int main()
{
  boost::value_initialized<int const> const cx_c ;

  get(cx_c) = 1234 ; // this should produce an ERROR

  return 0;
}
