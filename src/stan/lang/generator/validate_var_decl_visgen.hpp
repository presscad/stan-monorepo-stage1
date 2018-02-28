#ifndef STAN_LANG_GENERATOR_VALIDATE_VAR_DECL_VISGEN_HPP
#define STAN_LANG_GENERATOR_VALIDATE_VAR_DECL_VISGEN_HPP

#include <stan/lang/ast.hpp>
#include <stan/lang/generator/constants.hpp>
#include <stan/lang/generator/generate_indent.hpp>
#include <stan/lang/generator/visgen.hpp>
#include <ostream>
#include <string>
#include <vector>

namespace stan {
  namespace lang {

    struct validate_var_decl_visgen : public visgen {
      /**
       * Construct a variable declaration validating visitor with the
       * specified indentation level writing to the specified stream.
       *
       * @param[in] indent indentation level
       * @param[in,out] o stream for generating
       */
      validate_var_decl_visgen(int indent, std::ostream& o)
        : visgen(indent, o) {  }

      /**
       * Validate the specified basic type declaration.
       *
       * @tparam T declaration type
       * @param[in] x declaration
       */
      template <typename T>
      void basic_validate(const T& x) const {
        if (!(x.range_.has_low() || x.range_.has_high())) {
          return;  // unconstrained
        }
        generate_begin_for_dims(x.dims_);
        if (x.range_.has_low()) {
          generate_indent(indent_ + x.dims_.size(), o_);
          o_ << "check_greater_or_equal(function__,";
          o_ << "\"";
          generate_loop_var(x.name_, x.dims_.size());
          o_ << "\",";
          generate_loop_var(x.name_, x.dims_.size());
          o_ << ",";
          generate_expression(x.range_.low_.expr_, NOT_USER_FACING, o_);
          o_ << ");" << EOL;
        }
        if (x.range_.has_high()) {
          generate_indent(indent_ + x.dims_.size(), o_);
          o_ << "check_less_or_equal(function__,";
          o_ << "\"";
          generate_loop_var(x.name_, x.dims_.size());
          o_ << "\",";
          generate_loop_var(x.name_, x.dims_.size());
          o_ << ",";
          generate_expression(x.range_.high_.expr_, NOT_USER_FACING, o_);
          o_ << ");" << EOL;
        }
        generate_end_for_dims(x.dims_.size());
      }

      /**
       * Validate the specified structured type declaration.
       *
       * @tparam T declaration type
       * @param[in] x declaration
       * @param[in] type_name name of type to check
       */
      template <typename T>
      void nonbasic_validate(const T& x,
                             const std::string& type_name) const {
        generate_begin_for_dims(x.dims_);
        generate_indent(indent_ + x.dims_.size(), o_);
        o_ << "stan::math::check_" << type_name << "(function__,";
        o_ << "\"";
        generate_loop_var(x.name_, x.dims_.size());
        o_ << "\",";
        generate_loop_var(x.name_, x.dims_.size());
        o_ << ");"
           << EOL;
        generate_end_for_dims(x.dims_.size());
      }

      void operator()(const nil& /*x*/) const { }

      void operator()(const int_var_decl& x) const {
        basic_validate(x);
      }

      void operator()(const double_var_decl& x) const {
        basic_validate(x);
      }

      void operator()(const vector_var_decl& x) const {
        basic_validate(x);
      }

      void operator()(const row_vector_var_decl& x) const {
        basic_validate(x);
      }

      void operator()(const matrix_var_decl& x) const {
        basic_validate(x);
      }

      void operator()(const unit_vector_var_decl& x) const {
        nonbasic_validate(x, "unit_vector");
      }

      void operator()(const simplex_var_decl& x) const {
        nonbasic_validate(x, "simplex");
      }

      void operator()(const ordered_var_decl& x) const {
        nonbasic_validate(x, "ordered");
      }

      void operator()(const positive_ordered_var_decl& x) const {
        nonbasic_validate(x, "positive_ordered");
      }

      void operator()(const cholesky_factor_var_decl& x) const {
        nonbasic_validate(x, "cholesky_factor");
      }

      void operator()(const cholesky_corr_var_decl& x) const {
        nonbasic_validate(x, "cholesky_factor_corr");
      }

      void operator()(const cov_matrix_var_decl& x) const {
        nonbasic_validate(x, "cov_matrix");
      }

      void operator()(const corr_matrix_var_decl& x) const {
        nonbasic_validate(x, "corr_matrix");
      }
    };


  }
}
#endif
