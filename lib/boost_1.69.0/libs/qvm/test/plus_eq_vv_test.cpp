//Copyright (c) 2008-2016 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/qvm/vec_operations.hpp>
#include "test_qvm_vector.hpp"
#include "gold.hpp"

namespace
    {
    template <int Dim>
    void
    test()
        {
        using namespace boost::qvm::sfinae;
        test_qvm::vector<V1,Dim> x(42,2);
            {
            test_qvm::vector<V1,Dim> const y(42,1);
            test_qvm::add_v(x.b,x.a,y.a);
            x+=y;
            BOOST_QVM_TEST_EQ(x.a,x.b);
            }
            {
            test_qvm::vector<V2,Dim> const y(42,1);
            test_qvm::add_v(x.b,x.a,y.a);
            x+=y;
            BOOST_QVM_TEST_EQ(x.a,x.b);
            }
        }
    }

int
main()
    {
    test<2>();
    test<3>();
    test<4>();
    test<5>();
    return boost::report_errors();
    }
