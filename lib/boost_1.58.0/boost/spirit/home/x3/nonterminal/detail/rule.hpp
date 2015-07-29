/*=============================================================================
    Copyright (c) 2001-2014 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_SPIRIT_X3_DETAIL_RULE_JAN_08_2012_0326PM)
#define BOOST_SPIRIT_X3_DETAIL_RULE_JAN_08_2012_0326PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/x3/core/parser.hpp>
#include <boost/spirit/home/x3/support/traits/make_attribute.hpp>
#include <boost/spirit/home/x3/support/utility/sfinae.hpp>
#include <boost/spirit/home/x3/nonterminal/detail/transform_attribute.hpp>
#include <boost/utility/addressof.hpp>

#if defined(BOOST_SPIRIT_X3_DEBUG)
#include <boost/spirit/home/x3/nonterminal/simple_trace.hpp>
#endif

namespace boost { namespace spirit { namespace x3
{
    template <typename ID>
    struct identity;
    
    template <typename ID, typename Attribute = unused_type>
    struct rule;

    struct parse_pass_context_tag;

    namespace detail
    {
        // we use this so we can detect if the default parse_rule
        // is the being called.
        struct default_parse_rule_result
        {
            default_parse_rule_result(bool r)
              : r(r) {}
            operator bool() const { return r; }
            bool r;
        };
    }
    
    // default parse_rule implementation
    template <typename ID, typename Attribute, typename Iterator
      , typename Context, typename ActualAttribute>
    inline detail::default_parse_rule_result
    parse_rule(
        rule<ID, Attribute> rule_
      , Iterator& first, Iterator const& last
      , Context const& context, ActualAttribute& attr);
}}}

namespace boost { namespace spirit { namespace x3 { namespace detail
{
#if defined(BOOST_SPIRIT_X3_DEBUG)
    template <typename Iterator, typename Attribute>
    struct context_debug
    {
        context_debug(
            char const* rule_name
          , Iterator const& first, Iterator const& last
          , Attribute const& attr
          , bool const& ok_parse //was parse successful?
          )
          : ok_parse(ok_parse), rule_name(rule_name)
          , first(first), last(last)
          , attr(attr)
          , f(detail::get_simple_trace())
        {
            f(first, last, attr, pre_parse, rule_name);
        }

        ~context_debug()
        {
            auto status = ok_parse ? successful_parse : failed_parse ;
            f(first, last, attr, status, rule_name);
        }

        bool const& ok_parse;
        char const* rule_name;
        Iterator const& first;
        Iterator const& last;
        Attribute const& attr;
        detail::simple_trace_type& f;
    };
#endif
    
    template <typename ID, typename Iterator, typename Context, typename Enable = void>
    struct has_on_error : mpl::false_ {};

    template <typename ID, typename Iterator, typename Context>
    struct has_on_error<ID, Iterator, Context,
        typename disable_if_substitution_failure<
            decltype(
                std::declval<ID>().on_error(
                    std::declval<Iterator&>()
                  , std::declval<Iterator>()
                  , std::declval<expectation_failure<Iterator>>()
                  , std::declval<Context>()
                )
            )>::type
        >
      : mpl::true_
    {};
    
    template <typename ID, typename Iterator, typename Attribute, typename Context, typename Enable = void>
    struct has_on_success : mpl::false_ {};

    template <typename ID, typename Iterator, typename Attribute, typename Context>
    struct has_on_success<ID, Iterator, Context, Attribute,
        typename disable_if_substitution_failure<
            decltype(
                std::declval<ID>().on_success(
                    std::declval<Iterator&>()
                  , std::declval<Iterator>()
                  , std::declval<Attribute&>()
                  , std::declval<Context>()
                )
            )>::type
        >
      : mpl::true_
    {};

    template <typename ID>
    struct make_id
    {
        typedef identity<ID> type;
    };

    template <typename ID>
    struct make_id<identity<ID>>
    {
        typedef identity<ID> type;
    };
    
    template <typename ID, typename RHS, typename Context>
    Context const&
    make_rule_context(RHS const& rhs, Context const& context
      , mpl::false_ /* is_default_parse_rule */)
    {
        return context;
    }
    
    template <typename ID, typename RHS, typename Context>
    auto make_rule_context(RHS const& rhs, Context const& context
      , mpl::true_ /* is_default_parse_rule */ )
    {
        return make_unique_context<ID>(rhs, context);
    }

    template <typename Attribute, typename ID>
    struct rule_parser
    {
        template <typename Iterator, typename Context, typename ActualAttribute>
        static bool call_on_success(
            Iterator& first, Iterator const& last
          , Context const& context, ActualAttribute& attr
          , mpl::false_ /* No on_success handler */ )
        {
            return true;
        }
        
        template <typename Iterator, typename Context, typename ActualAttribute>
        static bool call_on_success(
            Iterator& first, Iterator const& last
          , Context const& context, ActualAttribute& attr
          , mpl::true_ /* Has on_success handler */)
        {
            bool pass = true;
            ID().on_success(
                first
              , last
              , attr
              , make_context<parse_pass_context_tag>(pass, context)
            );
            return pass;
        }
        
        template <typename RHS, typename Iterator, typename Context
          , typename RContext, typename ActualAttribute>
        static bool parse_rhs_main(
            RHS const& rhs
          , Iterator& first, Iterator const& last
          , Context const& context, RContext& rcontext, ActualAttribute& attr
          , mpl::false_)
        {
            // see if the user has a BOOST_SPIRIT_DEFINE for this rule
            typedef
                decltype(parse_rule(
                    rule<ID, Attribute>(), first, last
                  , make_unique_context<ID>(rhs, context), attr))
            parse_rule_result;

            // If there is no BOOST_SPIRIT_DEFINE for this rule,
            // we'll make a context for this rule tagged by its ID
            // so we can extract the rule later on in the default
            // (generic) parse_rule function.
            typedef
                is_same<parse_rule_result, default_parse_rule_result>
            is_default_parse_rule;

            Iterator i = first;
            bool r = rhs.parse(
                i
              , last
              , make_rule_context<ID>(rhs, context, is_default_parse_rule())
              , rcontext
              , attr
            );

            if (r)
            {
                auto first_ = first;
                x3::skip_over(first_, last, context);
                r = call_on_success(first_, i, context, attr
                  , has_on_success<ID, Iterator, Context, ActualAttribute>());
            }
            
            if (r)
                first = i;
            return r;
        }

        template <typename RHS, typename Iterator, typename Context
          , typename RContext, typename ActualAttribute>
        static bool parse_rhs_main(
            RHS const& rhs
          , Iterator& first, Iterator const& last
          , Context const& context, RContext& rcontext, ActualAttribute& attr
          , mpl::true_ /* on_error is found */)
        {
            for (;;)
            {
                try
                {
                    return parse_rhs_main(
                        rhs, first, last, context, rcontext, attr, mpl::false_());
                }
                catch (expectation_failure<Iterator> const& x)
                {
                    switch (ID().on_error(first, last, x, context))
                    {
                        case error_handler_result::fail:
                            return false;
                        case error_handler_result::retry:
                            continue;
                        case error_handler_result::accept:
                            return true;
                        case error_handler_result::rethrow:
                            throw;
                    }
                }
            }
        }

        template <typename RHS, typename Iterator
          , typename Context, typename RContext, typename ActualAttribute>
        static bool parse_rhs_main(
            RHS const& rhs
          , Iterator& first, Iterator const& last
          , Context const& context, RContext& rcontext, ActualAttribute& attr)
        {
            return parse_rhs_main(
                rhs, first, last, context, rcontext, attr
              , has_on_error<ID, Iterator, Context>()
            );
        }

        template <typename RHS, typename Iterator
          , typename Context, typename RContext, typename ActualAttribute>
        static bool parse_rhs(
            RHS const& rhs
          , Iterator& first, Iterator const& last
          , Context const& context, RContext& rcontext, ActualAttribute& attr
          , mpl::false_)
        {
            return parse_rhs_main(rhs, first, last, context, rcontext, attr);
        }

        template <typename RHS, typename Iterator
          , typename Context, typename RContext, typename ActualAttribute>
        static bool parse_rhs(
            RHS const& rhs
          , Iterator& first, Iterator const& last
          , Context const& context, RContext& rcontext, ActualAttribute& attr
          , mpl::true_)
        {
            return parse_rhs_main(rhs, first, last, context, rcontext, unused);
        }

        template <typename RHS, typename Iterator, typename Context
          , typename ActualAttribute, typename ExplicitAttrPropagation>
        static bool call_rule_definition(
            RHS const& rhs
          , char const* rule_name
          , Iterator& first, Iterator const& last
          , Context const& context, ActualAttribute& attr
          , ExplicitAttrPropagation)
        {
            typedef traits::make_attribute<Attribute, ActualAttribute> make_attribute;

            // do down-stream transformation, provides attribute for
            // rhs parser
            typedef traits::transform_attribute<
                typename make_attribute::type, Attribute, parser_id>
            transform;

            typedef typename make_attribute::value_type value_type;
            typedef typename transform::type transform_attr;
            value_type made_attr = make_attribute::call(attr);
            transform_attr attr_ = transform::pre(made_attr);

            bool ok_parse
              //Creates a place to hold the result of parse_rhs
              //called inside the following scope.
              ;
            {
             //Create a scope to cause the dbg variable below (within
             //the #if...#endif) to call it's DTOR before any
             //modifications are made to the attribute, attr_ passed
             //to parse_rhs (such as might be done in
             //traits::post_transform when, for example,
             //ActualAttribute is a recursive variant).
#if defined(BOOST_SPIRIT_X3_DEBUG)
                  context_debug<Iterator, typename make_attribute::value_type>
                dbg(rule_name, first, last, attr_, ok_parse);
#endif
                ok_parse=parse_rhs(rhs, first, last, context, attr_, attr_
                   , mpl::bool_
                     < (  RHS::has_action 
                       && !ExplicitAttrPropagation::value
                       )
                     >()
                  );
            }
            if(ok_parse)
            {
                // do up-stream transformation, this integrates the results
                // back into the original attribute value, if appropriate
                traits::post_transform(attr, attr_);
            }
            return ok_parse;
        }

//        template <typename RuleDef, typename Iterator, typename Context
//            , typename ActualAttribute, typename AttributeContext>
//        static bool call_from_rule(
//            RuleDef const& rule_def
//          , char const* rule_name
//          , Iterator& first, Iterator const& last
//          , Context const& context, ActualAttribute& attr, AttributeContext& attr_ctx)
//        {
//            // This is called when a rule-body has already been established.
//            // The rule body is already established by the rule_definition class,
//            // we will not do it again. We'll simply call the RHS by calling
//            // call_rule_definition.
//
//            return call_rule_definition(
//                rule_def.rhs, rule_name, first, last
//              , context, attr, attr_ctx.attr_ptr
//              , mpl::bool_<(RuleDef::explicit_attribute_propagation)>());
//        }
//
//        template <typename RuleDef, typename Iterator, typename Context
//            , typename ActualAttribute>
//        static bool call_from_rule(
//            RuleDef const& rule_def
//          , char const* rule_name
//          , Iterator& first, Iterator const& last
//          , Context const& context, ActualAttribute& attr, unused_type)
//        {
//            // This is called when a rule-body has *not yet* been established.
//            // The rule body is established by the rule_definition class, so
//            // we call it to parse and establish the rule-body.
//
//            return rule_def.parse(first, last, context, unused, attr); // $$$ fix unused param $$$
//        }
    };
}}}}

#endif
