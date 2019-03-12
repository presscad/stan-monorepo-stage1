/*<-
Copyright Barrett Adair 2016-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

#include <boost/callable_traits/detail/config.hpp>
#ifdef BOOST_CLBL_TRTS_DISABLE_REFERENCE_QUALIFIERS
int main(){ return 0; }
#else

//[ add_member_volatile
#include <type_traits>
#include <boost/callable_traits/add_member_volatile.hpp>

namespace ct = boost::callable_traits;

struct foo {};

int main() {

    {
        using pmf = void(foo::*)();
        using expect = void(foo::*)() volatile;
        using test = ct::add_member_volatile_t<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_member_volatile_t doesn't change anything when
        // the function type is already volatile.
        using pmf = void(foo::*)() volatile &&;
        using expect = void(foo::*)() volatile &&;
        using test = ct::add_member_volatile_t<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        using pmf = void(foo::*)() const &;
        using expect = void(foo::*)() const volatile &;
        using test = ct::add_member_volatile_t<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_member_volatile_t can also be used with "abominable"
        // function types.
        using f = void();
        using expect = void() volatile;
        using test = ct::add_member_volatile_t<f>;
        static_assert(std::is_same<test, expect>::value, "");
    }
}

//]
#endif //#ifdef BOOST_CLBL_TRTS_DISABLE_REFERENCE_QUALIFIERS
