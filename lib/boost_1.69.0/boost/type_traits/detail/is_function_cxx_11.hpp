
//  Copyright 2000 John Maddock (john@johnmaddock.co.uk)
//  Copyright 2002 Aleksey Gurtovoy (agurtovoy@meta-comm.com)
//
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef BOOST_TT_IS_FUNCTION_CXX_11_HPP_INCLUDED
#define BOOST_TT_IS_FUNCTION_CXX_11_HPP_INCLUDED

#include <boost/type_traits/integral_constant.hpp>

namespace boost {

   template <class T>
   struct is_function : public false_type {};

#if defined(__cpp_noexcept_function_type) && !defined(_MSC_VER)
#define BOOST_TT_NOEXCEPT_PARAM , bool NE
#define BOOST_TT_NOEXCEPT_DECL noexcept(NE)
#else
#define BOOST_TT_NOEXCEPT_PARAM
#define BOOST_TT_NOEXCEPT_DECL
#endif

#ifdef _MSC_VER
#define BOOST_TT_DEF_CALL __cdecl
#else
#define BOOST_TT_DEF_CALL
#endif
   
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret BOOST_TT_DEF_CALL(Args...)BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class ...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret(Args..., ...)BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // const qualified:
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret BOOST_TT_DEF_CALL(Args...)const BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class ...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret(Args..., ...)const BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // volatile:
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret BOOST_TT_DEF_CALL(Args...)volatile BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class ...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret(Args..., ...)volatile BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // const volatile
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret BOOST_TT_DEF_CALL(Args...)const volatile BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class ...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret(Args..., ...)const volatile BOOST_TT_NOEXCEPT_DECL> : public true_type {};

   // Reference qualified:

   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret BOOST_TT_DEF_CALL(Args...)& BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class ...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret(Args..., ...)& BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // const qualified:
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret BOOST_TT_DEF_CALL(Args...)const & BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class ...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret(Args..., ...)const & BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // volatile:
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret BOOST_TT_DEF_CALL(Args...)volatile & BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class ...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret(Args..., ...)volatile & BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // const volatile
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret BOOST_TT_DEF_CALL(Args...)const volatile & BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class ...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret(Args..., ...)const volatile & BOOST_TT_NOEXCEPT_DECL> : public true_type {};

   // rvalue reference qualified:

   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret BOOST_TT_DEF_CALL(Args...)&& BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class ...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret(Args..., ...)&& BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // const qualified:
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret BOOST_TT_DEF_CALL(Args...)const && BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class ...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret(Args..., ...)const && BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // volatile:
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret BOOST_TT_DEF_CALL(Args...)volatile && BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class ...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret(Args..., ...)volatile && BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // const volatile
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret BOOST_TT_DEF_CALL(Args...)const volatile && BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class ...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret(Args..., ...)const volatile && BOOST_TT_NOEXCEPT_DECL> : public true_type {};

#ifdef _MSC_VER
#ifdef __CLR_VER
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __clrcall(Args...)BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
#ifndef _M_AMD64
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __stdcall(Args...)BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __fastcall(Args...)BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __vectorcall(Args...)BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // const:
#ifdef __CLR_VER
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __clrcall(Args...)const BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
#ifndef _M_AMD64
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __stdcall(Args...)const BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __fastcall(Args...)const BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __vectorcall(Args...)const BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // volatile:
#ifdef __CLR_VER
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __clrcall(Args...)volatile BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
#ifndef _M_AMD64
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __stdcall(Args...)volatile BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __fastcall(Args...)volatile BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __vectorcall(Args...)volatile BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // const volatile:
#ifdef __CLR_VER
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __clrcall(Args...)const volatile BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
#ifndef _M_AMD64
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __stdcall(Args...)const volatile BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __fastcall(Args...)const volatile BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __vectorcall(Args...)const volatile BOOST_TT_NOEXCEPT_DECL> : public true_type {};

   // reference qualified:
#ifdef __CLR_VER
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __clrcall(Args...)&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
#ifndef _M_AMD64
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __stdcall(Args...)&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __fastcall(Args...)&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __vectorcall(Args...)&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // const:
#ifdef __CLR_VER
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __clrcall(Args...)const &BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
#ifndef _M_AMD64
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __stdcall(Args...)const &BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __fastcall(Args...)const &BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __vectorcall(Args...)const &BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // volatile:
#ifdef __CLR_VER
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __clrcall(Args...)volatile &BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
#ifndef _M_AMD64
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __stdcall(Args...)volatile &BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __fastcall(Args...)volatile &BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __vectorcall(Args...)volatile &BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // const volatile:
#ifdef __CLR_VER
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __clrcall(Args...)const volatile &BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
#ifndef _M_AMD64
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __stdcall(Args...)const volatile &BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __fastcall(Args...)const volatile &BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __vectorcall(Args...)const volatile &BOOST_TT_NOEXCEPT_DECL> : public true_type {};

   // rvalue reference qualified:
#ifdef __CLR_VER
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __clrcall(Args...)&&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
#ifndef _M_AMD64
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __stdcall(Args...)&&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __fastcall(Args...)&&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __vectorcall(Args...)&&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // const:
#ifdef __CLR_VER
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __clrcall(Args...)const &&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
#ifndef _M_AMD64
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __stdcall(Args...)const &&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __fastcall(Args...)const &&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __vectorcall(Args...)const &&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // volatile:
#ifdef __CLR_VER
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __clrcall(Args...)volatile &&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
#ifndef _M_AMD64
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __stdcall(Args...)volatile &&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __fastcall(Args...)volatile &&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __vectorcall(Args...)volatile &&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // const volatile:
#ifdef __CLR_VER
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __clrcall(Args...)const volatile &&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
#ifndef _M_AMD64
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __stdcall(Args...)const volatile &&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __fastcall(Args...)const volatile &&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __vectorcall(Args...)const volatile &&BOOST_TT_NOEXCEPT_DECL> : public true_type {};

#endif // _MSC_VER

   // All over again for msvc with noexcept:

#if defined(_MSVC_LANG) && (_MSVC_LANG >= 201703) 

#undef BOOST_TT_NOEXCEPT_DECL
#define BOOST_TT_NOEXCEPT_DECL noexcept

   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret BOOST_TT_DEF_CALL(Args...)BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class ...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret(Args..., ...)BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // const qualified:
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret BOOST_TT_DEF_CALL(Args...)const BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class ...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret(Args..., ...)const BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // volatile:
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret BOOST_TT_DEF_CALL(Args...)volatile BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class ...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret(Args..., ...)volatile BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // const volatile
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret BOOST_TT_DEF_CALL(Args...)const volatile BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class ...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret(Args..., ...)const volatile BOOST_TT_NOEXCEPT_DECL> : public true_type {};

   // Reference qualified:

   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret BOOST_TT_DEF_CALL(Args...)& BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class ...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret(Args..., ...)& BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // const qualified:
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret BOOST_TT_DEF_CALL(Args...)const & BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class ...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret(Args..., ...)const & BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // volatile:
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret BOOST_TT_DEF_CALL(Args...)volatile & BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class ...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret(Args..., ...)volatile & BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // const volatile
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret BOOST_TT_DEF_CALL(Args...)const volatile & BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class ...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret(Args..., ...)const volatile & BOOST_TT_NOEXCEPT_DECL> : public true_type {};

   // rvalue reference qualified:

   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret BOOST_TT_DEF_CALL(Args...) && BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class ...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret(Args..., ...) && BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // const qualified:
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret BOOST_TT_DEF_CALL(Args...)const && BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class ...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret(Args..., ...)const && BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // volatile:
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret BOOST_TT_DEF_CALL(Args...)volatile && BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class ...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret(Args..., ...)volatile && BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // const volatile
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret BOOST_TT_DEF_CALL(Args...)const volatile && BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class ...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret(Args..., ...)const volatile && BOOST_TT_NOEXCEPT_DECL> : public true_type {};

#ifdef _MSC_VER
#ifdef __CLR_VER
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __clrcall(Args...)BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
#ifndef _M_AMD64
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __stdcall(Args...)BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __fastcall(Args...)BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __vectorcall(Args...)BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // const:
#ifdef __CLR_VER
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __clrcall(Args...)const BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
#ifndef _M_AMD64
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __stdcall(Args...)const BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __fastcall(Args...)const BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __vectorcall(Args...)const BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // volatile:
#ifdef __CLR_VER
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __clrcall(Args...)volatile BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
#ifndef _M_AMD64
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __stdcall(Args...)volatile BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __fastcall(Args...)volatile BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __vectorcall(Args...)volatile BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // const volatile:
#ifdef __CLR_VER
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __clrcall(Args...)const volatile BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
#ifndef _M_AMD64
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __stdcall(Args...)const volatile BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __fastcall(Args...)const volatile BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __vectorcall(Args...)const volatile BOOST_TT_NOEXCEPT_DECL> : public true_type {};

   // reference qualified:
#ifdef __CLR_VER
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __clrcall(Args...)&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
#ifndef _M_AMD64
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __stdcall(Args...)&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __fastcall(Args...)&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __vectorcall(Args...)&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // const:
#ifdef __CLR_VER
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __clrcall(Args...)const &BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
#ifndef _M_AMD64
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __stdcall(Args...)const &BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __fastcall(Args...)const &BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __vectorcall(Args...)const &BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // volatile:
#ifdef __CLR_VER
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __clrcall(Args...)volatile &BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
#ifndef _M_AMD64
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __stdcall(Args...)volatile &BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __fastcall(Args...)volatile &BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __vectorcall(Args...)volatile &BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // const volatile:
#ifdef __CLR_VER
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __clrcall(Args...)const volatile &BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
#ifndef _M_AMD64
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __stdcall(Args...)const volatile &BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __fastcall(Args...)const volatile &BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __vectorcall(Args...)const volatile &BOOST_TT_NOEXCEPT_DECL> : public true_type {};

   // rvalue reference qualified:
#ifdef __CLR_VER
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __clrcall(Args...) && BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
#ifndef _M_AMD64
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __stdcall(Args...) && BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __fastcall(Args...) && BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __vectorcall(Args...) && BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // const:
#ifdef __CLR_VER
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __clrcall(Args...)const &&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
#ifndef _M_AMD64
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __stdcall(Args...)const &&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __fastcall(Args...)const &&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __vectorcall(Args...)const &&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // volatile:
#ifdef __CLR_VER
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __clrcall(Args...)volatile &&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
#ifndef _M_AMD64
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __stdcall(Args...)volatile &&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __fastcall(Args...)volatile &&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __vectorcall(Args...)volatile &&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   // const volatile:
#ifdef __CLR_VER
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __clrcall(Args...)const volatile &&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
#ifndef _M_AMD64
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __stdcall(Args...)const volatile &&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __fastcall(Args...)const volatile &&BOOST_TT_NOEXCEPT_DECL> : public true_type {};
#endif
   template <class Ret, class...Args BOOST_TT_NOEXCEPT_PARAM>
   struct is_function<Ret __vectorcall(Args...)const volatile &&BOOST_TT_NOEXCEPT_DECL> : public true_type {};

#endif // _MSC_VER

#endif

}

#undef BOOST_TT_NOEXCEPT_DECL
#undef BOOST_TT_NOEXCEPT_PARAM
#undef BOOST_TT_DEF_CALL

#endif // BOOST_TT_IS_FUNCTION_CXX_11_HPP_INCLUDED

