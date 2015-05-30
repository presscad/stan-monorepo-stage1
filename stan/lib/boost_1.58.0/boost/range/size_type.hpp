// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_SIZE_TYPE_HPP
#define BOOST_RANGE_SIZE_TYPE_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/range/config.hpp>
#include <boost/range/difference_type.hpp>
#include <boost/range/concepts.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <cstddef>
#include <utility>

namespace boost
{
    namespace detail
    {

        //////////////////////////////////////////////////////////////////////////
        // default
        //////////////////////////////////////////////////////////////////////////

        template<typename T>
        class has_size_type
        {
            typedef char no_type;
            struct yes_type { char dummy[2]; };

            template<typename C>
            static yes_type test(BOOST_DEDUCED_TYPENAME C::size_type x);

            template<typename C>
            static no_type test(...);

        public:
            static const bool value = sizeof(test<T>(0)) == sizeof(yes_type);
        };

        template<typename C, typename Enabler=void>
        struct range_size
        {
            typedef BOOST_DEDUCED_TYPENAME make_unsigned<
                BOOST_DEDUCED_TYPENAME range_difference<C>::type
            >::type type;
        };

        template<typename C>
        struct range_size<
            C,
            BOOST_DEDUCED_TYPENAME ::boost::enable_if<has_size_type<C>, void>::type
        >
        {
            typedef BOOST_DEDUCED_TYPENAME C::size_type type;
        };

    }

    template< class T >
    struct range_size :
        detail::range_size<T>
    {
// Very strange things happen on some compilers that have the range concept
// asserts disabled. This preprocessor condition is clearly redundant on a
// working compiler but is vital for at least some compilers such as clang 4.2
// but only on the Mac!
#if BOOST_RANGE_ENABLE_CONCEPT_ASSERT == 1
        BOOST_RANGE_CONCEPT_ASSERT((boost::SinglePassRangeConcept<T>));
#endif
    };

    template< class T >
    struct range_size<const T >
        : detail::range_size<T>
    {
#if BOOST_RANGE_ENABLE_CONCEPT_ASSERT == 1        
        BOOST_RANGE_CONCEPT_ASSERT((boost::SinglePassRangeConcept<T>));
#endif
    };

} // namespace boost



#endif
