#ifndef STAN_LANG_AST_NODE_FOR_ARRAY_STATEMENT_DEF_HPP
#define STAN_LANG_AST_NODE_FOR_ARRAY_STATEMENT_DEF_HPP

#include <stan/lang/ast.hpp>
#include <string>

namespace stan {
  namespace lang {

    for_array_statement::for_array_statement() { }

    for_array_statement::for_array_statement(const std::string& variable,
                                             const expression& expression, //FOREACHCHANGE:  really, this should be an array_expr. where do we do the type checking?
                                             const statement& stmt)
      : variable_(variable), expression_(expression), statement_(stmt) { } //FOREACHCHANGE:  really, this should be an array_expr. where do we do the type checking?

  }
}
#endif
