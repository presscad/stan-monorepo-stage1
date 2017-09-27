#ifndef STAN_LANG_GENERATOR_GENERATE_STATEMENTS_HPP
#define STAN_LANG_GENERATOR_GENERATE_STATEMENTS_HPP

#include <stan/lang/ast.hpp>
#include <stan/lang/generator/generate_statement.hpp>
#include <ostream>
#include <vector>

namespace stan {
  namespace lang {

    /**
     * Generate the set of statements in a program block with
     * the specified indentation level on the specified stream
     * with flags indicating whether sampling statements are allowed.
     *
     * @param[in] statements vector of statements
     * @param[in] indent indentation level
     * @param[in,out] o stream for generating
     * @param[in] include_sampling true if sampling statements are
     * included
     */
    void generate_statements(const std::vector<statement> statements,
                             int indent, std::ostream& o,
                             bool include_sampling) {
      for (size_t i = 0; i < statements.size(); ++i)
        generate_statement(statements[i], indent, o, include_sampling);
    }

  }
}
#endif

