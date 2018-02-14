//
// Copyright (c) 2016-2017 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_IMPL_SERIALIZER_IPP
#define BOOST_BEAST_HTTP_IMPL_SERIALIZER_IPP

#include <boost/beast/core/detail/buffers_ref.hpp>
#include <boost/beast/http/error.hpp>
#include <boost/beast/http/status.hpp>
#include <boost/beast/core/detail/config.hpp>
#include <boost/assert.hpp>
#include <ostream>

namespace boost {
namespace beast {
namespace http {

template<
    bool isRequest, class Body, class Fields>
void
serializer<isRequest, Body, Fields>::
frdinit(std::true_type)
{
    frd_.emplace(m_, m_.version(), m_.method());
}

template<
    bool isRequest, class Body, class Fields>
void
serializer<isRequest, Body, Fields>::
frdinit(std::false_type)
{
    frd_.emplace(m_, m_.version(), m_.result_int());
}

template<
    bool isRequest, class Body, class Fields>
template<std::size_t I, class Visit>
inline
void
serializer<isRequest, Body, Fields>::
do_visit(error_code& ec, Visit& visit)
{
    pv_.template emplace<I>(limit_, v_.template get<I>());
    visit(ec, beast::detail::make_buffers_ref(
        pv_.template get<I>()));
}

//------------------------------------------------------------------------------

template<
    bool isRequest, class Body, class Fields>
serializer<isRequest, Body, Fields>::
serializer(value_type& m)
    : m_(m)
    , rd_(m_)
{
}

template<
    bool isRequest, class Body, class Fields>
template<class Visit>
void
serializer<isRequest, Body, Fields>::
next(error_code& ec, Visit&& visit)
{
    using boost::asio::buffer_size;
    switch(s_)
    {
    case do_construct:
    {
        frdinit(std::integral_constant<bool,
            isRequest>{});
        if(m_.chunked())
            goto go_init_c;
        s_ = do_init;
        BOOST_BEAST_FALLTHROUGH;
    }

    case do_init:
    {
        rd_.init(ec);
        if(ec)
            return;
        if(split_)
            goto go_header_only;
        auto result = rd_.get(ec);
        if(ec == error::need_more)
            goto go_header_only;
        if(ec)
            return;
        if(! result)
            goto go_header_only;
        more_ = result->second;
        v_.template emplace<2>(
            boost::in_place_init,
            frd_->get(),
            result->first);
        s_ = do_header;
        BOOST_BEAST_FALLTHROUGH;
    }

    case do_header:
        do_visit<2>(ec, visit);
        break;

    go_header_only:
        v_.template emplace<1>(frd_->get());
        s_ = do_header_only;
        BOOST_BEAST_FALLTHROUGH;
    case do_header_only:
        do_visit<1>(ec, visit);
        break;

    case do_body:
        s_ = do_body + 1;
        BOOST_BEAST_FALLTHROUGH;

    case do_body + 1:
    {
        auto result = rd_.get(ec);
        if(ec)
            return;
        if(! result)
            goto go_complete;
        more_ = result->second;
        v_.template emplace<3>(result->first);
        s_ = do_body + 2;
        BOOST_BEAST_FALLTHROUGH;
    }

    case do_body + 2:
        do_visit<3>(ec, visit);
        break;

    //----------------------------------------------------------------------

        go_init_c:
        s_ = do_init_c;
        BOOST_BEAST_FALLTHROUGH;
    case do_init_c:
    {
        rd_.init(ec);
        if(ec)
            return;
        if(split_)
            goto go_header_only_c;
        auto result = rd_.get(ec);
        if(ec == error::need_more)
            goto go_header_only_c;
        if(ec)
            return;
        if(! result)
            goto go_header_only_c;
        more_ = result->second;
        if(! more_)
        {
            // do it all in one buffer
            v_.template emplace<7>(
                boost::in_place_init,
                frd_->get(),
                buffer_size(result->first),
                boost::asio::const_buffer{nullptr, 0},
                chunk_crlf{},
                result->first,
                chunk_crlf{},
                detail::chunk_last(),
                boost::asio::const_buffer{nullptr, 0},
                chunk_crlf{});
            goto go_all_c;
        }
        v_.template emplace<4>(
            boost::in_place_init,
            frd_->get(),
            buffer_size(result->first),
            boost::asio::const_buffer{nullptr, 0},
            chunk_crlf{},
            result->first,
            chunk_crlf{});
        s_ = do_header_c;
        BOOST_BEAST_FALLTHROUGH;
    }

    case do_header_c:
        do_visit<4>(ec, visit);
        break;

    go_header_only_c:
        v_.template emplace<1>(frd_->get());
        s_ = do_header_only_c;
    case do_header_only_c:
        do_visit<1>(ec, visit);
        break;

    case do_body_c:
        s_ = do_body_c + 1;
        BOOST_BEAST_FALLTHROUGH;

    case do_body_c + 1:
    {
        auto result = rd_.get(ec);
        if(ec)
            return;
        if(! result)
            goto go_final_c;
        more_ = result->second;
        if(! more_)
        {
            // do it all in one buffer
            v_.template emplace<6>(
                boost::in_place_init,
                buffer_size(result->first),
                boost::asio::const_buffer{nullptr, 0},
                chunk_crlf{},
                result->first,
                chunk_crlf{},
                detail::chunk_last(),
                boost::asio::const_buffer{nullptr, 0},
                chunk_crlf{});
            goto go_body_final_c;
        }
        v_.template emplace<5>(
            boost::in_place_init,
            buffer_size(result->first),
            boost::asio::const_buffer{nullptr, 0},
            chunk_crlf{},
            result->first,
            chunk_crlf{});
        s_ = do_body_c + 2;
        BOOST_BEAST_FALLTHROUGH;
    }

    case do_body_c + 2:
        do_visit<5>(ec, visit);
        break;

    go_body_final_c:
        s_ = do_body_final_c;
        BOOST_BEAST_FALLTHROUGH;
    case do_body_final_c:
        do_visit<6>(ec, visit);
        break;

    go_all_c:
        s_ = do_all_c;
        BOOST_BEAST_FALLTHROUGH;
    case do_all_c:
        do_visit<7>(ec, visit);
        break;

    go_final_c:
    case do_final_c:
        v_.template emplace<8>(
            boost::in_place_init,
            detail::chunk_last(),
            boost::asio::const_buffer{nullptr, 0},
            chunk_crlf{});
        s_ = do_final_c + 1;
        BOOST_BEAST_FALLTHROUGH;

    case do_final_c + 1:
        do_visit<8>(ec, visit);
        break;

    //----------------------------------------------------------------------

    default:
    case do_complete:
        BOOST_ASSERT(false);
        break;

    go_complete:
        s_ = do_complete;
        break;
    }
}

template<
    bool isRequest, class Body, class Fields>
void
serializer<isRequest, Body, Fields>::
consume(std::size_t n)
{
    using boost::asio::buffer_size;
    switch(s_)
    {
    case do_header:
        BOOST_ASSERT(
            n <= buffer_size(v_.template get<2>()));
        v_.template get<2>().consume(n);
        if(buffer_size(v_.template get<2>()) > 0)
            break;
        header_done_ = true;
        v_.reset();
        if(! more_)
            goto go_complete;
        s_ = do_body + 1;
        break;

    case do_header_only:
        BOOST_ASSERT(
            n <= buffer_size(v_.template get<1>()));
        v_.template get<1>().consume(n);
        if(buffer_size(v_.template get<1>()) > 0)
            break;
        frd_ = boost::none;
        header_done_ = true;
        if(! split_)
            goto go_complete;
        s_ = do_body;
        break;

    case do_body + 2:
    {
        BOOST_ASSERT(
            n <= buffer_size(v_.template get<3>()));
        v_.template get<3>().consume(n);
        if(buffer_size(v_.template get<3>()) > 0)
            break;
        v_.reset();
        if(! more_)
            goto go_complete;
        s_ = do_body + 1;
        break;
    }

    //----------------------------------------------------------------------

    case do_header_c:
        BOOST_ASSERT(
            n <= buffer_size(v_.template get<4>()));
        v_.template get<4>().consume(n);
        if(buffer_size(v_.template get<4>()) > 0)
            break;
        header_done_ = true;
        v_.reset();
        if(more_)
            s_ = do_body_c + 1;
        else
            s_ = do_final_c;
        break;

    case do_header_only_c:
    {
        BOOST_ASSERT(
            n <= buffer_size(v_.template get<1>()));
        v_.template get<1>().consume(n);
        if(buffer_size(v_.template get<1>()) > 0)
            break;
        frd_ = boost::none;
        header_done_ = true;
        if(! split_)
        {
            s_ = do_final_c;
            break;
        }
        s_ = do_body_c;
        break;
    }

    case do_body_c + 2:
        BOOST_ASSERT(
            n <= buffer_size(v_.template get<5>()));
        v_.template get<5>().consume(n);
        if(buffer_size(v_.template get<5>()) > 0)
            break;
        v_.reset();
        if(more_)
            s_ = do_body_c + 1;
        else
            s_ = do_final_c;
        break;

    case do_body_final_c:
    {
        BOOST_ASSERT(
            n <= buffer_size(v_.template get<6>()));
        v_.template get<6>().consume(n);
        if(buffer_size(v_.template get<6>()) > 0)
            break;
        v_.reset();
        s_ = do_complete;
        break;
    }

    case do_all_c:
    {
        BOOST_ASSERT(
            n <= buffer_size(v_.template get<7>()));
        v_.template get<7>().consume(n);
        if(buffer_size(v_.template get<7>()) > 0)
            break;
        header_done_ = true;
        v_.reset();
        s_ = do_complete;
        break;
    }

    case do_final_c + 1:
        BOOST_ASSERT(buffer_size(v_.template get<8>()));
        v_.template get<8>().consume(n);
        if(buffer_size(v_.template get<8>()) > 0)
            break;
        v_.reset();
        goto go_complete;

    //----------------------------------------------------------------------

    default:
        BOOST_ASSERT(false);
    case do_complete:
        break;

    go_complete:
        s_ = do_complete;
        break;
    }
}

} // http
} // beast
} // boost

#endif
