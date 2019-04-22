//---------------------------------------------------------------------------//
// Copyright (c) 2015 Jakub Szuppe <j.szuppe@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#include <iostream>
#include <algorithm>
#include <vector>

#include <bolt/cl/copy.h>
#include <bolt/cl/device_vector.h>
#include <bolt/cl/reduce_by_key.h>

#include "perf.hpp"

int rand_int()
{
    return static_cast<int>((rand() / double(RAND_MAX)) * 25.0);
}

struct unique_key {
  int current;
  int avgValuesNoPerKey;

  unique_key()
  {
      current = 0;
      avgValuesNoPerKey = 512;
  }

  int operator()()
  {
      double p = double(1.0) / static_cast<double>(avgValuesNoPerKey);
      if((rand() / double(RAND_MAX)) <= p)
          return ++current;
      return current;
  }
} UniqueKey;

int main(int argc, char *argv[])
{
    perf_parse_args(argc, argv);

    std::cout << "size: " << PERF_N << std::endl;

    bolt::cl::control ctrl = bolt::cl::control::getDefault();
    ::cl::Device device = ctrl.getDevice();
    std::cout << "device: " << device.getInfo<CL_DEVICE_NAME>() << std::endl;

    // create vector of keys and random values
    std::vector<int> host_keys(PERF_N);
    std::vector<int> host_values(PERF_N);
    std::generate(host_keys.begin(), host_keys.end(), UniqueKey);
    std::generate(host_values.begin(), host_values.end(), rand_int);

    // create device vectors for data
    bolt::cl::device_vector<int> device_keys(PERF_N);
    bolt::cl::device_vector<int> device_values(PERF_N);

    // transfer data to the device
    bolt::cl::copy(host_keys.begin(), host_keys.end(), device_keys.begin());
    bolt::cl::copy(host_values.begin(), host_values.end(), device_values.begin());

    // create device vectors for the results
    bolt::cl::device_vector<int> device_keys_results(PERF_N);
    bolt::cl::device_vector<int> device_values_results(PERF_N);

    typedef bolt::cl::device_vector<int>::iterator iterType;
    bolt::cl::pair<iterType, iterType> result = {
        device_keys_results.begin(),
        device_values_results.begin()
    };

    perf_timer t;
    for(size_t trial = 0; trial < PERF_TRIALS; trial++){
        t.start();
        result = bolt::cl::reduce_by_key(device_keys.begin(),
                                         device_keys.end(),
                                         device_values.begin(),
                                         device_keys_results.begin(),
                                         device_values_results.begin());
        t.stop();
    }
    std::cout << "time: " << t.min_time() / 1e6 << " ms" << std::endl;

    size_t result_size = bolt::cl::distance(device_keys_results.begin(), result.first);
    if(result_size != static_cast<size_t>(host_keys[PERF_N-1] + 1)){
        std::cout << "ERROR: "
                  << "wrong number of keys"
                  << std::endl;
        return -1;
    }

    return 0;
}
