#ifndef __STAN__GM__PARSER__EXPRESSION_GRAMMAR_DEF__HPP__
#define __STAN__GM__PARSER__EXPRESSION_GRAMMAR_DEF__HPP__

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <istream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <stdexcept>

#include <boost/spirit/include/qi.hpp>
// FIXME: get rid of unused include
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

#include <boost/lexical_cast.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_numeric.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>
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

#include <stan/gm/ast.hpp>
#include <stan/gm/parser/whitespace_grammar.hpp>
#include <stan/gm/parser/expression_grammar.hpp>

BOOST_FUSION_ADAPT_STRUCT(stan::gm::index_op,
                          (stan::gm::expression, expr_)
                          (std::vector<std::vector<stan::gm::expression> >, 
                           dimss_) )

BOOST_FUSION_ADAPT_STRUCT(stan::gm::fun,
                          (std::string, name_)
                          (std::vector<stan::gm::expression>, args_) )

BOOST_FUSION_ADAPT_STRUCT(stan::gm::int_literal,
                          (int,val_)
                          (stan::gm::expr_type,type_))

BOOST_FUSION_ADAPT_STRUCT(stan::gm::double_literal,
                          (double,val_)
                          (stan::gm::expr_type,type_) )

namespace stan { 

  namespace gm {

    struct set_fun_type {
      template <typename T1>
      struct result { typedef fun type; };

      fun operator()(fun& fun) const {
        std::vector<expr_type> arg_types;
        for (size_t i = 0; i < fun.args_.size(); ++i)
          arg_types.push_back(fun.args_[i].expression_type());
        fun.type_ = function_signatures::instance().get_result_type(fun.name_,
                                                                    arg_types);
        return fun;
      }
    };
    boost::phoenix::function<set_fun_type> set_fun_type_f;


    struct addition_expr {
      template <typename T1, typename T2>
      struct result { typedef expression type; };

      expression operator()(expression& expr1,
                            const expression& expr2) const {
        if (expr1.expression_type().is_primitive()
            && expr2.expression_type().is_primitive()) {
          return expr1 += expr2;
        }
        std::vector<expression> args;
        args.push_back(expr1);
        args.push_back(expr2);
        set_fun_type sft;
        fun f("add",args);
        sft(f);
        return expression(f);
        return expr1 += expr2;
      }
    };
    boost::phoenix::function<addition_expr> addition;


    struct subtraction_expr {
      template <typename T1, typename T2>
      struct result { typedef expression type; };

      expression operator()(expression& expr1,
                            const expression& expr2) const {
        if (expr1.expression_type().is_primitive()
            && expr2.expression_type().is_primitive()) {
          return expr1 -= expr2;
        }
        std::vector<expression> args;
        args.push_back(expr1);
        args.push_back(expr2);
        set_fun_type sft;
        fun f("subtract",args);
        sft(f);
        return expression(f);
      }
    };
    boost::phoenix::function<subtraction_expr> subtraction;

    struct multiplication_expr {
      template <typename T1, typename T2>
      struct result { typedef expression type; };

      expression operator()(expression& expr1,
                            const expression& expr2) const {

        if (expr1.expression_type().is_primitive()
            && expr2.expression_type().is_primitive()) {
          return expr1 *= expr2;
        }
        std::vector<expression> args;
        args.push_back(expr1);
        args.push_back(expr2);
        set_fun_type sft;
        fun f("multiply",args);
        sft(f);
        return expression(f);
      }
    };
    boost::phoenix::function<multiplication_expr> multiplication;

    struct division_expr {
      template <typename T1, typename T2>
      struct result { typedef expression type; };

      expression operator()(expression& expr1,
                            const expression& expr2) const {
        if (expr1.expression_type().is_primitive()
            && expr2.expression_type().is_primitive()) {
          return expr1 /= expr2;
        }
        std::vector<expression> args;
        args.push_back(expr1);
        args.push_back(expr2);
        set_fun_type sft;
        fun f("divide",args);
        sft(f);
        return expression(f);
      }
    };
    boost::phoenix::function<division_expr> division;

    struct elt_multiplication_expr {
      template <typename T1, typename T2>
      struct result { typedef expression type; };

      expression operator()(expression& expr1,
                            const expression& expr2) const {

        if (expr1.expression_type().is_primitive()
            && expr2.expression_type().is_primitive()) {
          return expr1 *= expr2;
        }
        std::vector<expression> args;
        args.push_back(expr1);
        args.push_back(expr2);
        set_fun_type sft;
        fun f("elt_multiply",args);
        sft(f);
        return expression(f);
        return expr1 += expr2;
      }
    };
    boost::phoenix::function<elt_multiplication_expr> elt_multiplication;

    struct elt_division_expr {
      template <typename T1, typename T2>
      struct result { typedef expression type; };

      expression operator()(expression& expr1,
                            const expression& expr2) const {

        if (expr1.expression_type().is_primitive()
            && expr2.expression_type().is_primitive()) {
          return expr1 /= expr2;
        }
        std::vector<expression> args;
        args.push_back(expr1);
        args.push_back(expr2);
        set_fun_type sft;
        fun f("elt_divide",args);
        sft(f);
        return expression(f);
        return expr1 += expr2;
      }
    };
    boost::phoenix::function<elt_division_expr> elt_division;

    // Cut-and-Paste from Spirit examples, including comment:  We
    // should be using expression::operator-. There's a bug in phoenix
    // type deduction mechanism that prevents us from doing
    // so. Phoenix will be switching to BOOST_TYPEOF. In the meantime,
    // we will use a phoenix::function below:
    struct negate_expr {
      template <typename T>
      struct result { typedef expression type; };

      expression operator()(const expression& expr) const {
        if (expr.expression_type().is_primitive()) {
          return expression(unary_op('-', expr));
        }
        std::vector<expression> args;
        args.push_back(expr);
        set_fun_type sft;
        fun f("minus",args);
        sft(f);
        return expression(f);
      }
    };
    boost::phoenix::function<negate_expr> negate_expr_f;

    struct transpose_expr {
      template <typename T>
      struct result { typedef expression type; };

      expression operator()(const expression& expr) const {
        if (expr.expression_type().is_primitive()) {
          return expr; // transpose of basic is self?
        }
        std::vector<expression> args;
        args.push_back(expr);
        set_fun_type sft;
        fun f("transpose",args);
        sft(f);
        return expression(f);
      }
    };
    boost::phoenix::function<transpose_expr> transpose_f;

    struct set_indexed_factor_type {
      template <typename T1, typename T2>
      struct result { typedef bool type; };
      bool operator()(index_op& io,
                      std::ostream& error_msgs) const {
        io.infer_type();
        if (io.type_.is_ill_formed()) {
          error_msgs << "indexes inappropriate for expression." << std::endl;
          return false;
        }
        return true;
      }
    };
    boost::phoenix::function<set_indexed_factor_type> set_indexed_factor_type_f;

    struct set_var_type {
      template <typename T1, typename T2, typename T3, typename T4>
      struct result { typedef variable type; };
      variable operator()(variable& var_expr, 
                          variable_map& vm,
                          std::ostream& error_msgs,
                          bool& pass) const {
        std::string name = var_expr.name_;
        if (!vm.exists(name)) {
          pass = false;
          error_msgs << "variable \"" << name << '"' << " does not exist." 
                     << std::endl;
          return var_expr;
        }
        pass = true;
        var_expr.set_type(vm.get_base_type(name),vm.get_num_dims(name));
        return var_expr;
      }
    };
    boost::phoenix::function<set_var_type> set_var_type_f;

    struct validate_int_expr {
      template <typename T1, typename T2>
      struct result { typedef bool type; };

      bool operator()(const expression& expr,
                      std::stringstream& error_msgs) const {
        if (!expr.expression_type().is_primitive_int()) {
          error_msgs << "expression denoting integer required; found type=" 
                     << expr.expression_type() << std::endl;
          return false;
        }
        return true;
      }
    };
    boost::phoenix::function<validate_int_expr> validate_int_expr_f;


    struct validate_expr_type {
      template <typename T1, typename T2>
      struct result { typedef bool type; };

      bool operator()(const expression& expr,
                      std::ostream& error_msgs) const {
        if (expr.expression_type().is_ill_formed()) {
          error_msgs << "expression is ill formed" << std::endl;
          return false;
        }
        return true;
      }
    };
    boost::phoenix::function<validate_expr_type> validate_expr_type_f;

    



    template <typename Iterator>
    expression_grammar<Iterator>::expression_grammar(variable_map& var_map,
                                                     std::stringstream& error_msgs)
      : expression_grammar::base_type(expression_r),
        var_map_(var_map),
        error_msgs_(error_msgs) 
    {
      using boost::spirit::qi::_1;
      using boost::spirit::qi::char_;
      using boost::spirit::qi::double_;
      using boost::spirit::qi::eps;
      using boost::spirit::qi::int_;
      using boost::spirit::qi::lexeme;
      using boost::spirit::qi::lit;
      using boost::spirit::qi::_pass;
      using boost::spirit::qi::_val;

      expression_r.name("expression");
      expression_r 
        %=  term_r                     [_val = _1]
        >> *( (lit('+') > term_r       [_val = addition(_val,_1)])
              |   (lit('-') > term_r   [_val = subtraction(_val,_1)])
              )
        > eps[_pass = validate_expr_type_f(_val,boost::phoenix::ref(error_msgs_))]
        ;

      term_r.name("term");
      term_r 
        %= ( negated_factor_r                       [_val = _1]
             >> *( (lit('*') > negated_factor_r     [_val = multiplication(_val,_1)])
                   | (lit('/') > negated_factor_r   [_val = division(_val,_1)])
                   | (lit(".*") > negated_factor_r   
                      [_val = elt_multiplication(_val,_1)])
                   | (lit("./") > negated_factor_r   
                      [_val = elt_division(_val,_1)])
                   )
             )
        ;

      negated_factor_r 
        %= lit('-') >> indexed_factor_r [_val = negate_expr_f(_1)]
        | lit('+') >> indexed_factor_r  [_val = _1]
        | indexed_factor_r [_val = _1];


      // two of these to put semantic action on this one w. index_op input
      indexed_factor_r.name("(optionally) indexed factor [sub]");
      indexed_factor_r 
        %=  transposed_factor_r
        [_val = transpose_f(_1)] 
        | (indexed_factor_2_r 
           [_pass = set_indexed_factor_type_f(_1,
                                              boost::phoenix::ref(error_msgs))])
        ;
        
      indexed_factor_2_r.name("(optionally) indexed factor [sub] 2");
      indexed_factor_2_r 
        %= (factor_r >> *dims_r);

      transposed_factor_r.name("matrix transpose");
      transposed_factor_r 
        %= (factor_r >> lit("'"));

      factor_r.name("factor");
      factor_r
        %=  int_literal_r      [_val = _1]
        | double_literal_r    [_val = _1]
        | fun_r               [_val = set_fun_type_f(_1)]
        | variable_r          
        [_val = set_var_type_f(_1,boost::phoenix::ref(var_map_),
                               boost::phoenix::ref(error_msgs_),
                               _pass)]
        | ( lit('(') 
            > expression_r    [_val = _1]
            > lit(')') )
        ;

      int_literal_r.name("integer literal");
      int_literal_r
        %= int_ 
        >> !( lit('.')
              | lit('e')
              | lit('E') );

      double_literal_r.name("real literal");
      double_literal_r
        %= double_;

      fun_r.name("function and argument expressions");
      fun_r 
        %= identifier_r 
        >> args_r; 

      identifier_r.name("identifier");
      identifier_r
        %= (lexeme[char_("a-zA-Z") 
                   >> *char_("a-zA-Z0-9_.")]);

      args_r.name("function argument expressions");
      args_r 
        %= lit('(') 
        >> (expression_r % ',')
        > lit(')');

      dims_r.name("array dimensions");
      dims_r 
        %= lit('[') 
        > (expression_r 
           [_pass = validate_int_expr_f(_1,boost::phoenix::ref(error_msgs_))]
           % ',')
        > lit(']')
        ;
 
      variable_r.name("variable expression");
      variable_r
        %= identifier_r;

    }
  }
}

#endif
