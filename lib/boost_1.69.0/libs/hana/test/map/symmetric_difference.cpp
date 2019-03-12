// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <boost/hana/assert.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/symmetric_difference.hpp>

#include <laws/base.hpp>
#include <support/minimal_product.hpp>
namespace hana = boost::hana;
using hana::test::ct_eq;


template <int i>
auto key() { return hana::test::ct_eq<i>{}; }

template <int i>
auto val() { return hana::test::ct_eq<-i>{}; }

template <int i, int j>
auto p() { return ::minimal_product(key<i>(), val<j>()); }

int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::symmetric_difference(
            hana::make_map(),
            hana::make_map()
        ),
        hana::make_map()
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::symmetric_difference(
                    hana::make_map(p<1, 1>()),
                    hana::make_map(p<1, 1>())
            ),
            hana::make_map()
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::symmetric_difference(
                    hana::make_map(p<1, 2>()),
                    hana::make_map(p<2, 4>())
            ),
            hana::make_map(p<1, 2>(),
                           p<2, 4>())
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::symmetric_difference(
                    hana::make_map(p<1, 2>(),
                                   p<2, 22>()),
                    hana::make_map(p<2, 4>(),
                                   p<3, 33>())
            ),
            hana::make_map(p<1, 2>(),
                           p<3, 33>())
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::symmetric_difference(
                    hana::make_map(p<1, 2>(),
                                   p<2, 22>(),
                                   p<3, 33>(),
                                   p<5, 55>(),
                                   p<8, 88>()),
                    hana::make_map(p<2, 4>(),
                                   p<3, 33>(),
                                   p<4, 44>(),
                                   p<9, 99>())
            ),
            hana::make_map(p<1, 2>(),
                           p<5, 55>(),
                           p<8, 88>(),
                           p<4, 44>(),
                           p<9, 99>())
    ));
}
