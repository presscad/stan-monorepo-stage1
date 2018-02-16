//
// Copyright (c) 2016-2017 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_TYPE_TRAITS_HPP
#define BOOST_BEAST_DETAIL_TYPE_TRAITS_HPP

#include <boost/beast/core/error.hpp>
#include <boost/asio/buffer.hpp>
#include <iterator>
#include <tuple>
#include <type_traits>
#include <string>
#include <utility>

namespace boost {
namespace beast {
namespace detail {

//
// utilities
//

template<class... Ts>
struct make_void
{
    using type = void;
};

template<class... Ts>
using void_t = typename make_void<Ts...>::type;

template<class T>
inline
void
accept_rv(T){}

template<class U>
std::size_t constexpr
max_sizeof()
{
    return sizeof(U);
}

template<class U0, class U1, class... Us>
std::size_t constexpr
max_sizeof()
{
    return
        max_sizeof<U0>() > max_sizeof<U1, Us...>() ?
        max_sizeof<U0>() : max_sizeof<U1, Us...>();
}

template<class U>
std::size_t constexpr
max_alignof()
{
    return alignof(U);
}

template<class U0, class U1, class... Us>
std::size_t constexpr
max_alignof()
{
    return
        max_alignof<U0>() > max_alignof<U1, Us...>() ?
        max_alignof<U0>() : max_alignof<U1, Us...>();
}

template<unsigned N, class T, class... Tn>
struct repeat_tuple_impl
{
    using type = typename repeat_tuple_impl<
        N - 1, T, T, Tn...>::type;
};

template<class T, class... Tn>
struct repeat_tuple_impl<0, T, Tn...>
{
    using type = std::tuple<T, Tn...>;
};

template<unsigned N, class T>
struct repeat_tuple
{
    using type =
        typename repeat_tuple_impl<N-1, T>::type;
};

template<class T>
struct repeat_tuple<0, T>
{
    using type = std::tuple<>;
};

template<class R, class C, class ...A>
auto
is_invocable_test(C&& c, int, A&& ...a)
    -> decltype(std::is_convertible<
        decltype(c(std::forward<A>(a)...)), R>::value ||
            std::is_same<R, void>::value,
                std::true_type());

template<class R, class C, class ...A>
std::false_type
is_invocable_test(C&& c, long, A&& ...a);

/** Metafunction returns `true` if F callable as R(A...)

    Example:

    @code
        is_invocable<T, void(std::string)>
    @endcode
*/
/** @{ */
template<class C, class F>
struct is_invocable : std::false_type
{
};

template<class C, class R, class ...A>
struct is_invocable<C, R(A...)>
    : decltype(is_invocable_test<R>(
        std::declval<C>(), 1, std::declval<A>()...))
{
};
/** @} */

// for span
template<class T, class E, class = void>
struct is_contiguous_container: std::false_type {};

template<class T, class E>
struct is_contiguous_container<T, E, void_t<
    decltype(
        std::declval<std::size_t&>() = std::declval<T const&>().size(),
        std::declval<E*&>() = std::declval<T&>().data(),
        (void)0),
    typename std::enable_if<
        std::is_same<
            typename std::remove_cv<E>::type,
            typename std::remove_cv<
                typename std::remove_pointer<
                    decltype(std::declval<T&>().data())
                >::type
            >::type
        >::value
    >::type>>: std::true_type
{};

template<class...>
struct unwidest_unsigned;

template<class U0>
struct unwidest_unsigned<U0>
{
    using type = U0;
};

template<class U0, class... UN>
struct unwidest_unsigned<U0, UN...>
{
    BOOST_STATIC_ASSERT(std::is_unsigned<U0>::value);
    using type = typename std::conditional<
        (sizeof(U0) < sizeof(typename unwidest_unsigned<UN...>::type)),
        U0, typename unwidest_unsigned<UN...>::type>::type;
};

template<class...>
struct widest_unsigned;

template<class U0>
struct widest_unsigned<U0>
{
    using type = U0;
};

template<class U0, class... UN>
struct widest_unsigned<U0, UN...>
{
    BOOST_STATIC_ASSERT(std::is_unsigned<U0>::value);
    using type = typename std::conditional<
        (sizeof(U0) > sizeof(typename widest_unsigned<UN...>::type)),
        U0, typename widest_unsigned<UN...>::type>::type;
};

template<class U>
inline
constexpr
U
min_all(U u)
{
    BOOST_STATIC_ASSERT(std::is_unsigned<U>::value);
    return u;
}

template<class U0, class U1, class... UN>
inline
constexpr
typename unwidest_unsigned<U0, U1, UN...>::type
min_all(U0 u0, U1 u1, UN... un)
{
    using type =
        typename unwidest_unsigned<U0, U1, UN...>::type;
    return u0 < u1 ?
        static_cast<type>(min_all(u0, un...)) :
        static_cast<type>(min_all(u1, un...));
}

template<class U>
inline
constexpr
U
max_all(U u)
{
    BOOST_STATIC_ASSERT(std::is_unsigned<U>::value);
    return u;
}

template<class U0, class U1, class... UN>
inline
constexpr
typename widest_unsigned<U0, U1, UN...>::type
max_all(U0 u0, U1 u1, UN... un)
{
    return u0 > u1? max_all(u0, un...) : max_all(u1, un...);
}

//------------------------------------------------------------------------------

//
// buffer concepts
//

// Types that meet the requirements,
// for use with std::declval only.
template<class BufferType>
struct BufferSequence
{
    using value_type = BufferType;
    using const_iterator = BufferType const*;
    ~BufferSequence();
    BufferSequence(BufferSequence const&) = default;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
};
using ConstBufferSequence =
    BufferSequence<boost::asio::const_buffer>;
using MutableBufferSequence =
    BufferSequence<boost::asio::mutable_buffer>;

template<class B1, class... Bn>
struct is_all_const_buffer_sequence
    : std::integral_constant<bool,
        boost::asio::is_const_buffer_sequence<B1>::value &&
        is_all_const_buffer_sequence<Bn...>::value>
{
};

template<class B>
struct is_all_const_buffer_sequence<B>
    : boost::asio::is_const_buffer_sequence<B>
{
};

template<class... Bn>
struct common_buffers_type
{
    using type = typename std::conditional<
        std::is_convertible<std::tuple<Bn...>,
            typename repeat_tuple<sizeof...(Bn),
                boost::asio::mutable_buffer>::type>::value,
                    boost::asio::mutable_buffer,
                        boost::asio::const_buffer>::type;
};

template<class B>
struct buffer_sequence_iterator
{
    using type = decltype(
        boost::asio::buffer_sequence_begin(
            std::declval<B const&>()));
};

// Types that meet the requirements,
// for use with std::declval only.
struct StreamHandler
{
    StreamHandler(StreamHandler const&) = default;
    void operator()(error_code ec, std::size_t);
};
using ReadHandler = StreamHandler;
using WriteHandler = StreamHandler;

template<class Buffers>
class buffers_range_adapter
{
    Buffers const& b_;

public:
    using value_type = typename std::conditional<
        std::is_convertible<typename std::iterator_traits<
            typename buffer_sequence_iterator<Buffers>::type>::value_type,
                boost::asio::const_buffer>::value,
        boost::asio::const_buffer,
        boost::asio::mutable_buffer>::type;

    /* VFALCO This isn't right, because range-for will pick up the iterator's
              value_type which might not be const_buffer or mutable_buffer. We
              need to declare our own iterator wrapper that converts the underlying
              iterator's value_type to const_buffer or mutable_buffer so that
              range-for sees one of those types.
    */
    using const_iterator = typename
        buffer_sequence_iterator<Buffers>::type;

    explicit
    buffers_range_adapter(Buffers const& b)
        : b_(b)
    {
    }

    const_iterator
    begin() const noexcept
    {
        return boost::asio::buffer_sequence_begin(b_);
    }

    const_iterator
    end() const noexcept
    {
        return boost::asio::buffer_sequence_end(b_);
    }
};

template<class Buffers>
buffers_range_adapter<Buffers>
buffers_range(Buffers const& buffers)
{
    return buffers_range_adapter<Buffers>{buffers};
}

} // detail
} // beast
} // boost

#endif
