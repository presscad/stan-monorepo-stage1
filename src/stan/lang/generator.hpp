#ifndef STAN_LANG_GENERATOR_HPP
#define STAN_LANG_GENERATOR_HPP

// TODO(carpenter): move into general utilities (morris: what gen utils?)
#include <stan/lang/generator/to_string.hpp>

// utilities
#include <stan/lang/generator/constants.hpp>
#include <stan/lang/generator/fun_scalar_type.hpp>

#include <stan/lang/generator/generate_block_var.hpp>
#include <stan/lang/generator/generate_validate_block_var.hpp>
#include <stan/lang/generator/generate_write_block_var.hpp>
#include <stan/lang/generator/generate_data_var_init.hpp>
#include <stan/lang/generator/generate_param_names_array.hpp>
#include <stan/lang/generator/generate_var_constructor.hpp>
#include <stan/lang/generator/generate_var_fill_define.hpp>
#include <stan/lang/generator/generate_validate_tparam_inits.hpp>
#include <stan/lang/generator/generate_validate_var_decl.hpp>
#include <stan/lang/generator/generate_validate_var_dims.hpp>
#include <stan/lang/generator/generate_param_names_array.hpp>


#include <stan/lang/generator/get_typedef_var_type.hpp>
#include <stan/lang/generator/get_verbose_var_type.hpp>
#include <stan/lang/generator/get_block_var_dims.hpp>

#include <stan/lang/generator/write_begin_all_dims_col_maj_loop.hpp>
#include <stan/lang/generator/write_begin_all_dims_row_maj_loop.hpp>
#include <stan/lang/generator/write_begin_array_dims_loop.hpp>
#include <stan/lang/generator/write_constraints_fn.hpp>
#include <stan/lang/generator/write_end_loop.hpp>
#include <stan/lang/generator/write_nested_resize_loop_begin.hpp>
#include <stan/lang/generator/write_resize_var_idx.hpp>
#include <stan/lang/generator/write_var_idx_all_dims.hpp>
#include <stan/lang/generator/write_var_idx_all_dims_msg.hpp>
#include <stan/lang/generator/write_var_idx_array_dims.hpp>

#include <stan/lang/generator/write_var_decl_arg.hpp>
#include <stan/lang/generator/write_var_decl_type.hpp>

// visitor classes for tests
#include <stan/lang/generator/is_numbered_statement_vis.hpp>

// visitor classes for generation

#include <stan/lang/generator/expression_visgen.hpp>
#include <stan/lang/generator/printable_visgen.hpp>
#include <stan/lang/generator/idx_visgen.hpp>
#include <stan/lang/generator/idx_user_visgen.hpp>

#include <stan/lang/generator/statement_visgen.hpp>
#include <stan/lang/generator/visgen.hpp>

// generation functions, starts from generate_cpp
#include <stan/lang/generator/generate_arg_decl.hpp>
#include <stan/lang/generator/generate_array_builder_adds.hpp>
#include <stan/lang/generator/generate_bare_type.hpp>
#include <stan/lang/generator/generate_catch_throw_located.hpp>
#include <stan/lang/generator/generate_class_decl.hpp>
#include <stan/lang/generator/generate_class_decl_end.hpp>
#include <stan/lang/generator/generate_comment.hpp>
#include <stan/lang/generator/generate_constrained_param_names_method.hpp>
#include <stan/lang/generator/generate_constructor.hpp>
#include <stan/lang/generator/generate_cpp.hpp>
#include <stan/lang/generator/generate_destructor.hpp>
#include <stan/lang/generator/generate_dims_method.hpp>
#include <stan/lang/generator/generate_eigen_index_expression.hpp>
#include <stan/lang/generator/generate_expression.hpp>
#include <stan/lang/generator/generate_function.hpp>
#include <stan/lang/generator/generate_functions.hpp>
#include <stan/lang/generator/generate_function_arguments.hpp>
#include <stan/lang/generator/generate_function_body.hpp>
#include <stan/lang/generator/generate_function_functor.hpp>
#include <stan/lang/generator/generate_function_inline_return_type.hpp>
#include <stan/lang/generator/generate_function_template_parameters.hpp>
#include <stan/lang/generator/generate_functor_arguments.hpp>
#include <stan/lang/generator/generate_globals.hpp>
#include <stan/lang/generator/generate_idx.hpp>
#include <stan/lang/generator/generate_idxs.hpp>
#include <stan/lang/generator/generate_idxs_user.hpp>
#include <stan/lang/generator/generate_indent.hpp>
#include <stan/lang/generator/generate_include.hpp>
#include <stan/lang/generator/generate_includes.hpp>
#include <stan/lang/generator/generate_indexed_expr.hpp>
#include <stan/lang/generator/generate_indexed_expr_user.hpp>
#include <stan/lang/generator/generate_initializer.hpp>
#include <stan/lang/generator/generate_line_number.hpp>
#include <stan/lang/generator/generate_local_var_decl_inits.hpp>
#include <stan/lang/generator/generate_log_prob.hpp>
#include <stan/lang/generator/generate_member_var_decls.hpp>
#include <stan/lang/generator/generate_member_var_decls_all.hpp>
#include <stan/lang/generator/generate_model_name_method.hpp>
#include <stan/lang/generator/generate_model_typedef.hpp>
#include <stan/lang/generator/generate_namespace_end.hpp>
#include <stan/lang/generator/generate_namespace_start.hpp>
#include <stan/lang/generator/generate_param_names_method.hpp>
#include <stan/lang/generator/generate_printable.hpp>
#include <stan/lang/generator/generate_private_decl.hpp>
#include <stan/lang/generator/generate_program_reader_fun.hpp>
#include <stan/lang/generator/generate_propto_default_function.hpp>
#include <stan/lang/generator/generate_propto_default_function_body.hpp>
#include <stan/lang/generator/generate_public_decl.hpp>
#include <stan/lang/generator/generate_quoted_expression.hpp>
#include <stan/lang/generator/generate_quoted_string.hpp>
#include <stan/lang/generator/generate_real_var_type.hpp>
#include <stan/lang/generator/generate_read_transform_params.hpp>
#include <stan/lang/generator/generate_set_param_ranges.hpp>
#include <stan/lang/generator/generate_statement.hpp>
#include <stan/lang/generator/generate_statements.hpp>
#include <stan/lang/generator/generate_transform_inits_method.hpp>
#include <stan/lang/generator/generate_typedef.hpp>
#include <stan/lang/generator/generate_typedefs.hpp>
#include <stan/lang/generator/generate_try.hpp>
#include <stan/lang/generator/generate_unconstrained_param_names_method.hpp>
#include <stan/lang/generator/generate_using.hpp>
#include <stan/lang/generator/generate_using_namespace.hpp>
#include <stan/lang/generator/generate_usings.hpp>
#include <stan/lang/generator/generate_validate_context_size.hpp>
#include <stan/lang/generator/generate_validate_positive.hpp>
#include <stan/lang/generator/generate_version_comment.hpp>
#include <stan/lang/generator/generate_void_statement.hpp>
#include <stan/lang/generator/generate_write_array_method.hpp>

#endif
