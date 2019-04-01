//  Copyright John Maddock 2012.  
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/integer.hpp>

typedef boost::int_t<sizeof(boost::intmax_t)*CHAR_BIT + 1>::least fail_int_least;
