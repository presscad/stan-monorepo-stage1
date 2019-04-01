//
// Copyright (c) 2012 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//

#include <boost/shared_ptr.hpp>

struct X
{
};

template<class T> void f( T & /*t*/ )
{
}

int main()
{
    boost::shared_ptr<X> px( new X );
    f( px[ 0 ] );
}
