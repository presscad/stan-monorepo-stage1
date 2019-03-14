//  (C) Copyright 2009-2011 Frederic Bron.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/type_traits/has_operator.hpp>
#include "test.hpp"
#include "check_integral_constant.hpp"
#include "has_binary_classes.hpp"

TT_TEST_BEGIN(BOOST_TT_TRAIT_NAME)
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C334 const, C334 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C334 const, C334 const, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C334 const, C334 &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C334 const, C334 const &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C334 const, C334 const &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C334 &, C334, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C334 &, C334, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C334 &, C334, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C334 &, C334 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C334 &, C334 const, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C334 &, C334 &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C334 &, C334 &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C334 &, C334 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C334 &, C334 &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C334 &, C334 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C334 &, C334 const &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C334 &, C334 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C334 const &, C334, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C334 const &, C334, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C334 const &, C334, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C334 const &, C334, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C334 const &, C334 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C334 const &, C334 const, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C334 const &, C334 &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C334 const &, C334 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335, C335, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335, C335 &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335, C335 &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335, C335 const &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335, C335 const &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 const, C335, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 const, C335, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 const, C335 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 const, C335 const, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 const, C335 const, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 const, C335 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 const, C335 &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 const, C335 &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 const, C335 &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 const, C335 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 const, C335 const &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 const, C335 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 &, C335, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 &, C335, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 &, C335, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 &, C335 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 &, C335 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 &, C335 &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 &, C335 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 &, C335 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 &, C335 const &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 const &, C335, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 const &, C335, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 const &, C335 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 const &, C335 const, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 const &, C335 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 const &, C335 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 const &, C335 &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 const &, C335 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 const &, C335 const &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 const &, C335 const &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C335 const &, C335 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338, C338, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338, C338, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338, C338, ret & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338, C338 const, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338, C338 &, ret & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338, C338 &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338, C338 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338 const, C338, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338 const, C338, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338 const, C338, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338 const, C338 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338 const, C338 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338 const, C338 &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338 const, C338 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338 const, C338 &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338 const, C338 const &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338 &, C338, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338 &, C338 const, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338 &, C338 &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338 &, C338 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338 &, C338 const &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338 &, C338 const &, ret & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338 const &, C338, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338 const &, C338 const, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338 const &, C338 &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338 const &, C338 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338 const &, C338 &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338 const &, C338 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C338 const &, C338 const &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339, C339, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339, C339 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339, C339 &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339, C339 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339, C339 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339, C339 const &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339, C339 const &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 const, C339, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 const, C339 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 const, C339 const, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 const, C339 &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 const, C339 &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 const, C339 &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 const, C339 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 const, C339 const &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 const, C339 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 const, C339 const &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 &, C339, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 &, C339, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 &, C339 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 &, C339 const, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 &, C339 &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 &, C339 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 &, C339 const &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 &, C339 const &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 &, C339 const &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 const &, C339, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 const &, C339, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 const &, C339 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 const &, C339 const, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 const &, C339 &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 const &, C339 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 const &, C339 const &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C339 const &, C339 const &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C360, C360, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C360, C360 &, void >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C360, C360 &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C360, C360 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C360, C360 const &, void >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C360 const, C360, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C360 const, C360 const, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C360 const, C360 &, void >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C360 const, C360 &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C360 &, C360, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C360 &, C360 const, void >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C360 &, C360 const, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C360 &, C360 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C360 &, C360 &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C360 &, C360 &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C360 &, C360 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C360 &, C360 const &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C360 const &, C360, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C360 const &, C360, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C360 const &, C360 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C360 const &, C360 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C360 const &, C360 const &, void >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C360 const &, C360 const &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C360 const &, C360 const &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361, C361, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361, C361, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361, C361 const, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361, C361 &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361, C361 &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361, C361 const &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 const, C361, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 const, C361, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 const, C361 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 const, C361 const, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 const, C361 const, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 const, C361 &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 const, C361 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 const, C361 &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 &, C361, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 &, C361, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 &, C361 const, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 &, C361 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 &, C361 &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 &, C361 &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 &, C361 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 &, C361 const &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 &, C361 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 const &, C361, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 const &, C361, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 const &, C361 const, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 const &, C361 const, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 const &, C361 &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 const &, C361 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 const &, C361 &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 const &, C361 const &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 const &, C361 const &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 const &, C361 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C361 const &, C361 const &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362, C362, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362, C362, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362, C362 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362, C362 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362, C362 &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362, C362 const &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362, C362 const &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362, C362 const &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362 const, C362, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362 const, C362, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362 const, C362, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362 const, C362 const, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362 const, C362 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362 const, C362 const, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362 const, C362 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362 const, C362 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362 const, C362 const &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362 &, C362 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362 &, C362 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362 &, C362 const, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362 &, C362 const &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362 &, C362 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362 &, C362 const &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362 const &, C362, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362 const &, C362, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362 const &, C362 const, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362 const &, C362 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362 const &, C362 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362 const &, C362 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362 const &, C362 const &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C362 const &, C362 const &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C365, C365, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C365, C365, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C365, C365 const, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C365, C365 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C365, C365 &, ret & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C365, C365 const &, ret & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C365 const, C365, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C365 const, C365, ret & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C365 const, C365, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C365 const, C365 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C365 const, C365 const, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C365 const, C365 const, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C365 const, C365 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C365 const, C365 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C365 const, C365 const &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C365 &, C365, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C365 &, C365, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C365 &, C365, ret & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C365 &, C365 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C365 &, C365 &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C365 &, C365 const &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C365 &, C365 const &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C365 const &, C365 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C365 const &, C365 const, ret & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C365 const &, C365 &, ret & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C365 const &, C365 const &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C366, C366, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C366, C366, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C366, C366, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C366, C366 const, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C366, C366 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C366, C366 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C366, C366 &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C366 const, C366, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C366 const, C366, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C366 const, C366, ret const & >::value), 1);
TT_TEST_END
