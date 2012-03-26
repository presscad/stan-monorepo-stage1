#ifndef __STAN__GM__PARSER__PROGRAM_GRAMMAR__HPP__
#define __STAN__GM__PARSER__PROGRAM_GRAMMAR__HPP__

#include <string>
#include <sstream>
#include <vector>

#include <boost/spirit/include/qi.hpp>

#include <stan/gm/ast.hpp>
#include <stan/gm/parser/whitespace_grammar.hpp>
#include <stan/gm/parser/expression_grammar.hpp>
#include <stan/gm/parser/var_decls_grammar.hpp>
#include <stan/gm/parser/statement_grammar.hpp>

namespace stan { 

  namespace gm {

    template <typename Iterator>
    struct program_grammar 
      : boost::spirit::qi::grammar<Iterator, 
                                   program(), 
                                   whitespace_grammar<Iterator> > {
      
      program_grammar();
      
      // global info for parses
      variable_map var_map_;
      std::stringstream error_msgs_;

      // grammars
      expression_grammar<Iterator> expression_g;
      var_decls_grammar<Iterator> var_decls_g;
      statement_grammar<Iterator> statement_g;

      // rules

      boost::spirit::qi::rule<Iterator, 
                              std::vector<var_decl>(), 
                              whitespace_grammar<Iterator> >       
      data_var_decls_r;

      boost::spirit::qi::rule<Iterator, 
                              std::pair<std::vector<var_decl>,
                                        std::vector<statement> >(), 
                              whitespace_grammar<Iterator> > 
      derived_data_var_decls_r;

      boost::spirit::qi::rule<Iterator, 
                              std::pair<std::vector<var_decl>,
                                        std::vector<statement> >(), 
                              whitespace_grammar<Iterator> > 
      derived_var_decls_r;

      boost::spirit::qi::rule<Iterator, 
                              std::pair<std::vector<var_decl>,
                                        std::vector<statement> >(), 
                              whitespace_grammar<Iterator> > 
      generated_var_decls_r;

      boost::spirit::qi::rule<Iterator, 
                              statement(), 
                              whitespace_grammar<Iterator> > 
      model_r;

      boost::spirit::qi::rule<Iterator, 
                              std::vector<var_decl>(), 
                              whitespace_grammar<Iterator> >
      param_var_decls_r;

      boost::spirit::qi::rule<Iterator, 
                              program(),
                              whitespace_grammar<Iterator> >
      program_r;
    
    };


  }
}

#endif
