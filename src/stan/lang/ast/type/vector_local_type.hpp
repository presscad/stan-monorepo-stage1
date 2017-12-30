#ifndef STAN_LANG_AST_VECTOR_LOCAL_TYPE_HPP
#define STAN_LANG_AST_VECTOR_LOCAL_TYPE_HPP

#include <stan/lang/ast/node/expression.hpp>

namespace stan {
  namespace lang {

    /**
     * Vector local var type.
     */
    struct vector_local_type {
      /**
       * Vector length
       */
      expression N_;

      /**
       * Construct a local var type with default values.
       */
      vector_local_type();

      /**
       * Construct a local var type with specified values.
       * Length should be int expression - constructor doesn't check.
       *
       * @param N vector length
       */
      vector_local_type(const expression& N);
    };

  }
}
#endif
