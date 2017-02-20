/*!
@file
Defines `boost::hana::Metafunction`.

@copyright Louis Dionne 2013-2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_METAFUNCTION_HPP
#define BOOST_HANA_CONCEPT_METAFUNCTION_HPP

#include <boost/hana/fwd/concept/metafunction.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename F, typename Tag = typename tag_of<F>::type>
        struct metafunction_dispatch {
            static constexpr bool value = Metafunction<Tag>::value;
        };

        template <typename F>
        struct metafunction_dispatch<F, F> {
            static constexpr bool value = false;
        };
    }

    template <typename F>
    struct Metafunction
        : detail::metafunction_dispatch<F>
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_METAFUNCTION_HPP
