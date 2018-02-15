//
// Copyright (c) 2016-2017 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_SPAN_BODY_HPP
#define BOOST_BEAST_HTTP_SPAN_BODY_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/span.hpp>
#include <boost/beast/http/error.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/optional.hpp>

namespace boost {
namespace beast {
namespace http {

/** A @b Body using @ref span

    This body uses @ref span as a memory-based container for
    holding message payloads. The container represents a
    non-owning reference to a continguous area of memory.
    Messages using this body type may be serialized and
    parsed.

    Unlike @ref buffer_body, only one buffer may be provided
    during a parse or serialize operation.
*/
template<class T>
struct span_body
{
private:
    static_assert(std::is_pod<T>::value,
        "POD requirements not met");

public:
    /** The type of container used for the body

        This determines the type of @ref message::body
        when this body type is used with a message container.
    */
    using value_type = span<T>;

    /** Returns the payload size of the body

        When this body is used with @ref message::prepare_payload,
        the Content-Length will be set to the payload size, and
        any chunked Transfer-Encoding will be removed.
    */
    static
    std::uint64_t
    size(value_type const& body)
    {
        return body.size();
    }

    /** The algorithm for parsing the body

        Meets the requirements of @b BodyReader.
    */
#if BOOST_BEAST_DOXYGEN
    using reader = implementation_defined;
#else
    class reader
    {
        value_type& body_;

    public:
        template<bool isRequest, class Fields>
        explicit
        reader(message<isRequest,
                span_body, Fields>& m)
            : body_(m.body())
        {
        }

        void
        init(boost::optional<
            std::uint64_t> const& length, error_code& ec)
        {
            if(length && *length > body_.size())
            {
                ec = error::buffer_overflow;
                return;
            }
            ec.assign(0, ec.category());
        }

        template<class ConstBufferSequence>
        std::size_t
        put(ConstBufferSequence const& buffers,
            error_code& ec)
        {
            using boost::asio::buffer_size;
            using boost::asio::buffer_copy;
            auto const n = buffer_size(buffers);
            auto const len = body_.size();
            if(n > len)
            {
                ec = error::buffer_overflow;
                return 0;
            }
            ec.assign(0, ec.category());
            buffer_copy(boost::asio::buffer(
                body_.data(), n), buffers);
            body_ = value_type{
                body_.data() + n, body_.size() - n};
            return n;
        }

        void
        finish(error_code& ec)
        {
            ec.assign(0, ec.category());
        }
    };
#endif

    /** The algorithm for serializing the body

        Meets the requirements of @b BodyWriter.
    */
#if BOOST_BEAST_DOXYGEN
    using writer = implementation_defined;
#else
    class writer
    {
        value_type const& body_;

    public:
        using const_buffers_type =
            boost::asio::const_buffer;

        template<bool isRequest, class Fields>
        explicit
        writer(message<isRequest,
                span_body, Fields> const& msg)
            : body_(msg.body())
        {
        }

        void
        init(error_code& ec)
        {
            ec.assign(0, ec.category());
        }

        boost::optional<std::pair<const_buffers_type, bool>>
        get(error_code& ec)
        {
            ec.assign(0, ec.category());
            return {{
                { body_.data(),
                  body_.size() * sizeof(typename
                    value_type::value_type)},
                false}};
        }
    };
#endif
};

} // http
} // beast
} // boost

#endif
