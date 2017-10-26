#ifndef STAN_MATH_PRIM_MAT_HPP
#define STAN_MATH_PRIM_MAT_HPP

#include <stan/math/prim/arr/meta/get.hpp>
#include <stan/math/prim/arr/meta/index_type.hpp>
#include <stan/math/prim/arr/meta/is_vector.hpp>
#include <stan/math/prim/arr/meta/length.hpp>

#include <stan/math/prim/mat/meta/broadcast_array.hpp>
#include <stan/math/prim/mat/meta/get.hpp>
#include <stan/math/prim/mat/meta/index_type.hpp>
#include <stan/math/prim/mat/meta/is_constant_struct.hpp>
#include <stan/math/prim/mat/meta/is_vector.hpp>
#include <stan/math/prim/mat/meta/is_vector_like.hpp>
#include <stan/math/prim/mat/meta/length.hpp>
#include <stan/math/prim/mat/meta/length_mvt.hpp>
#include <stan/math/prim/mat/meta/seq_view.hpp>
#include <stan/math/prim/mat/meta/scalar_type.hpp>
#include <stan/math/prim/mat/meta/value_type.hpp>
#include <stan/math/prim/mat/meta/vector_seq_view.hpp>

#include <stan/math/prim/mat/err/check_cholesky_factor.hpp>
#include <stan/math/prim/mat/err/check_cholesky_factor_corr.hpp>
#include <stan/math/prim/mat/err/check_column_index.hpp>
#include <stan/math/prim/mat/err/check_corr_matrix.hpp>
#include <stan/math/prim/mat/err/check_cov_matrix.hpp>
#include <stan/math/prim/mat/err/check_ldlt_factor.hpp>
#include <stan/math/prim/mat/err/check_lower_triangular.hpp>
#include <stan/math/prim/mat/err/check_matching_dims.hpp>
#include <stan/math/prim/mat/err/check_multiplicable.hpp>
#include <stan/math/prim/mat/err/check_ordered.hpp>
#include <stan/math/prim/mat/err/check_pos_definite.hpp>
#include <stan/math/prim/mat/err/check_pos_semidefinite.hpp>
#include <stan/math/prim/mat/err/check_positive_ordered.hpp>
#include <stan/math/prim/mat/err/check_range.hpp>
#include <stan/math/prim/mat/err/check_row_index.hpp>
#include <stan/math/prim/mat/err/check_simplex.hpp>
#include <stan/math/prim/mat/err/check_spsd_matrix.hpp>
#include <stan/math/prim/mat/err/check_square.hpp>
#include <stan/math/prim/mat/err/check_std_vector_index.hpp>
#include <stan/math/prim/mat/err/check_symmetric.hpp>
#include <stan/math/prim/mat/err/check_unit_vector.hpp>
#include <stan/math/prim/mat/err/check_vector.hpp>
#include <stan/math/prim/mat/err/constraint_tolerance.hpp>
#include <stan/math/prim/mat/err/validate_non_negative_index.hpp>

#include <stan/math/prim/mat/fun/accumulator.hpp>
#include <stan/math/prim/mat/fun/acos.hpp>
#include <stan/math/prim/mat/fun/acosh.hpp>
#include <stan/math/prim/mat/fun/add.hpp>
#include <stan/math/prim/mat/fun/append_array.hpp>
#include <stan/math/prim/mat/fun/append_col.hpp>
#include <stan/math/prim/mat/fun/append_row.hpp>
#include <stan/math/prim/mat/fun/asin.hpp>
#include <stan/math/prim/mat/fun/asinh.hpp>
#include <stan/math/prim/mat/fun/assign.hpp>
#include <stan/math/prim/mat/fun/atan.hpp>
#include <stan/math/prim/mat/fun/atanh.hpp>
#include <stan/math/prim/mat/fun/autocorrelation.hpp>
#include <stan/math/prim/mat/fun/autocovariance.hpp>
#include <stan/math/prim/mat/fun/block.hpp>
#include <stan/math/prim/mat/fun/cbrt.hpp>
#include <stan/math/prim/mat/fun/ceil.hpp>
#include <stan/math/prim/mat/fun/chol2inv.hpp>
#include <stan/math/prim/mat/fun/cholesky_corr_constrain.hpp>
#include <stan/math/prim/mat/fun/cholesky_corr_free.hpp>
#include <stan/math/prim/mat/fun/cholesky_decompose.hpp>
#include <stan/math/prim/mat/fun/cholesky_factor_constrain.hpp>
#include <stan/math/prim/mat/fun/cholesky_factor_free.hpp>
#include <stan/math/prim/mat/fun/col.hpp>
#include <stan/math/prim/mat/fun/cols.hpp>
#include <stan/math/prim/mat/fun/columns_dot_product.hpp>
#include <stan/math/prim/mat/fun/columns_dot_self.hpp>
#include <stan/math/prim/mat/fun/common_type.hpp>
#include <stan/math/prim/mat/fun/corr_matrix_constrain.hpp>
#include <stan/math/prim/mat/fun/corr_matrix_free.hpp>
#include <stan/math/prim/mat/fun/cos.hpp>
#include <stan/math/prim/mat/fun/cosh.hpp>
#include <stan/math/prim/mat/fun/cov_exp_quad.hpp>
#include <stan/math/prim/mat/fun/cov_matrix_constrain.hpp>
#include <stan/math/prim/mat/fun/cov_matrix_constrain_lkj.hpp>
#include <stan/math/prim/mat/fun/cov_matrix_free.hpp>
#include <stan/math/prim/mat/fun/cov_matrix_free_lkj.hpp>
#include <stan/math/prim/mat/fun/crossprod.hpp>
#include <stan/math/prim/mat/fun/csr_extract_u.hpp>
#include <stan/math/prim/mat/fun/csr_extract_v.hpp>
#include <stan/math/prim/mat/fun/csr_extract_w.hpp>
#include <stan/math/prim/mat/fun/csr_matrix_times_vector.hpp>
#include <stan/math/prim/mat/fun/csr_to_dense_matrix.hpp>
#include <stan/math/prim/mat/fun/csr_u_to_z.hpp>
#include <stan/math/prim/mat/fun/cumulative_sum.hpp>
#include <stan/math/prim/mat/fun/determinant.hpp>
#include <stan/math/prim/mat/fun/diagonal.hpp>
#include <stan/math/prim/mat/fun/diag_matrix.hpp>
#include <stan/math/prim/mat/fun/diag_post_multiply.hpp>
#include <stan/math/prim/mat/fun/diag_pre_multiply.hpp>
#include <stan/math/prim/mat/fun/digamma.hpp>
#include <stan/math/prim/mat/fun/dims.hpp>
#include <stan/math/prim/mat/fun/distance.hpp>
#include <stan/math/prim/mat/fun/divide.hpp>
#include <stan/math/prim/mat/fun/dot_product.hpp>
#include <stan/math/prim/mat/fun/dot_self.hpp>
#include <stan/math/prim/mat/fun/Eigen.hpp>
#include <stan/math/prim/mat/fun/eigenvalues_sym.hpp>
#include <stan/math/prim/mat/fun/eigenvectors_sym.hpp>
#include <stan/math/prim/mat/fun/elt_divide.hpp>
#include <stan/math/prim/mat/fun/elt_multiply.hpp>
#include <stan/math/prim/mat/fun/erf.hpp>
#include <stan/math/prim/mat/fun/erfc.hpp>
#include <stan/math/prim/mat/fun/exp.hpp>
#include <stan/math/prim/mat/fun/exp2.hpp>
#include <stan/math/prim/mat/fun/expm1.hpp>
#include <stan/math/prim/mat/fun/fabs.hpp>
#include <stan/math/prim/mat/fun/factor_cov_matrix.hpp>
#include <stan/math/prim/mat/fun/factor_U.hpp>
#include <stan/math/prim/mat/fun/fill.hpp>
#include <stan/math/prim/mat/fun/floor.hpp>
#include <stan/math/prim/mat/fun/get_base1.hpp>
#include <stan/math/prim/mat/fun/get_base1_lhs.hpp>
#include <stan/math/prim/mat/fun/get_lp.hpp>
#include <stan/math/prim/mat/fun/head.hpp>
#include <stan/math/prim/mat/fun/initialize.hpp>
#include <stan/math/prim/mat/fun/inv.hpp>
#include <stan/math/prim/mat/fun/inverse.hpp>
#include <stan/math/prim/mat/fun/inverse_spd.hpp>
#include <stan/math/prim/mat/fun/inv_cloglog.hpp>
#include <stan/math/prim/mat/fun/inv_logit.hpp>
#include <stan/math/prim/mat/fun/inv_Phi.hpp>
#include <stan/math/prim/mat/fun/inv_sqrt.hpp>
#include <stan/math/prim/mat/fun/inv_square.hpp>
#include <stan/math/prim/mat/fun/LDLT_factor.hpp>
#include <stan/math/prim/mat/fun/lgamma.hpp>
#include <stan/math/prim/mat/fun/log.hpp>
#include <stan/math/prim/mat/fun/log10.hpp>
#include <stan/math/prim/mat/fun/log1m.hpp>
#include <stan/math/prim/mat/fun/log1m_exp.hpp>
#include <stan/math/prim/mat/fun/log1m_inv_logit.hpp>
#include <stan/math/prim/mat/fun/log1p.hpp>
#include <stan/math/prim/mat/fun/log1p_exp.hpp>
#include <stan/math/prim/mat/fun/log2.hpp>
#include <stan/math/prim/mat/fun/log_determinant.hpp>
#include <stan/math/prim/mat/fun/log_determinant_ldlt.hpp>
#include <stan/math/prim/mat/fun/log_determinant_spd.hpp>
#include <stan/math/prim/mat/fun/log_inv_logit.hpp>
#include <stan/math/prim/mat/fun/log_softmax.hpp>
#include <stan/math/prim/mat/fun/log_sum_exp.hpp>
#include <stan/math/prim/mat/fun/logit.hpp>
#include <stan/math/prim/mat/fun/make_nu.hpp>
#include <stan/math/prim/mat/fun/matrix_exp.hpp>
#include <stan/math/prim/mat/fun/max.hpp>
#include <stan/math/prim/mat/fun/mdivide_left.hpp>
#include <stan/math/prim/mat/fun/mdivide_left_ldlt.hpp>
#include <stan/math/prim/mat/fun/mdivide_left_spd.hpp>
#include <stan/math/prim/mat/fun/mdivide_left_tri.hpp>
#include <stan/math/prim/mat/fun/mdivide_left_tri_low.hpp>
#include <stan/math/prim/mat/fun/mdivide_right.hpp>
#include <stan/math/prim/mat/fun/mdivide_right_ldlt.hpp>
#include <stan/math/prim/mat/fun/mdivide_right_spd.hpp>
#include <stan/math/prim/mat/fun/mdivide_right_tri.hpp>
#include <stan/math/prim/mat/fun/mdivide_right_tri_low.hpp>
#include <stan/math/prim/mat/fun/mean.hpp>
#include <stan/math/prim/mat/fun/min.hpp>
#include <stan/math/prim/mat/fun/minus.hpp>
#include <stan/math/prim/mat/fun/multiply.hpp>
#include <stan/math/prim/mat/fun/multiply_lower_tri_self_transpose.hpp>
#include <stan/math/prim/mat/fun/num_elements.hpp>
#include <stan/math/prim/mat/fun/ordered_constrain.hpp>
#include <stan/math/prim/mat/fun/ordered_free.hpp>
#include <stan/math/prim/mat/fun/Phi.hpp>
#include <stan/math/prim/mat/fun/Phi_approx.hpp>
#include <stan/math/prim/mat/fun/positive_ordered_constrain.hpp>
#include <stan/math/prim/mat/fun/positive_ordered_free.hpp>
#include <stan/math/prim/mat/fun/prod.hpp>
#include <stan/math/prim/mat/fun/promote_common.hpp>
#include <stan/math/prim/mat/fun/promote_elements.hpp>
#include <stan/math/prim/mat/fun/promote_scalar.hpp>
#include <stan/math/prim/mat/fun/promote_scalar_type.hpp>
#include <stan/math/prim/mat/fun/qr_Q.hpp>
#include <stan/math/prim/mat/fun/qr_R.hpp>
#include <stan/math/prim/mat/fun/quad_form.hpp>
#include <stan/math/prim/mat/fun/quad_form_diag.hpp>
#include <stan/math/prim/mat/fun/quad_form_sym.hpp>
#include <stan/math/prim/mat/fun/rank.hpp>
#include <stan/math/prim/mat/fun/read_corr_L.hpp>
#include <stan/math/prim/mat/fun/read_corr_matrix.hpp>
#include <stan/math/prim/mat/fun/read_cov_L.hpp>
#include <stan/math/prim/mat/fun/read_cov_matrix.hpp>
#include <stan/math/prim/mat/fun/rep_matrix.hpp>
#include <stan/math/prim/mat/fun/rep_row_vector.hpp>
#include <stan/math/prim/mat/fun/rep_vector.hpp>
#include <stan/math/prim/mat/fun/resize.hpp>
#include <stan/math/prim/mat/fun/round.hpp>
#include <stan/math/prim/mat/fun/row.hpp>
#include <stan/math/prim/mat/fun/rows.hpp>
#include <stan/math/prim/mat/fun/rows_dot_product.hpp>
#include <stan/math/prim/mat/fun/rows_dot_self.hpp>
#include <stan/math/prim/mat/fun/sd.hpp>
#include <stan/math/prim/mat/fun/segment.hpp>
#include <stan/math/prim/mat/fun/simplex_constrain.hpp>
#include <stan/math/prim/mat/fun/simplex_free.hpp>
#include <stan/math/prim/mat/fun/sin.hpp>
#include <stan/math/prim/mat/fun/singular_values.hpp>
#include <stan/math/prim/mat/fun/sinh.hpp>
#include <stan/math/prim/mat/fun/size.hpp>
#include <stan/math/prim/mat/fun/softmax.hpp>
#include <stan/math/prim/mat/fun/sort_asc.hpp>
#include <stan/math/prim/mat/fun/sort_desc.hpp>
#include <stan/math/prim/mat/fun/sort_indices.hpp>
#include <stan/math/prim/mat/fun/sort_indices_asc.hpp>
#include <stan/math/prim/mat/fun/sort_indices_desc.hpp>
#include <stan/math/prim/mat/fun/sqrt.hpp>
#include <stan/math/prim/mat/fun/square.hpp>
#include <stan/math/prim/mat/fun/squared_distance.hpp>
#include <stan/math/prim/mat/fun/stan_print.hpp>
#include <stan/math/prim/mat/fun/subtract.hpp>
#include <stan/math/prim/mat/fun/sub_col.hpp>
#include <stan/math/prim/mat/fun/sub_row.hpp>
#include <stan/math/prim/mat/fun/sum.hpp>
#include <stan/math/prim/mat/fun/tail.hpp>
#include <stan/math/prim/mat/fun/tan.hpp>
#include <stan/math/prim/mat/fun/tanh.hpp>
#include <stan/math/prim/mat/fun/tcrossprod.hpp>
#include <stan/math/prim/mat/fun/tgamma.hpp>
#include <stan/math/prim/mat/fun/to_array_1d.hpp>
#include <stan/math/prim/mat/fun/to_array_2d.hpp>
#include <stan/math/prim/mat/fun/to_matrix.hpp>
#include <stan/math/prim/mat/fun/to_row_vector.hpp>
#include <stan/math/prim/mat/fun/to_vector.hpp>
#include <stan/math/prim/mat/fun/trace.hpp>
#include <stan/math/prim/mat/fun/trace_gen_inv_quad_form_ldlt.hpp>
#include <stan/math/prim/mat/fun/trace_gen_quad_form.hpp>
#include <stan/math/prim/mat/fun/trace_inv_quad_form_ldlt.hpp>
#include <stan/math/prim/mat/fun/trace_quad_form.hpp>
#include <stan/math/prim/mat/fun/transpose.hpp>
#include <stan/math/prim/mat/fun/trigamma.hpp>
#include <stan/math/prim/mat/fun/trunc.hpp>
#include <stan/math/prim/mat/fun/typedefs.hpp>
#include <stan/math/prim/mat/fun/unit_vector_constrain.hpp>
#include <stan/math/prim/mat/fun/unit_vector_free.hpp>
#include <stan/math/prim/mat/fun/value_of.hpp>
#include <stan/math/prim/mat/fun/value_of_rec.hpp>
#include <stan/math/prim/mat/fun/variance.hpp>
#include <stan/math/prim/mat/fun/welford_covar_estimator.hpp>
#include <stan/math/prim/mat/fun/welford_var_estimator.hpp>

#include <stan/math/prim/mat/functor/finite_diff_gradient.hpp>
#include <stan/math/prim/mat/functor/finite_diff_hessian.hpp>

#include <stan/math/prim/mat/prob/bernoulli_logit_glm_lpmf.hpp>
#include <stan/math/prim/mat/prob/categorical_log.hpp>
#include <stan/math/prim/mat/prob/categorical_lpmf.hpp>
#include <stan/math/prim/mat/prob/categorical_logit_log.hpp>
#include <stan/math/prim/mat/prob/categorical_logit_lpmf.hpp>
#include <stan/math/prim/mat/prob/categorical_rng.hpp>
#include <stan/math/prim/mat/prob/categorical_logit_rng.hpp>
#include <stan/math/prim/mat/prob/dirichlet_log.hpp>
#include <stan/math/prim/mat/prob/dirichlet_lpmf.hpp>
#include <stan/math/prim/mat/prob/dirichlet_rng.hpp>
#include <stan/math/prim/mat/prob/gaussian_dlm_obs_log.hpp>
#include <stan/math/prim/mat/prob/gaussian_dlm_obs_lpdf.hpp>
#include <stan/math/prim/mat/prob/inv_wishart_log.hpp>
#include <stan/math/prim/mat/prob/inv_wishart_lpdf.hpp>
#include <stan/math/prim/mat/prob/inv_wishart_rng.hpp>
#include <stan/math/prim/mat/prob/lkj_corr_cholesky_log.hpp>
#include <stan/math/prim/mat/prob/lkj_corr_cholesky_lpdf.hpp>
#include <stan/math/prim/mat/prob/lkj_corr_cholesky_rng.hpp>
#include <stan/math/prim/mat/prob/lkj_corr_log.hpp>
#include <stan/math/prim/mat/prob/lkj_corr_lpdf.hpp>
#include <stan/math/prim/mat/prob/lkj_corr_rng.hpp>
#include <stan/math/prim/mat/prob/lkj_cov_log.hpp>
#include <stan/math/prim/mat/prob/lkj_cov_lpdf.hpp>
#include <stan/math/prim/mat/prob/matrix_normal_prec_log.hpp>
#include <stan/math/prim/mat/prob/matrix_normal_prec_lpdf.hpp>
#include <stan/math/prim/mat/prob/multi_gp_cholesky_log.hpp>
#include <stan/math/prim/mat/prob/multi_gp_cholesky_lpdf.hpp>
#include <stan/math/prim/mat/prob/multi_gp_log.hpp>
#include <stan/math/prim/mat/prob/multi_gp_lpdf.hpp>
#include <stan/math/prim/mat/prob/multi_normal_cholesky_log.hpp>
#include <stan/math/prim/mat/prob/multi_normal_cholesky_lpdf.hpp>
#include <stan/math/prim/mat/prob/multi_normal_cholesky_rng.hpp>
#include <stan/math/prim/mat/prob/multi_normal_log.hpp>
#include <stan/math/prim/mat/prob/multi_normal_lpdf.hpp>
#include <stan/math/prim/mat/prob/multi_normal_prec_log.hpp>
#include <stan/math/prim/mat/prob/multi_normal_prec_lpdf.hpp>
#include <stan/math/prim/mat/prob/multi_normal_rng.hpp>
#include <stan/math/prim/mat/prob/multi_student_t_log.hpp>
#include <stan/math/prim/mat/prob/multi_student_t_lpdf.hpp>
#include <stan/math/prim/mat/prob/multi_student_t_rng.hpp>
#include <stan/math/prim/mat/prob/multinomial_log.hpp>
#include <stan/math/prim/mat/prob/multinomial_lpmf.hpp>
#include <stan/math/prim/mat/prob/multinomial_rng.hpp>
#include <stan/math/prim/mat/prob/ordered_logistic_log.hpp>
#include <stan/math/prim/mat/prob/ordered_logistic_lpmf.hpp>
#include <stan/math/prim/mat/prob/ordered_logistic_rng.hpp>
#include <stan/math/prim/mat/prob/ordered_probit_log.hpp>
#include <stan/math/prim/mat/prob/ordered_probit_lpmf.hpp>
#include <stan/math/prim/mat/prob/ordered_probit_rng.hpp>
#include <stan/math/prim/mat/prob/wishart_log.hpp>
#include <stan/math/prim/mat/prob/wishart_lpdf.hpp>
#include <stan/math/prim/mat/prob/wishart_rng.hpp>

#include <stan/math/prim/mat/vectorize/apply_scalar_unary.hpp>

#include <stan/math/prim/arr.hpp>


#endif
