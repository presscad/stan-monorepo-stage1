
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef CLOCK_H
#define CLOCK_H

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <numeric>
#include <vector>

#include <boost/assert.hpp>

typedef std::chrono::steady_clock  clock_type;
typedef clock_type::duration                duration_type;
typedef clock_type::time_point              time_point_type;

struct clock_overhead
{
    std::uint64_t operator()()
    {
        time_point_type start( clock_type::now() );
        return ( clock_type::now() - start).count();
    }
};

duration_type overhead_clock()
{
    std::size_t iterations( 10);
    std::vector< std::uint64_t >  overhead( iterations, 0);
    for ( std::size_t i = 0; i < iterations; ++i)
        std::generate(
            overhead.begin(), overhead.end(),
            clock_overhead() );
    BOOST_ASSERT( overhead.begin() != overhead.end() );
    return duration_type( std::accumulate( overhead.begin(), overhead.end(), 0) / iterations);
}

#endif // CLOCK_H
