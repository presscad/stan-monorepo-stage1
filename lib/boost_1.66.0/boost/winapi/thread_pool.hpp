/*
 * Copyright 2013 Andrey Semashev
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef BOOST_WINAPI_THREAD_POOL_HPP_INCLUDED_
#define BOOST_WINAPI_THREAD_POOL_HPP_INCLUDED_

#include <boost/winapi/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if BOOST_USE_WINAPI_VERSION >= BOOST_WINAPI_VERSION_WIN2K

#include <boost/winapi/basic_types.hpp>

#if !defined( BOOST_USE_WINDOWS_H )
extern "C" {
#if BOOST_WINAPI_PARTITION_DESKTOP
typedef boost::winapi::VOID_ (NTAPI *WAITORTIMERCALLBACKFUNC)
    (boost::winapi::PVOID_, boost::winapi::BOOLEAN_);
typedef WAITORTIMERCALLBACKFUNC WAITORTIMERCALLBACK;

BOOST_SYMBOL_IMPORT boost::winapi::BOOL_ WINAPI
RegisterWaitForSingleObject(
    boost::winapi::PHANDLE_ phNewWaitObject,
    boost::winapi::HANDLE_ hObject,
    WAITORTIMERCALLBACK Callback,
    boost::winapi::PVOID_ Context,
    boost::winapi::ULONG_ dwMilliseconds,
    boost::winapi::ULONG_ dwFlags);
#endif
} // extern "C"
#endif

// MinGW is buggy - it is missing these function declarations for Win2000
#if !defined( BOOST_USE_WINDOWS_H ) || (defined(BOOST_WINAPI_IS_MINGW) && BOOST_USE_WINAPI_VERSION < BOOST_WINAPI_VERSION_WINXP)
extern "C" {
#if BOOST_WINAPI_PARTITION_DESKTOP
BOOST_SYMBOL_IMPORT boost::winapi::BOOL_ WINAPI
UnregisterWait(boost::winapi::HANDLE_ WaitHandle);
#endif

#if BOOST_WINAPI_PARTITION_DESKTOP || BOOST_WINAPI_PARTITION_SYSTEM
BOOST_SYMBOL_IMPORT boost::winapi::BOOL_ WINAPI
UnregisterWaitEx(
    boost::winapi::HANDLE_ WaitHandle,
    boost::winapi::HANDLE_ CompletionEvent);
#endif
} // extern "C"
#endif

namespace boost {
namespace winapi {

#if BOOST_WINAPI_PARTITION_DESKTOP
typedef ::WAITORTIMERCALLBACKFUNC WAITORTIMERCALLBACKFUNC_;
typedef ::WAITORTIMERCALLBACK WAITORTIMERCALLBACK_;

using ::RegisterWaitForSingleObject;
using ::UnregisterWait;
#endif

#if BOOST_WINAPI_PARTITION_DESKTOP || BOOST_WINAPI_PARTITION_SYSTEM
using ::UnregisterWaitEx;
#endif
#if defined( BOOST_USE_WINDOWS_H )

const ULONG_ WT_EXECUTEDEFAULT_ = WT_EXECUTEDEFAULT;
const ULONG_ WT_EXECUTEINIOTHREAD_ = WT_EXECUTEINIOTHREAD;
#if defined( BOOST_WINAPI_IS_MINGW )
const ULONG_ WT_EXECUTEINUITHREAD_ = 0x00000002;
#else
const ULONG_ WT_EXECUTEINUITHREAD_ = WT_EXECUTEINUITHREAD;
#endif
const ULONG_ WT_EXECUTEINWAITTHREAD_ = WT_EXECUTEINWAITTHREAD;
const ULONG_ WT_EXECUTEONLYONCE_ = WT_EXECUTEONLYONCE;
const ULONG_ WT_EXECUTEINTIMERTHREAD_ = WT_EXECUTEINTIMERTHREAD;
const ULONG_ WT_EXECUTELONGFUNCTION_ = WT_EXECUTELONGFUNCTION;
#if defined( BOOST_WINAPI_IS_MINGW )
const ULONG_ WT_EXECUTEINPERSISTENTIOTHREAD_ = 0x00000040;
#else
const ULONG_ WT_EXECUTEINPERSISTENTIOTHREAD_ = WT_EXECUTEINPERSISTENTIOTHREAD;
#endif
const ULONG_ WT_EXECUTEINPERSISTENTTHREAD_ = WT_EXECUTEINPERSISTENTTHREAD;
const ULONG_ WT_TRANSFER_IMPERSONATION_ = WT_TRANSFER_IMPERSONATION;

#else // defined( BOOST_USE_WINDOWS_H )

const ULONG_ WT_EXECUTEDEFAULT_ = 0x00000000;
const ULONG_ WT_EXECUTEINIOTHREAD_ = 0x00000001;
const ULONG_ WT_EXECUTEINUITHREAD_ = 0x00000002;
const ULONG_ WT_EXECUTEINWAITTHREAD_ = 0x00000004;
const ULONG_ WT_EXECUTEONLYONCE_ = 0x00000008;
const ULONG_ WT_EXECUTEINTIMERTHREAD_ = 0x00000020;
const ULONG_ WT_EXECUTELONGFUNCTION_ = 0x00000010;
const ULONG_ WT_EXECUTEINPERSISTENTIOTHREAD_ = 0x00000040;
const ULONG_ WT_EXECUTEINPERSISTENTTHREAD_ = 0x00000080;
const ULONG_ WT_TRANSFER_IMPERSONATION_ = 0x00000100;

#endif // defined( BOOST_USE_WINDOWS_H )

BOOST_FORCEINLINE BOOST_CONSTEXPR ULONG_ wt_set_max_threadpool_threads(ULONG_ flags, ULONG_ limit) BOOST_NOEXCEPT
{
    // Note: We don't use WT_SET_MAX_THREADPOOL_THREADS here because the way it's defined
    //       the function no longer meets C++11 constexpr requirements.
    return flags | (limit << 16);
}

const ULONG_ wt_execute_default = WT_EXECUTEDEFAULT_;
const ULONG_ wt_execute_in_io_thread = WT_EXECUTEINIOTHREAD_;
const ULONG_ wt_execute_in_ui_thread = WT_EXECUTEINUITHREAD_;
const ULONG_ wt_execute_in_wait_thread = WT_EXECUTEINWAITTHREAD_;
const ULONG_ wt_execute_only_once = WT_EXECUTEONLYONCE_;
const ULONG_ wt_execute_in_timer_thread = WT_EXECUTEINTIMERTHREAD_;
const ULONG_ wt_execute_long_function = WT_EXECUTELONGFUNCTION_;
const ULONG_ wt_execute_in_persistent_io_thread = WT_EXECUTEINPERSISTENTIOTHREAD_;
const ULONG_ wt_execute_in_persistent_thread = WT_EXECUTEINPERSISTENTTHREAD_;
const ULONG_ wt_transfer_impersonation = WT_TRANSFER_IMPERSONATION_;

}
}

#endif // BOOST_USE_WINAPI_VERSION >= BOOST_WINAPI_VERSION_WIN2K
#endif // BOOST_WINAPI_THREAD_POOL_HPP_INCLUDED_
