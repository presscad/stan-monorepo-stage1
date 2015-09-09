#ifndef STAN_LANG_GRAMMARS_INDEXES_GRAMMAR_DEF_HPP
#define STAN_LANG_GRAMMARS_INDEXES_GRAMMAR_DEF_HPP

#include <boost/spirit/include/qi.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi_numeric.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/recursive_variant.hpp>

#include <boost/spirit/include/version.hpp>
#include <boost/spirit/include/support_line_pos_iterator.hpp>

#include <stan/lang/ast.hpp>
#include <stan/lang/grammars/bare_type_grammar.hpp>
#include <stan/lang/grammars/indexes_grammar.hpp>
#include <stan/lang/grammars/whitespace_grammar.hpp>

BOOST_FUSION_ADAPT_STRUCT(stan::lang::uni_idx,
                          (stan::lang::expression, idx_) )
BOOST_FUSION_ADAPT_STRUCT(stan::lang::multi_idx,
                          (stan::lang::expression, idxs_) )
BOOST_FUSION_ADAPT_STRUCT(stan::lang::lb_idx,
                          (stan::lang::expression, lb_) )
BOOST_FUSION_ADAPT_STRUCT(stan::lang::ub_idx,
                          (stan::lang::expression, ub_) )
BOOST_FUSION_ADAPT_STRUCT(stan::lang::lub_idx,
                          (stan::lang::expression, lb_)
                          (stan::lang::expression, ub_) )

namespace stan {
  namespace lang {

    struct set_omni_idx {
      template <class> struct result;
      template <typename F, typename T1>
      struct result<F(T1)> { typedef void type; };
      template <typename T1>
      void operator()(T1& val) const {
        val = omni_idx();
      }
    };
    boost::phoenix::function<set_omni_idx> set_omni_idx_f;


    template <typename Iterator>
    indexes_grammar<Iterator>::indexes_grammar(variable_map& var_map,
                                               std::stringstream& error_msgs,
                                               expression_grammar<Iterator>& eg)
      : indexes_grammar::base_type(indexes_r),
        var_map_(var_map),
        error_msgs_(error_msgs),
        expression_g(eg) {
      using boost::spirit::qi::eps;
      using boost::spirit::qi::lit;
      using boost::spirit::qi::_val;
      using boost::spirit::qi::_r1;
      using boost::spirit::qi::_1;

      indexes_r.name("indexes (zero or more)");
      indexes_r
        %= -(lit("[")
             > (index_r(_r1) % ',')
             > lit("]"));
      
      index_r.name("index expression denoting (int, int[], int:, :int, int:int, :)");
      index_r
        %= uni_index_r(_r1)
        | multi_index_r(_r1)
        | omni_index_r(_r1)
        | lb_index_r(_r1)
        | ub_index_r(_r1)
        | lub_index_r(_r1);

      lub_index_r
        %= int_expression_r(_r1) 
        >> lit(":") 
        >> int_expression_r(_r1)
        > eps;
      
      lb_index_r
        %= int_expression_r(_r1) 
        >> lit(":")
        > eps;

      uni_index_r 
        %= int_expression_r(_r1);

      multi_index_r
        %= expression_g(_r1);  // validate int[]
      
      ub_index_r
        %= lit(":") 
        >> int_expression_r(_r1)
        > eps;

      omni_index_r
        = -lit(":")[set_omni_idx_f(_val)];
      
      int_expression_r
        %= expression_g(_r1);  // validate int
      
    }

  }
}
#endif
