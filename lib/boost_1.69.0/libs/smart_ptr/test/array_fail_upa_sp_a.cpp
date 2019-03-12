//
// Copyright (c) 2012 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//

#include <boost/shared_ptr.hpp>
#include <memory>

struct X
{
};

int main()
{
    std::unique_ptr<X[]> px;
    boost::shared_ptr<X> px2; px2 = px;
}
