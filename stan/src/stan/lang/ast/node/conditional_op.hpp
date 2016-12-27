#ifndef STAN_LANG_AST_NODE_CONDITIONAL_OP_HPP
#define STAN_LANG_AST_NODE_CONDITIONAL_OP_HPP

#include <stan/lang/ast/expr_type.hpp>
#include <stan/lang/ast/var_origin.hpp>
#include <stan/lang/ast/node/expression.hpp>

namespace stan {
  namespace lang {

    /**
     * Structure for the conditional operator
     */
    struct conditional_op {
      /**
       * Condition (integer).
       */
      expression cond_;

      /**
       * Return value if condition is true.
       */
      expression true_val_;

      /**
       * Return value if condition is false.
       */
      expression false_val_;

      /**
       * Type of result.
       */
      expr_type type_;

      /**
       * True if the conditional operator contains a variable that is
       * declared as a parameter, transformed parameter, or local
       * variable. 
       */
      bool has_var_;

      /**
       * Origin of this conditional operator expression.
       */
      var_origin var_origin_;

      /**
       * Construct a default conditional operator expression.
       */
      conditional_op();

      /**
       * Construct a conditional operator expression from the
       * specified condition and values.
       *
       * @param cond condition expression
       * @param true_val value to return if true
       * @param false_val value to return if false
       */
      conditional_op(const expression& cond,
                     const expression& true_val,
                     const expression& false_val);
    };

  }
}
#endif
