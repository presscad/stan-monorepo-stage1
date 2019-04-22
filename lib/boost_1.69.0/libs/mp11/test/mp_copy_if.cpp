
// Copyright 2015-2017 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt


#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/integral.hpp>
#include <boost/core/lightweight_test_trait.hpp>
#include <type_traits>
#include <tuple>

struct X1 {};
struct X2 {};
struct X3 {};

using boost::mp11::mp_bool;

template<class N> using is_even = mp_bool<N::value % 2 == 0>;

int main()
{
    using boost::mp11::mp_list;
    using boost::mp11::mp_copy_if;

    {
        using L1 = mp_list<>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_copy_if<L1, std::is_const>, L1>));

        using L2 = mp_list<X1, X1 const, X1*, X2 const, X2*, X3*>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_copy_if<L2, std::is_volatile>, L1>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_copy_if<L2, std::is_const>, mp_list<X1 const, X2 const>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_copy_if<L2, std::is_pointer>, mp_list<X1*, X2*, X3*>>));
    }

    {
        using L1 = std::tuple<>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_copy_if<L1, std::is_const>, L1>));

        using L2 = std::tuple<X1, X1 const, X1*, X2 const, X2*, X3*>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_copy_if<L2, std::is_volatile>, L1>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_copy_if<L2, std::is_const>, std::tuple<X1 const, X2 const>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_copy_if<L2, std::is_pointer>, std::tuple<X1*, X2*, X3*>>));
    }

    using boost::mp11::mp_iota_c;
    using boost::mp11::mp_size_t;

    {
        int const N = 12;
        using L1 = mp_iota_c<N>;

        using R1 = mp_copy_if<L1, is_even>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<R1, mp_list<mp_size_t<0>, mp_size_t<2>, mp_size_t<4>, mp_size_t<6>, mp_size_t<8>, mp_size_t<10>>>));
    }

    return boost::report_errors();
}
