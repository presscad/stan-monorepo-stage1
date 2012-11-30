#ifndef __STAN__GM__PARSER__EXPRESSION_GRAMMAR__HPP__
#define __STAN__GM__PARSER__EXPRESSION_GRAMMAR__HPP__

#include <string>
#include <sstream>
#include <vector>

#include <boost/spirit/include/qi.hpp>

#include <stan/gm/ast.hpp>
#include <stan/gm/grammars/whitespace_grammar.hpp>

namespace stan { 

  namespace gm {

    template <typename Iterator>
    struct expression_grammar 
      : public boost::spirit::qi::grammar<Iterator,
                                          expression(),
                                          whitespace_grammar<Iterator> > {

      expression_grammar(variable_map& var_map,
                         std::stringstream& error_msgs,
                         bool allow_lte = true);

      variable_map& var_map_;

      std::stringstream& error_msgs_;

      boost::spirit::qi::rule<Iterator, 
                              std::vector<expression>(), 
                              whitespace_grammar<Iterator> > 
      args_r;

      boost::spirit::qi::rule<Iterator, 
                              std::vector<expression>(), 
               whitespace_grammar<Iterator> > 
      dims_r;

      boost::spirit::qi::rule<Iterator, 
                              double_literal(),
                              whitespace_grammar<Iterator> > 
      double_literal_r;

      boost::spirit::qi::rule<Iterator, 
                              array_literal(),
                              whitespace_grammar<Iterator> > 
      array_literal_r;


      boost::spirit::qi::rule<Iterator, 
                              expression(), 
                              whitespace_grammar<Iterator> > 
      expression_r;

      boost::spirit::qi::rule<Iterator, 
                              expression(), 
                              whitespace_grammar<Iterator> > 
      expression07_r;

      boost::spirit::qi::rule<Iterator, 
                              expression(), 
                              whitespace_grammar<Iterator> > 
      expression09_r;

      boost::spirit::qi::rule<Iterator, 
                              expression(), 
                              whitespace_grammar<Iterator> > 
      expression10_r;

      boost::spirit::qi::rule<Iterator, 
                              expression(), 
                              whitespace_grammar<Iterator> > 
      expression14_r;

      boost::spirit::qi::rule<Iterator, 
                              expression(), 
                              whitespace_grammar<Iterator> > 
       expression15_r;

      boost::spirit::qi::rule<Iterator, 
                              boost::spirit::qi::locals<bool>, 
                              expression(), 
                              whitespace_grammar<Iterator> > 
      factor_r;

      boost::spirit::qi::rule<Iterator, 
                              fun(), 
                              whitespace_grammar<Iterator> > 
      fun_r;

      boost::spirit::qi::rule<Iterator, 
                              std::string(), 
                              whitespace_grammar<Iterator> > 
      identifier_r;

      boost::spirit::qi::rule<Iterator, 
                              expression(), 
                              whitespace_grammar<Iterator> > 
      indexed_factor_r;

      boost::spirit::qi::rule<Iterator,
                              int_literal(), 
                              whitespace_grammar<Iterator> > 
      int_literal_r;

      boost::spirit::qi::rule<Iterator,
                              expression(), 
                              whitespace_grammar<Iterator> > 
      negated_factor_r;

      boost::spirit::qi::rule<Iterator, 
                              expression(), 
                              whitespace_grammar<Iterator> > 
      term_r;

      boost::spirit::qi::rule<Iterator, 
                              variable(), 
                              whitespace_grammar<Iterator> > 
      variable_r;


    };

  }
}

#endif
