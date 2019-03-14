// Boost.Range library
//
//  Copyright Neil Groves 2014. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#include <boost/range/iterator_range_core.hpp>

#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>
#include <string>

namespace boost
{
    namespace
    {
        class str_ref : public boost::iterator_range<const char*>
        {
        public:
            explicit str_ref(const std::string& str)
                : boost::iterator_range<const char*>(
                    str.c_str(), str.c_str() + str.size())
            {
            }
        };

        void test_ticket_6715_iterator_range_equality()
        {
            std::string src("test");
            str_ref a(src);
            str_ref b(src);
            BOOST_CHECK(a == b);
        }
    }
}

boost::unit_test::test_suite*
init_unit_test_suite(int argc, char* argv[])
{
    boost::unit_test::test_suite* test
        = BOOST_TEST_SUITE(
                   "RangeTestSuite.ticket_6715_iterator_range_equality");

    test->add(BOOST_TEST_CASE(
                      &boost::test_ticket_6715_iterator_range_equality));

    return test;
}
