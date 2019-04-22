/*
 *             Copyright Andrey Semashev 2018.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   semaphore_abi.cpp
 * \author Andrey Semashev
 * \date   10.03.2018
 *
 * \brief  This file contains ABI test for semaphore.hpp
 */

#include <boost/winapi/semaphore.hpp>
#include <windows.h>
#include "abi_test_tools.hpp"

int main()
{
#if BOOST_WINAPI_PARTITION_APP_SYSTEM

    BOOST_WINAPI_TEST_CONSTANT(SEMAPHORE_ALL_ACCESS);
    BOOST_WINAPI_TEST_CONSTANT(SEMAPHORE_MODIFY_STATE);

    BOOST_WINAPI_TEST_FUNCTION_SIGNATURE(ReleaseSemaphore);

#endif // BOOST_WINAPI_PARTITION_APP_SYSTEM

#if BOOST_WINAPI_PARTITION_DESKTOP_SYSTEM

#if !defined( BOOST_NO_ANSI_APIS )
    BOOST_WINAPI_TEST_FUNCTION_SIGNATURE(OpenSemaphoreA);
#endif // !defined( BOOST_NO_ANSI_APIS )
    BOOST_WINAPI_TEST_FUNCTION_SIGNATURE(OpenSemaphoreW);

#endif // BOOST_WINAPI_PARTITION_DESKTOP_SYSTEM

    return boost::report_errors();
}
