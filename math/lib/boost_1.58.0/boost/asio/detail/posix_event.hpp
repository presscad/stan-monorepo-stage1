//
// detail/posix_event.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_POSIX_EVENT_HPP
#define BOOST_ASIO_DETAIL_POSIX_EVENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_PTHREADS)

#include <pthread.h>
#include <boost/asio/detail/assert.hpp>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class posix_event
  : private noncopyable
{
public:
  // Constructor.
  BOOST_ASIO_DECL posix_event();

  // Destructor.
  ~posix_event()
  {
    ::pthread_cond_destroy(&cond_);
  }

  // Signal the event. (Retained for backward compatibility.)
  template <typename Lock>
  void signal(Lock& lock)
  {
    this->signal_all(lock);
  }

  // Signal all waiters.
  template <typename Lock>
  void signal_all(Lock& lock)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    (void)lock;
    state_ |= 1;
    ::pthread_cond_broadcast(&cond_); // Ignore EINVAL.
  }

  // Unlock the mutex and signal one waiter.
  template <typename Lock>
  void unlock_and_signal_one(Lock& lock)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    state_ |= 1;
    bool have_waiters = (state_ > 1);
    lock.unlock();
    if (have_waiters)
      ::pthread_cond_signal(&cond_); // Ignore EINVAL.
  }

  // If there's a waiter, unlock the mutex and signal it.
  template <typename Lock>
  bool maybe_unlock_and_signal_one(Lock& lock)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    state_ |= 1;
    if (state_ > 1)
    {
      lock.unlock();
      ::pthread_cond_signal(&cond_); // Ignore EINVAL.
      return true;
    }
    return false;
  }

  // Reset the event.
  template <typename Lock>
  void clear(Lock& lock)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    (void)lock;
    state_ &= ~std::size_t(1);
  }

  // Wait for the event to become signalled.
  template <typename Lock>
  void wait(Lock& lock)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    while ((state_ & 1) == 0)
    {
      state_ += 2;
      ::pthread_cond_wait(&cond_, &lock.mutex().mutex_); // Ignore EINVAL.
      state_ -= 2;
    }
  }

private:
  ::pthread_cond_t cond_;
  std::size_t state_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/posix_event.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_PTHREADS)

#endif // BOOST_ASIO_DETAIL_POSIX_EVENT_HPP
