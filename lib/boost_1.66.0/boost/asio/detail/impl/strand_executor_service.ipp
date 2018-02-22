//
// detail/impl/strand_executor_service.ipp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IMPL_STRAND_EXECUTOR_SERVICE_IPP
#define BOOST_ASIO_DETAIL_IMPL_STRAND_EXECUTOR_SERVICE_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/strand_executor_service.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

strand_executor_service::strand_executor_service(execution_context& ctx)
  : execution_context_service_base<strand_executor_service>(ctx),
    mutex_(),
    salt_(0),
    impl_list_(0)
{
}

void strand_executor_service::shutdown()
{
  op_queue<scheduler_operation> ops;

  boost::asio::detail::mutex::scoped_lock lock(mutex_);

  strand_impl* impl = impl_list_;
  while (impl)
  {
    ops.push(impl->waiting_queue_);
    ops.push(impl->ready_queue_);
    impl = impl->next_;
  }
}

strand_executor_service::implementation_type
strand_executor_service::create_implementation()
{
  implementation_type new_impl(new strand_impl);
  new_impl->locked_ = false;

  boost::asio::detail::mutex::scoped_lock lock(mutex_);

  // Select a mutex from the pool of shared mutexes.
  std::size_t salt = salt_++;
  std::size_t mutex_index = reinterpret_cast<std::size_t>(new_impl.get());
  mutex_index += (reinterpret_cast<std::size_t>(new_impl.get()) >> 3);
  mutex_index ^= salt + 0x9e3779b9 + (mutex_index << 6) + (mutex_index >> 2);
  mutex_index = mutex_index % num_mutexes;
  if (!mutexes_[mutex_index].get())
    mutexes_[mutex_index].reset(new mutex);
  new_impl->mutex_ = mutexes_[mutex_index].get();

  // Insert implementation into linked list of all implementations.
  new_impl->next_ = impl_list_;
  new_impl->prev_ = 0;
  if (impl_list_)
    impl_list_->prev_ = new_impl.get();
  impl_list_ = new_impl.get();
  new_impl->service_ = this;

  return new_impl;
}

strand_executor_service::strand_impl::~strand_impl()
{
  boost::asio::detail::mutex::scoped_lock lock(service_->mutex_);

  // Remove implementation from linked list of all implementations.
  if (service_->impl_list_ == this)
    service_->impl_list_ = next_;
  if (prev_)
    prev_->next_ = next_;
  if (next_)
    next_->prev_= prev_;
}

bool strand_executor_service::enqueue(const implementation_type& impl,
    scheduler_operation* op)
{
  impl->mutex_->lock();
  if (impl->locked_)
  {
    // Some other function already holds the strand lock. Enqueue for later.
    impl->waiting_queue_.push(op);
    impl->mutex_->unlock();
    return false;
  }
  else
  {
    // The function is acquiring the strand lock and so is responsible for
    // scheduling the strand.
    impl->locked_ = true;
    impl->mutex_->unlock();
    impl->ready_queue_.push(op);
    return true;
  }
}

bool strand_executor_service::running_in_this_thread(
    const implementation_type& impl)
{
  return !!call_stack<strand_impl>::contains(impl.get());
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_IMPL_STRAND_EXECUTOR_SERVICE_IPP
