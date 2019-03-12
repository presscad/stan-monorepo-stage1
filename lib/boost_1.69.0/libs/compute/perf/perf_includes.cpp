//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/includes.hpp>
#include <boost/compute/container/vector.hpp>

#include "perf.hpp"

int rand_int()
{
    return static_cast<int>((rand() / double(RAND_MAX)) * 25.0);
}

int main(int argc, char *argv[])
{
    perf_parse_args(argc, argv);
    std::cout << "size: " << PERF_N << std::endl;

    // setup context and queue for the default device
    boost::compute::device device = boost::compute::system::default_device();
    boost::compute::context context(device);
    boost::compute::command_queue queue(context, device);
    std::cout << "device: " << device.name() << std::endl;

    // create vectors of random numbers on the host
    std::vector<int> host_vector(PERF_N);
    std::generate(host_vector.begin(), host_vector.end(), rand_int);
    std::sort(host_vector.begin(), host_vector.end());

    // create vectors on the device and copy the data
    boost::compute::vector<int> device_vector(PERF_N, context);
    boost::compute::copy(
        host_vector.begin(), host_vector.end(), device_vector.begin(), queue
    );

    boost::compute::vector<int> device_vector2(PERF_N, context);
    boost::compute::copy(
        host_vector.begin(), host_vector.end(), device_vector2.begin(), queue
    );

    perf_timer t;
    for(size_t trial = 0; trial < PERF_TRIALS; trial++){
        t.start();
        boost::compute::includes(
            device_vector.begin(), device_vector.end(),
            device_vector2.begin(), device_vector2.end(),
            queue
        );
        queue.finish();
        t.stop();
    }
    std::cout << "time: " << t.min_time() / 1e6 << " ms" << std::endl;

    return 0;
}
