
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(BOOST_VMD_DETAIL_IS_TYPE_REGISTRATION_HPP)
#define BOOST_VMD_DETAIL_IS_TYPE_REGISTRATION_HPP

#define BOOST_VMD_REGISTER_BOOST_VMD_TYPE_UNKNOWN (BOOST_VMD_TYPE_UNKNOWN)
#define BOOST_VMD_REGISTER_BOOST_VMD_TYPE_EMPTY (BOOST_VMD_TYPE_EMPTY)
#define BOOST_VMD_REGISTER_BOOST_VMD_TYPE_ARRAY (BOOST_VMD_TYPE_ARRAY)
#define BOOST_VMD_REGISTER_BOOST_VMD_TYPE_LIST (BOOST_VMD_TYPE_LIST)
#define BOOST_VMD_REGISTER_BOOST_VMD_TYPE_SEQ (BOOST_VMD_TYPE_SEQ)
#define BOOST_VMD_REGISTER_BOOST_VMD_TYPE_TUPLE (BOOST_VMD_TYPE_TUPLE)
#define BOOST_VMD_REGISTER_BOOST_VMD_TYPE_IDENTIFIER (BOOST_VMD_TYPE_IDENTIFIER)
#define BOOST_VMD_REGISTER_BOOST_VMD_TYPE_NUMBER (BOOST_VMD_TYPE_NUMBER)
#define BOOST_VMD_REGISTER_BOOST_VMD_TYPE_SEQUENCE (BOOST_VMD_TYPE_SEQUENCE)
#define BOOST_VMD_REGISTER_BOOST_VMD_TYPE_TYPE (BOOST_VMD_TYPE_TYPE)

#define BOOST_VMD_DETECT_BOOST_VMD_TYPE_UNKNOWN_BOOST_VMD_TYPE_UNKNOWN
#define BOOST_VMD_DETECT_BOOST_VMD_TYPE_EMPTY_BOOST_VMD_TYPE_EMPTY
#define BOOST_VMD_DETECT_BOOST_VMD_TYPE_ARRAY_BOOST_VMD_TYPE_ARRAY
#define BOOST_VMD_DETECT_BOOST_VMD_TYPE_LIST_BOOST_VMD_TYPE_LIST
#define BOOST_VMD_DETECT_BOOST_VMD_TYPE_SEQ_BOOST_VMD_TYPE_SEQ
#define BOOST_VMD_DETECT_BOOST_VMD_TYPE_TUPLE_BOOST_VMD_TYPE_TUPLE
#define BOOST_VMD_DETECT_BOOST_VMD_TYPE_IDENTIFIER_BOOST_VMD_TYPE_IDENTIFIER
#define BOOST_VMD_DETECT_BOOST_VMD_TYPE_NUMBER_BOOST_VMD_TYPE_NUMBER
#define BOOST_VMD_DETECT_BOOST_VMD_TYPE_SEQUENCE_BOOST_VMD_TYPE_SEQUENCE
#define BOOST_VMD_DETECT_BOOST_VMD_TYPE_TYPE_BOOST_VMD_TYPE_TYPE

#define BOOST_VMD_SUBTYPE_REGISTER_BOOST_VMD_TYPE_UNKNOWN (BOOST_VMD_TYPE_TYPE,BOOST_VMD_TYPE_UNKNOWN)
#define BOOST_VMD_SUBTYPE_REGISTER_BOOST_VMD_TYPE_EMPTY (BOOST_VMD_TYPE_TYPE,BOOST_VMD_TYPE_EMPTY)
#define BOOST_VMD_SUBTYPE_REGISTER_BOOST_VMD_TYPE_ARRAY (BOOST_VMD_TYPE_TYPE,BOOST_VMD_TYPE_ARRAY)
#define BOOST_VMD_SUBTYPE_REGISTER_BOOST_VMD_TYPE_LIST (BOOST_VMD_TYPE_TYPE,BOOST_VMD_TYPE_LIST)
#define BOOST_VMD_SUBTYPE_REGISTER_BOOST_VMD_TYPE_SEQ (BOOST_VMD_TYPE_TYPE,BOOST_VMD_TYPE_SEQ)
#define BOOST_VMD_SUBTYPE_REGISTER_BOOST_VMD_TYPE_TUPLE (BOOST_VMD_TYPE_TYPE,BOOST_VMD_TYPE_TUPLE)
#define BOOST_VMD_SUBTYPE_REGISTER_BOOST_VMD_TYPE_IDENTIFIER (BOOST_VMD_TYPE_TYPE,BOOST_VMD_TYPE_IDENTIFIER)
#define BOOST_VMD_SUBTYPE_REGISTER_BOOST_VMD_TYPE_NUMBER (BOOST_VMD_TYPE_TYPE,BOOST_VMD_TYPE_NUMBER)
#define BOOST_VMD_SUBTYPE_REGISTER_BOOST_VMD_TYPE_SEQUENCE (BOOST_VMD_TYPE_TYPE,BOOST_VMD_TYPE_SEQUENCE)
#define BOOST_VMD_SUBTYPE_REGISTER_BOOST_VMD_TYPE_TYPE (BOOST_VMD_TYPE_TYPE,BOOST_VMD_TYPE_TYPE)

#endif /* BOOST_VMD_DETAIL_IS_TYPE_REGISTRATION_HPP */
