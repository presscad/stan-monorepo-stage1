//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// Copyright (C) 2011 Vicente J. Botet Escriba
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// <boost/thread/locks.hpp>

// template <class Mutex> class unique_lock;

// template <class Clock, class Duration>
//   bool try_lock_until(const chrono::time_point<Clock, Duration>& abs_time);

#include <boost/thread/lock_types.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/detail/lightweight_test.hpp>

#if defined BOOST_THREAD_USES_CHRONO


bool try_lock_until_called = false;

struct mutex
{
  template <class Clock, class Duration>
  bool try_lock_until(const boost::chrono::time_point<Clock, Duration>& abs_time)
  {
    typedef boost::chrono::milliseconds ms;
    BOOST_TEST(Clock::now() - abs_time < ms(5));
    try_lock_until_called = !try_lock_until_called;
    return try_lock_until_called;
  }
  void unlock()
  {
  }
};

mutex m;

int main()
{
  typedef boost::chrono::steady_clock Clock;
  boost::unique_lock<mutex> lk(m, boost::defer_lock);
  BOOST_TEST(lk.try_lock_until(Clock::now()) == true);
  BOOST_TEST(try_lock_until_called == true);
  BOOST_TEST(lk.owns_lock() == true);
  try
  {
    lk.try_lock_until(Clock::now());
    BOOST_TEST(false);
  }
  catch (boost::system::system_error& e)
  {
    BOOST_TEST(e.code().value() == boost::system::errc::resource_deadlock_would_occur);
  }
  lk.unlock();
  BOOST_TEST(lk.try_lock_until(Clock::now()) == false);
  BOOST_TEST(try_lock_until_called == false);
  BOOST_TEST(lk.owns_lock() == false);
  lk.release();
  try
  {
    lk.try_lock_until(Clock::now());
    BOOST_TEST(false);
  }
  catch (boost::system::system_error& e)
  {
    BOOST_TEST(e.code().value() == boost::system::errc::operation_not_permitted);
  }
  return boost::report_errors();
}

#else
#error "Test not applicable: BOOST_THREAD_USES_CHRONO not defined for this platform as not supported"
#endif

