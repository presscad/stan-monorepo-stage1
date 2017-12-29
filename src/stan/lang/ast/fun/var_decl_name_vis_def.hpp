#ifndef STAN_LANG_AST_FUN_VAR_DECL_NAME_VIS_DEF_HPP
#define STAN_LANG_AST_FUN_VAR_DECL_NAME_VIS_DEF_HPP

#include <stan/lang/ast.hpp>
#include <string>

namespace stan {
  namespace lang {

    var_decl_name_vis::var_decl_name_vis() { }

    std::string var_decl_name_vis::operator()(const nil& /* x */) const {
      return "";
    }

    std::string var_decl_name_vis::operator()(const array_block_var_decl& x) const {
      return x.name_;
    }

    std::string var_decl_name_vis::operator()(const array_local_var_decl& x) const {
      return x.name_;
    }

    std::string var_decl_name_vis::operator()(const array_fun_var_decl& x) const {
      return x.name_;
    }

    std::string var_decl_name_vis::operator()(const int_block_var_decl& x) const {
      return x.name_;
    }

    std::string var_decl_name_vis::operator()(const int_local_var_decl& x) const {
      return x.name_;
    }

    std::string var_decl_name_vis::operator()(const int_fun_var_decl& x) const {
      return x.name_;
    }

    std::string var_decl_name_vis::operator()(const double_block_var_decl& x) const {
      return x.name_;
    }

    std::string var_decl_name_vis::operator()(const double_local_var_decl& x) const {
      return x.name_;
    }

    std::string var_decl_name_vis::operator()(const double_fun_var_decl& x) const {
      return x.name_;
    }

    std::string var_decl_name_vis::operator()(const vector_block_var_decl& x) const {
      return x.name_;
    }

    std::string var_decl_name_vis::operator()(const vector_local_var_decl& x) const {
      return x.name_;
    }

    std::string var_decl_name_vis::operator()(const vector_fun_var_decl& x) const {
      return x.name_;
    }
    
    std::string var_decl_name_vis::operator()(const row_vector_block_var_decl& x) const {
      return x.name_;
    }
    
    std::string var_decl_name_vis::operator()(const row_vector_local_var_decl& x) const {
      return x.name_;
    }
    
    std::string var_decl_name_vis::operator()(const row_vector_fun_var_decl& x) const {
      return x.name_;
    }

    std::string var_decl_name_vis::operator()(const matrix_block_var_decl& x) const {
      return x.name_;
    }

    std::string var_decl_name_vis::operator()(const matrix_local_var_decl& x) const {
      return x.name_;
    }

    std::string var_decl_name_vis::operator()(const matrix_fun_var_decl& x) const {
      return x.name_;
    }

    std::string var_decl_name_vis::operator()(const cholesky_factor_block_var_decl& x) const {
      return x.name_;
    }

    std::string var_decl_name_vis::operator()(const cholesky_corr_block_var_decl& x) const {
      return x.name_;
    }

    std::string var_decl_name_vis::operator()(const cov_matrix_block_var_decl& x) const {
      return x.name_;
    }

    std::string var_decl_name_vis::operator()(const corr_matrix_block_var_decl& x) const {
      return x.name_;
    }

    std::string var_decl_name_vis::operator()(const ordered_block_var_decl& x) const {
      return x.name_;
    }

    std::string var_decl_name_vis::operator()(const positive_ordered_block_var_decl& x) const {
      return x.name_;
    }

    std::string var_decl_name_vis::operator()(const simplex_block_var_decl& x) const {
      return x.name_;
    }

    std::string var_decl_name_vis::operator()(const unit_vector_block_var_decl& x) const {
      return x.name_;
    }
  }
}
#endif
