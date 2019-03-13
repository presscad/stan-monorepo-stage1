//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#include <boost/container/pmr/resource_adaptor.hpp>
#include <boost/core/lightweight_test.hpp>
#include "propagation_test_allocator.hpp"
#include "derived_from_memory_resource.hpp"

using namespace boost::container::pmr;

void test_default_constructor()
{
   typedef propagation_test_allocator<char, 0> alloc_t;
   resource_adaptor<alloc_t> ra;
   BOOST_TEST(ra.get_allocator().m_default_contructed == true);
}

void test_copy_constructor()
{
   typedef propagation_test_allocator<char, 0> alloc_t;
   resource_adaptor<alloc_t> ra;
   BOOST_TEST(ra.get_allocator().m_default_contructed == true);
   resource_adaptor<alloc_t> rb(ra);
   BOOST_TEST(rb.get_allocator().m_default_contructed == false);
   BOOST_TEST(rb.get_allocator().m_move_contructed == false);
}

void test_move_constructor()
{
   typedef propagation_test_allocator<char, 0> alloc_t;
   resource_adaptor<alloc_t> ra;
   BOOST_TEST(ra.get_allocator().m_default_contructed == true);
   resource_adaptor<alloc_t> rb(::boost::move(ra));
   BOOST_TEST(rb.get_allocator().m_default_contructed == false);
   BOOST_TEST(rb.get_allocator().m_move_contructed == true);
}

void test_lvalue_alloc_constructor()
{
   typedef propagation_test_allocator<char, 0> alloc_t;
   alloc_t a;
   resource_adaptor<alloc_t> ra(a);
   BOOST_TEST(ra.get_allocator().m_default_contructed == false);
   BOOST_TEST(ra.get_allocator().m_move_contructed == false);
}

void test_rvalue_alloc_constructor()
{
   typedef propagation_test_allocator<char, 0> alloc_t;
   alloc_t a;
   resource_adaptor<alloc_t> ra(::boost::move(a));
   BOOST_TEST(ra.get_allocator().m_default_contructed == false);
   BOOST_TEST(ra.get_allocator().m_move_contructed == true);
}

void test_copy_assign()
{
   typedef propagation_test_allocator<char, 0> alloc_t;
   resource_adaptor<alloc_t> ra;
   BOOST_TEST(ra.get_allocator().m_default_contructed == true);
   resource_adaptor<alloc_t> rb;
   BOOST_TEST(ra.get_allocator().m_default_contructed == true);
   rb = ra;
   BOOST_TEST(rb.get_allocator().m_move_contructed == false);
   BOOST_TEST(rb.get_allocator().m_move_assigned == false);
}

void test_move_assign()
{
   typedef propagation_test_allocator<char, 0> alloc_t;
   resource_adaptor<alloc_t> ra;
   BOOST_TEST(ra.get_allocator().m_default_contructed == true);
   resource_adaptor<alloc_t> rb;
   BOOST_TEST(ra.get_allocator().m_default_contructed == true);
   rb = ::boost::move(ra);
   BOOST_TEST(rb.get_allocator().m_move_contructed == false);
   BOOST_TEST(rb.get_allocator().m_move_assigned == true);
}

struct stateful
{
   public:
   typedef char value_type;

   template<class U>
   struct rebind
   {  typedef stateful other; };

   stateful()
      : m_u(0u)
   {}

   char *allocate(std::size_t n)
   {  allocate_size = n;   return allocate_return;  }

   void deallocate(char *p, std::size_t n)
   {  deallocate_p = p;    deallocate_size = n; }

   friend bool operator==(const stateful &l, const stateful &r)
   {  return l.m_u == r.m_u;   }

   friend bool operator!=(const stateful &l, const stateful &r)
   {  return l.m_u != r.m_u;   }

   public:
   unsigned m_u;
   std::size_t allocate_size;
   char *allocate_return;
   std::size_t deallocate_size;
   char *deallocate_p;
};

void test_get_allocator()
{
   stateful a;
   a.m_u = 999;
   resource_adaptor<stateful> ra(a);
   const resource_adaptor<stateful> & cra = ra;
   BOOST_TEST( ra.get_allocator().m_u == 999);
   BOOST_TEST(cra.get_allocator().m_u == 999);
}

typedef resource_adaptor<stateful> stateful_resource_adaptor_t;

struct derived_from_resource_adaptor_stateful
   : public stateful_resource_adaptor_t
{
   public:
   typedef stateful_resource_adaptor_t base_t;
   using base_t::do_allocate;
   using base_t::do_deallocate;
   using base_t::do_is_equal;
};

void test_do_allocate()
{
   derived_from_resource_adaptor_stateful dra;
   char dummy = 0;
   dra.get_allocator().allocate_return = &dummy;
   void *allocate_ret = dra.do_allocate(998, 1234);
   BOOST_TEST(allocate_ret == &dummy);
   BOOST_TEST(dra.get_allocator().allocate_size == 998);
}

void test_do_deallocate()
{
   derived_from_resource_adaptor_stateful dra;
   char dummy = 0;
   dra.do_deallocate(&dummy, 1234, 753);
   BOOST_TEST(dra.get_allocator().deallocate_p == &dummy);
   BOOST_TEST(dra.get_allocator().deallocate_size == 1234);
}

void test_do_is_equal()
{
   derived_from_resource_adaptor_stateful dra;
   derived_from_memory_resource dmr;
   //Different dynamic type must return false
   BOOST_TEST(dra.do_is_equal(dmr) == false);

   //Same dynamic type with same state must return true
   derived_from_resource_adaptor_stateful dra2;
   BOOST_TEST(dra.do_is_equal(dra2) == true);

   //Same dynamic type with different state must return false
   dra2.get_allocator().m_u = 1234;
   BOOST_TEST(dra.do_is_equal(dra2) == false);
}

int main()
{
   test_default_constructor();
   test_copy_constructor();
   test_move_constructor();
   test_lvalue_alloc_constructor();
   test_rvalue_alloc_constructor();
   test_copy_assign();
   test_move_assign();
   test_get_allocator();
   test_do_allocate();
   test_do_deallocate();
   test_do_is_equal();
   return ::boost::report_errors();
}
