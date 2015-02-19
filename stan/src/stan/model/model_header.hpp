#ifndef STAN__MODEL__MODEL__HEADER_HPP__
#define STAN__MODEL__MODEL__HEADER_HPP__

#include <boost/exception/all.hpp>
#include <boost/random/linear_congruential.hpp>


#include <stan/io/cmd_line.hpp>
#include <stan/io/dump.hpp>
#include <stan/io/reader.hpp>
#include <stan/io/writer.hpp>
#include <stan/io/csv_writer.hpp>

#include <stan/math/prim/arr/err/domain_error_vec.hpp>
#include <stan/math/prim/arr/err/invalid_argument_vec.hpp>
#include <stan/math/prim/arr/functor/coupled_ode_observer.hpp>
#include <stan/math/prim/arr/functor/coupled_ode_system.hpp>
#include <stan/math/prim/arr/functor/integrate_ode.hpp>
#include <stan/math/prim/mat/err/check_cholesky_factor.hpp>
#include <stan/math/prim/mat/err/check_cholesky_factor_corr.hpp>
#include <stan/math/prim/mat/err/check_column_index.hpp>
#include <stan/math/prim/mat/err/check_corr_matrix.hpp>
#include <stan/math/prim/mat/err/check_cov_matrix.hpp>
#include <stan/math/prim/mat/err/check_ldlt_factor.hpp>
#include <stan/math/prim/mat/err/check_lower_triangular.hpp>
#include <stan/math/prim/mat/err/check_matching_dims.hpp>
#include <stan/math/prim/mat/err/check_matching_sizes.hpp>
#include <stan/math/prim/mat/err/check_multiplicable.hpp>
#include <stan/math/prim/mat/err/check_nonzero_size.hpp>
#include <stan/math/prim/mat/err/check_ordered.hpp>
#include <stan/math/prim/mat/err/check_pos_definite.hpp>
#include <stan/math/prim/mat/err/check_pos_semidefinite.hpp>
#include <stan/math/prim/mat/err/check_positive_ordered.hpp>
#include <stan/math/prim/mat/err/check_range.hpp>
#include <stan/math/prim/mat/err/check_row_index.hpp>
#include <stan/math/prim/mat/err/check_simplex.hpp>
#include <stan/math/prim/mat/err/check_size_match.hpp>
#include <stan/math/prim/mat/err/check_spsd_matrix.hpp>
#include <stan/math/prim/mat/err/check_square.hpp>
#include <stan/math/prim/mat/err/check_std_vector_index.hpp>
#include <stan/math/prim/mat/err/check_symmetric.hpp>
#include <stan/math/prim/mat/err/check_unit_vector.hpp>
#include <stan/math/prim/mat/err/check_vector.hpp>
#include <stan/math/prim/mat/err/constraint_tolerance.hpp>
#include <stan/math/prim/mat/err/validate_non_negative_index.hpp>
#include <stan/math/prim/mat/fun/accumulator.hpp>
#include <stan/math/prim/mat/fun/add.hpp>
#include <stan/math/prim/mat/fun/append_col.hpp>
#include <stan/math/prim/mat/fun/append_row.hpp>
#include <stan/math/prim/mat/fun/array_builder.hpp>
#include <stan/math/prim/mat/fun/assign.hpp>
#include <stan/math/prim/mat/fun/autocorrelation.hpp>
#include <stan/math/prim/mat/fun/autocovariance.hpp>
#include <stan/math/prim/mat/fun/block.hpp>
#include <stan/math/prim/mat/fun/cholesky_decompose.hpp>
#include <stan/math/prim/mat/fun/col.hpp>
#include <stan/math/prim/mat/fun/cols.hpp>
#include <stan/math/prim/mat/fun/columns_dot_product.hpp>
#include <stan/math/prim/mat/fun/columns_dot_self.hpp>
#include <stan/math/prim/mat/fun/common_type.hpp>
#include <stan/math/prim/mat/fun/crossprod.hpp>
#include <stan/math/prim/mat/fun/cumulative_sum.hpp>
#include <stan/math/prim/mat/fun/determinant.hpp>
#include <stan/math/prim/mat/fun/diag_matrix.hpp>
#include <stan/math/prim/mat/fun/diag_post_multiply.hpp>
#include <stan/math/prim/mat/fun/diag_pre_multiply.hpp>
#include <stan/math/prim/mat/fun/diagonal.hpp>
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
#include <stan/math/prim/mat/fun/exp.hpp>
#include <stan/math/prim/mat/fun/fill.hpp>
#include <stan/math/prim/mat/fun/get_base1.hpp>
#include <stan/math/prim/mat/fun/get_base1_lhs.hpp>
#include <stan/math/prim/mat/fun/get_lp.hpp>
#include <stan/math/prim/mat/fun/head.hpp>
#include <stan/math/prim/mat/fun/initialize.hpp>
#include <stan/math/prim/mat/fun/inverse.hpp>
#include <stan/math/prim/mat/fun/inverse_spd.hpp>
#include <stan/math/prim/mat/fun/LDLT_factor.hpp>
#include <stan/math/prim/mat/fun/log.hpp>
#include <stan/math/prim/mat/fun/log_determinant.hpp>
#include <stan/math/prim/mat/fun/log_determinant_ldlt.hpp>
#include <stan/math/prim/mat/fun/log_determinant_spd.hpp>
#include <stan/math/prim/mat/fun/log_softmax.hpp>
#include <stan/math/prim/mat/fun/log_sum_exp.hpp>
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
#include <stan/math/prim/mat/fun/prod.hpp>
#include <stan/math/prim/mat/fun/promote_common.hpp>
#include <stan/math/prim/mat/fun/promote_scalar.hpp>
#include <stan/math/prim/mat/fun/promote_scalar_type.hpp>
#include <stan/math/prim/mat/fun/promoter.hpp>
#include <stan/math/prim/mat/fun/qr_Q.hpp>
#include <stan/math/prim/mat/fun/qr_R.hpp>
#include <stan/math/prim/mat/fun/quad_form.hpp>
#include <stan/math/prim/mat/fun/quad_form_diag.hpp>
#include <stan/math/prim/mat/fun/quad_form_sym.hpp>
#include <stan/math/prim/mat/fun/rank.hpp>
#include <stan/math/prim/mat/fun/rep_matrix.hpp>
#include <stan/math/prim/mat/fun/rep_row_vector.hpp>
#include <stan/math/prim/mat/fun/rep_vector.hpp>
#include <stan/math/prim/mat/fun/resize.hpp>
#include <stan/math/prim/mat/fun/row.hpp>
#include <stan/math/prim/mat/fun/rows.hpp>
#include <stan/math/prim/mat/fun/rows_dot_product.hpp>
#include <stan/math/prim/mat/fun/rows_dot_self.hpp>
#include <stan/math/prim/mat/fun/sd.hpp>
#include <stan/math/prim/mat/fun/segment.hpp>
#include <stan/math/prim/mat/fun/singular_values.hpp>
#include <stan/math/prim/mat/fun/size.hpp>
#include <stan/math/prim/mat/fun/softmax.hpp>
#include <stan/math/prim/mat/fun/sort.hpp>
#include <stan/math/prim/mat/fun/sort_indices.hpp>
#include <stan/math/prim/mat/fun/squared_distance.hpp>
#include <stan/math/prim/mat/fun/stan_print.hpp>
#include <stan/math/prim/mat/fun/sub_col.hpp>
#include <stan/math/prim/mat/fun/sub_row.hpp>
#include <stan/math/prim/mat/fun/subtract.hpp>
#include <stan/math/prim/mat/fun/sum.hpp>
#include <stan/math/prim/mat/fun/tail.hpp>
#include <stan/math/prim/mat/fun/tcrossprod.hpp>
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
#include <stan/math/prim/mat/fun/typedefs.hpp>
#include <stan/math/prim/mat/fun/value_of.hpp>
#include <stan/math/prim/mat/fun/value_of_rec.hpp>
#include <stan/math/prim/mat/fun/variance.hpp>
#include <stan/math/prim/mat/fun/welford_covar_estimator.hpp>
#include <stan/math/prim/mat/fun/welford_var_estimator.hpp>
#include <stan/math/prim/mat/meta/index_type.hpp>
#include <stan/math/prim/mat/meta/seq_view.hpp>
#include <stan/math/prim/mat/meta/value_type.hpp>
#include <stan/math/prim/mat/prob/categorical_log.hpp>
#include <stan/math/prim/mat/prob/categorical_logit_log.hpp>
#include <stan/math/prim/mat/prob/categorical_rng.hpp>
#include <stan/math/prim/mat/prob/dirichlet_log.hpp>
#include <stan/math/prim/mat/prob/dirichlet_rng.hpp>
#include <stan/math/prim/mat/prob/gaussian_dlm_obs_log.hpp>
#include <stan/math/prim/mat/prob/inv_wishart_log.hpp>
#include <stan/math/prim/mat/prob/inv_wishart_rng.hpp>
#include <stan/math/prim/mat/prob/lkj_corr_cholesky_log.hpp>
#include <stan/math/prim/mat/prob/lkj_corr_cholesky_rng.hpp>
#include <stan/math/prim/mat/prob/lkj_corr_log.hpp>
#include <stan/math/prim/mat/prob/lkj_corr_rng.hpp>
#include <stan/math/prim/mat/prob/lkj_cov_log.hpp>
#include <stan/math/prim/mat/prob/matrix_normal_prec_log.hpp>
#include <stan/math/prim/mat/prob/multi_gp_cholesky_log.hpp>
#include <stan/math/prim/mat/prob/multi_gp_log.hpp>
#include <stan/math/prim/mat/prob/multi_normal_cholesky_log.hpp>
#include <stan/math/prim/mat/prob/multi_normal_cholesky_rng.hpp>
#include <stan/math/prim/mat/prob/multi_normal_log.hpp>
#include <stan/math/prim/mat/prob/multi_normal_prec_log.hpp>
#include <stan/math/prim/mat/prob/multi_normal_rng.hpp>
#include <stan/math/prim/mat/prob/multi_student_t_log.hpp>
#include <stan/math/prim/mat/prob/multi_student_t_rng.hpp>
#include <stan/math/prim/mat/prob/multinomial_log.hpp>
#include <stan/math/prim/mat/prob/multinomial_rng.hpp>
#include <stan/math/prim/mat/prob/wishart_log.hpp>
#include <stan/math/prim/mat/prob/wishart_rng.hpp>
#include <stan/math/prim/scal/err/check_bounded.hpp>
#include <stan/math/prim/scal/err/check_consistent_size.hpp>
#include <stan/math/prim/scal/err/check_consistent_sizes.hpp>
#include <stan/math/prim/scal/err/check_equal.hpp>
#include <stan/math/prim/scal/err/check_finite.hpp>
#include <stan/math/prim/scal/err/check_greater.hpp>
#include <stan/math/prim/scal/err/check_greater_or_equal.hpp>
#include <stan/math/prim/scal/err/check_less.hpp>
#include <stan/math/prim/scal/err/check_less_or_equal.hpp>
#include <stan/math/prim/scal/err/check_nonnegative.hpp>
#include <stan/math/prim/scal/err/check_not_nan.hpp>
#include <stan/math/prim/scal/err/check_positive.hpp>
#include <stan/math/prim/scal/err/check_positive_finite.hpp>
#include <stan/math/prim/scal/err/check_positive_size.hpp>
#include <stan/math/prim/scal/err/domain_error.hpp>
#include <stan/math/prim/scal/err/invalid_argument.hpp>
#include <stan/math/prim/scal/err/out_of_range.hpp>
#include <stan/math/prim/scal/fun/abs.hpp>
#include <stan/math/prim/scal/fun/as_bool.hpp>
#include <stan/math/prim/scal/fun/bessel_first_kind.hpp>
#include <stan/math/prim/scal/fun/bessel_second_kind.hpp>
#include <stan/math/prim/scal/fun/binary_log_loss.hpp>
#include <stan/math/prim/scal/fun/binomial_coefficient_log.hpp>
#include <stan/math/prim/scal/fun/constants.hpp>
#include <stan/math/prim/scal/fun/digamma.hpp>
#include <stan/math/prim/scal/fun/dist.hpp>
#include <stan/math/prim/scal/fun/divide.hpp>
#include <stan/math/prim/scal/fun/dot.hpp>
#include <stan/math/prim/scal/fun/dot_self.hpp>
#include <stan/math/prim/scal/fun/exp2.hpp>
#include <stan/math/prim/scal/fun/F32.hpp>
#include <stan/math/prim/scal/fun/falling_factorial.hpp>
#include <stan/math/prim/scal/fun/fdim.hpp>
#include <stan/math/prim/scal/fun/gamma_p.hpp>
#include <stan/math/prim/scal/fun/gamma_q.hpp>
#include <stan/math/prim/scal/fun/grad_2F1.hpp>
#include <stan/math/prim/scal/fun/grad_F32.hpp>
#include <stan/math/prim/scal/fun/grad_inc_beta.hpp>
#include <stan/math/prim/scal/fun/grad_reg_inc_beta.hpp>
#include <stan/math/prim/scal/fun/grad_reg_inc_gamma.hpp>
#include <stan/math/prim/scal/fun/ibeta.hpp>
#include <stan/math/prim/scal/fun/if_else.hpp>
#include <stan/math/prim/scal/fun/inc_beta.hpp>
#include <stan/math/prim/scal/fun/int_step.hpp>
#include <stan/math/prim/scal/fun/inv.hpp>
#include <stan/math/prim/scal/fun/inv_cloglog.hpp>
#include <stan/math/prim/scal/fun/inv_logit.hpp>
#include <stan/math/prim/scal/fun/inv_sqrt.hpp>
#include <stan/math/prim/scal/fun/inv_square.hpp>
#include <stan/math/prim/scal/fun/inverse_softmax.hpp>
#include <stan/math/prim/scal/fun/is_inf.hpp>
#include <stan/math/prim/scal/fun/is_nan.hpp>
#include <stan/math/prim/scal/fun/is_uninitialized.hpp>
#include <stan/math/prim/scal/fun/lbeta.hpp>
#include <stan/math/prim/scal/fun/lgamma.hpp>
#include <stan/math/prim/scal/fun/lmgamma.hpp>
#include <stan/math/prim/scal/fun/log1m.hpp>
#include <stan/math/prim/scal/fun/log1m_exp.hpp>
#include <stan/math/prim/scal/fun/log1m_inv_logit.hpp>
#include <stan/math/prim/scal/fun/log1p.hpp>
#include <stan/math/prim/scal/fun/log1p_exp.hpp>
#include <stan/math/prim/scal/fun/log2.hpp>
#include <stan/math/prim/scal/fun/log_diff_exp.hpp>
#include <stan/math/prim/scal/fun/log_falling_factorial.hpp>
#include <stan/math/prim/scal/fun/log_inv_logit.hpp>
#include <stan/math/prim/scal/fun/log_mix.hpp>
#include <stan/math/prim/scal/fun/log_rising_factorial.hpp>
#include <stan/math/prim/scal/fun/log_sum_exp.hpp>
#include <stan/math/prim/scal/fun/logical_and.hpp>
#include <stan/math/prim/scal/fun/logical_eq.hpp>
#include <stan/math/prim/scal/fun/logical_gt.hpp>
#include <stan/math/prim/scal/fun/logical_gte.hpp>
#include <stan/math/prim/scal/fun/logical_lt.hpp>
#include <stan/math/prim/scal/fun/logical_lte.hpp>
#include <stan/math/prim/scal/fun/logical_negation.hpp>
#include <stan/math/prim/scal/fun/logical_neq.hpp>
#include <stan/math/prim/scal/fun/logical_or.hpp>
#include <stan/math/prim/scal/fun/logit.hpp>
#include <stan/math/prim/scal/fun/max.hpp>
#include <stan/math/prim/scal/fun/min.hpp>
#include <stan/math/prim/scal/fun/modified_bessel_first_kind.hpp>
#include <stan/math/prim/scal/fun/modified_bessel_second_kind.hpp>
#include <stan/math/prim/scal/fun/modulus.hpp>
#include <stan/math/prim/scal/fun/multiply_log.hpp>
#include <stan/math/prim/scal/fun/owens_t.hpp>
#include <stan/math/prim/scal/fun/Phi.hpp>
#include <stan/math/prim/scal/fun/Phi_approx.hpp>
#include <stan/math/prim/scal/fun/primitive_value.hpp>
#include <stan/math/prim/scal/fun/promote_scalar.hpp>
#include <stan/math/prim/scal/fun/promote_scalar_type.hpp>
#include <stan/math/prim/scal/fun/rep_array.hpp>
#include <stan/math/prim/scal/fun/rising_factorial.hpp>
#include <stan/math/prim/scal/fun/scaled_add.hpp>
#include <stan/math/prim/scal/fun/sign.hpp>
#include <stan/math/prim/scal/fun/square.hpp>
#include <stan/math/prim/scal/fun/step.hpp>
#include <stan/math/prim/scal/fun/sub.hpp>
#include <stan/math/prim/scal/fun/sum.hpp>
#include <stan/math/prim/scal/fun/factor_cov_matrix.hpp>
#include <stan/math/prim/scal/fun/factor_U.hpp>
#include <stan/math/prim/scal/fun/read_corr_L.hpp>
#include <stan/math/prim/scal/fun/read_corr_matrix.hpp>
#include <stan/math/prim/scal/fun/read_cov_L.hpp>
#include <stan/math/prim/scal/fun/read_cov_matrix.hpp>
#include <stan/math/prim/scal/fun/make_nu.hpp>
#include <stan/math/prim/scal/fun/identity_constrain.hpp>
#include <stan/math/prim/scal/fun/identity_free.hpp>
#include <stan/math/prim/scal/fun/positive_constrain.hpp>
#include <stan/math/prim/scal/fun/positive_free.hpp>
#include <stan/math/prim/scal/fun/lb_constrain.hpp>
#include <stan/math/prim/scal/fun/lb_free.hpp>
#include <stan/math/prim/scal/fun/ub_constrain.hpp>
#include <stan/math/prim/scal/fun/ub_free.hpp>
#include <stan/math/prim/scal/fun/lub_constrain.hpp>
#include <stan/math/prim/scal/fun/lub_free.hpp>
#include <stan/math/prim/scal/fun/prob_constrain.hpp>
#include <stan/math/prim/scal/fun/prob_free.hpp>
#include <stan/math/prim/scal/fun/corr_constrain.hpp>
#include <stan/math/prim/scal/fun/corr_free.hpp>
#include <stan/math/prim/scal/fun/unit_vector_constrain.hpp>
#include <stan/math/prim/scal/fun/unit_vector_free.hpp>
#include <stan/math/prim/scal/fun/simplex_constrain.hpp>
#include <stan/math/prim/scal/fun/simplex_free.hpp>
#include <stan/math/prim/scal/fun/ordered_constrain.hpp>
#include <stan/math/prim/scal/fun/ordered_free.hpp>
#include <stan/math/prim/scal/fun/positive_ordered_constrain.hpp>
#include <stan/math/prim/scal/fun/positive_ordered_free.hpp>
#include <stan/math/prim/scal/fun/cholesky_factor_constrain.hpp>
#include <stan/math/prim/scal/fun/cholesky_factor_free.hpp>
#include <stan/math/prim/scal/fun/cholesky_corr_constrain.hpp>
#include <stan/math/prim/scal/fun/cholesky_corr_free.hpp>
#include <stan/math/prim/scal/fun/corr_matrix_constrain.hpp>
#include <stan/math/prim/scal/fun/corr_matrix_free.hpp>
#include <stan/math/prim/scal/fun/cov_matrix_constrain.hpp>
#include <stan/math/prim/scal/fun/cov_matrix_free.hpp>
#include <stan/math/prim/scal/fun/cov_matrix_constrain_lkj.hpp>
#include <stan/math/prim/scal/fun/cov_matrix_free_lkj.hpp>
#include <stan/math/prim/scal/fun/trigamma.hpp>
#include <stan/math/prim/scal/fun/value_of.hpp>
#include <stan/math/prim/scal/fun/value_of_rec.hpp>
#include <stan/math/prim/scal/meta/child_type.hpp>
#include <stan/math/prim/scal/meta/constants.hpp>
#include <stan/math/prim/scal/meta/index_type.hpp>
#include <stan/math/prim/scal/meta/likely.hpp>
#include <stan/math/prim/scal/meta/include_summand.hpp>

#include <stan/math/prim/scal/meta/value_type.hpp>
#include <stan/math/prim/scal/prob/bernoulli_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/bernoulli_cdf.hpp>
#include <stan/math/prim/scal/prob/bernoulli_cdf_log.hpp>
#include <stan/math/prim/scal/prob/bernoulli_log.hpp>
#include <stan/math/prim/scal/prob/bernoulli_logit_log.hpp>
#include <stan/math/prim/scal/prob/bernoulli_rng.hpp>
#include <stan/math/prim/scal/prob/beta_binomial_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/beta_binomial_cdf.hpp>
#include <stan/math/prim/scal/prob/beta_binomial_cdf_log.hpp>
#include <stan/math/prim/scal/prob/beta_binomial_log.hpp>
#include <stan/math/prim/scal/prob/beta_binomial_rng.hpp>
#include <stan/math/prim/scal/prob/beta_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/beta_cdf.hpp>
#include <stan/math/prim/scal/prob/beta_cdf_log.hpp>
#include <stan/math/prim/scal/prob/beta_log.hpp>
#include <stan/math/prim/scal/prob/beta_rng.hpp>
#include <stan/math/prim/scal/prob/binomial_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/binomial_cdf.hpp>
#include <stan/math/prim/scal/prob/binomial_cdf_log.hpp>
#include <stan/math/prim/scal/prob/binomial_log.hpp>
#include <stan/math/prim/scal/prob/binomial_logit_log.hpp>
#include <stan/math/prim/scal/prob/binomial_rng.hpp>
#include <stan/math/prim/scal/prob/cauchy_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/cauchy_cdf.hpp>
#include <stan/math/prim/scal/prob/cauchy_cdf_log.hpp>
#include <stan/math/prim/scal/prob/cauchy_log.hpp>
#include <stan/math/prim/scal/prob/cauchy_rng.hpp>
#include <stan/math/prim/scal/prob/chi_square_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/chi_square_cdf.hpp>
#include <stan/math/prim/scal/prob/chi_square_cdf_log.hpp>
#include <stan/math/prim/scal/prob/chi_square_log.hpp>
#include <stan/math/prim/scal/prob/chi_square_rng.hpp>
#include <stan/math/prim/scal/prob/double_exponential_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/double_exponential_cdf.hpp>
#include <stan/math/prim/scal/prob/double_exponential_cdf_log.hpp>
#include <stan/math/prim/scal/prob/double_exponential_log.hpp>
#include <stan/math/prim/scal/prob/double_exponential_rng.hpp>
#include <stan/math/prim/scal/prob/exp_mod_normal_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/exp_mod_normal_cdf.hpp>
#include <stan/math/prim/scal/prob/exp_mod_normal_cdf_log.hpp>
#include <stan/math/prim/scal/prob/exp_mod_normal_log.hpp>
#include <stan/math/prim/scal/prob/exp_mod_normal_rng.hpp>
#include <stan/math/prim/scal/prob/exponential_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/exponential_cdf.hpp>
#include <stan/math/prim/scal/prob/exponential_cdf_log.hpp>
#include <stan/math/prim/scal/prob/exponential_log.hpp>
#include <stan/math/prim/scal/prob/exponential_rng.hpp>
#include <stan/math/prim/scal/prob/frechet_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/frechet_cdf.hpp>
#include <stan/math/prim/scal/prob/frechet_cdf_log.hpp>
#include <stan/math/prim/scal/prob/frechet_log.hpp>
#include <stan/math/prim/scal/prob/frechet_rng.hpp>
#include <stan/math/prim/scal/prob/gamma_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/gamma_cdf.hpp>
#include <stan/math/prim/scal/prob/gamma_cdf_log.hpp>
#include <stan/math/prim/scal/prob/gamma_log.hpp>
#include <stan/math/prim/scal/prob/gamma_rng.hpp>
#include <stan/math/prim/scal/prob/gumbel_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/gumbel_cdf.hpp>
#include <stan/math/prim/scal/prob/gumbel_cdf_log.hpp>
#include <stan/math/prim/scal/prob/gumbel_log.hpp>
#include <stan/math/prim/scal/prob/gumbel_rng.hpp>
#include <stan/math/prim/scal/prob/hypergeometric_log.hpp>
#include <stan/math/prim/scal/prob/hypergeometric_rng.hpp>
#include <stan/math/prim/scal/prob/inv_chi_square_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/inv_chi_square_cdf.hpp>
#include <stan/math/prim/scal/prob/inv_chi_square_cdf_log.hpp>
#include <stan/math/prim/scal/prob/inv_chi_square_log.hpp>
#include <stan/math/prim/scal/prob/inv_chi_square_rng.hpp>
#include <stan/math/prim/scal/prob/inv_gamma_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/inv_gamma_cdf.hpp>
#include <stan/math/prim/scal/prob/inv_gamma_cdf_log.hpp>
#include <stan/math/prim/scal/prob/inv_gamma_log.hpp>
#include <stan/math/prim/scal/prob/inv_gamma_rng.hpp>
#include <stan/math/prim/scal/prob/logistic_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/logistic_cdf.hpp>
#include <stan/math/prim/scal/prob/logistic_cdf_log.hpp>
#include <stan/math/prim/scal/prob/logistic_log.hpp>
#include <stan/math/prim/scal/prob/logistic_rng.hpp>
#include <stan/math/prim/scal/prob/lognormal_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/lognormal_cdf.hpp>
#include <stan/math/prim/scal/prob/lognormal_cdf_log.hpp>
#include <stan/math/prim/scal/prob/lognormal_log.hpp>
#include <stan/math/prim/scal/prob/lognormal_rng.hpp>
#include <stan/math/prim/scal/prob/neg_binomial_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/neg_binomial_cdf.hpp>
#include <stan/math/prim/scal/prob/neg_binomial_cdf_log.hpp>
#include <stan/math/prim/scal/prob/neg_binomial_log.hpp>
#include <stan/math/prim/scal/prob/neg_binomial_rng.hpp>
#include <stan/math/prim/scal/prob/neg_binomial_2_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/neg_binomial_2_cdf.hpp>
#include <stan/math/prim/scal/prob/neg_binomial_2_cdf_log.hpp>
#include <stan/math/prim/scal/prob/neg_binomial_2_log.hpp>
#include <stan/math/prim/scal/prob/neg_binomial_2_log_log.hpp>
#include <stan/math/prim/scal/prob/neg_binomial_2_log_rng.hpp>
#include <stan/math/prim/scal/prob/neg_binomial_2_rng.hpp>
#include <stan/math/prim/scal/prob/normal_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/normal_cdf.hpp>
#include <stan/math/prim/scal/prob/normal_cdf_log.hpp>
#include <stan/math/prim/scal/prob/normal_log.hpp>
#include <stan/math/prim/scal/prob/normal_rng.hpp>
#include <stan/math/prim/scal/prob/ordered_logistic_log.hpp>
#include <stan/math/prim/scal/prob/ordered_logistic_rng.hpp>
#include <stan/math/prim/scal/prob/pareto_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/pareto_cdf.hpp>
#include <stan/math/prim/scal/prob/pareto_cdf_log.hpp>
#include <stan/math/prim/scal/prob/pareto_log.hpp>
#include <stan/math/prim/scal/prob/pareto_rng.hpp>
#include <stan/math/prim/scal/prob/pareto_type_2_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/pareto_type_2_cdf.hpp>
#include <stan/math/prim/scal/prob/pareto_type_2_cdf_log.hpp>
#include <stan/math/prim/scal/prob/pareto_type_2_log.hpp>
#include <stan/math/prim/scal/prob/pareto_type_2_rng.hpp>
#include <stan/math/prim/scal/prob/poisson_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/poisson_cdf.hpp>
#include <stan/math/prim/scal/prob/poisson_cdf_log.hpp>
#include <stan/math/prim/scal/prob/poisson_log.hpp>
#include <stan/math/prim/scal/prob/poisson_log_log.hpp>
#include <stan/math/prim/scal/prob/poisson_log_rng.hpp>
#include <stan/math/prim/scal/prob/poisson_rng.hpp>
#include <stan/math/prim/scal/prob/rayleigh_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/rayleigh_cdf.hpp>
#include <stan/math/prim/scal/prob/rayleigh_cdf_log.hpp>
#include <stan/math/prim/scal/prob/rayleigh_log.hpp>
#include <stan/math/prim/scal/prob/rayleigh_rng.hpp>
#include <stan/math/prim/scal/prob/scaled_inv_chi_square_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/scaled_inv_chi_square_cdf.hpp>
#include <stan/math/prim/scal/prob/scaled_inv_chi_square_cdf_log.hpp>
#include <stan/math/prim/scal/prob/scaled_inv_chi_square_log.hpp>
#include <stan/math/prim/scal/prob/scaled_inv_chi_square_rng.hpp>
#include <stan/math/prim/scal/prob/skew_normal_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/skew_normal_cdf.hpp>
#include <stan/math/prim/scal/prob/skew_normal_cdf_log.hpp>
#include <stan/math/prim/scal/prob/skew_normal_log.hpp>
#include <stan/math/prim/scal/prob/skew_normal_rng.hpp>
#include <stan/math/prim/scal/prob/student_t.hpp>
#include <stan/math/prim/scal/prob/uniform.hpp>
#include <stan/math/prim/scal/prob/von_mises.hpp>
#include <stan/math/prim/scal/prob/weibull.hpp>
#include <stan/math/rev/arr/functor/coupled_ode_system.hpp>
#include <stan/math/rev/core/autodiffstackstorage.hpp>
#include <stan/math/rev/core/chainable.hpp>
#include <stan/math/rev/core/chainable_alloc.hpp>
#include <stan/math/rev/core/chainablestack.hpp>
#include <stan/math/rev/core/ddv_vari.hpp>
#include <stan/math/rev/core/ddv_vari.hpp>
#include <stan/math/rev/core/dv_vari.hpp>
#include <stan/math/rev/core/dv_vari.hpp>
#include <stan/math/rev/core/dvd_vari.hpp>
#include <stan/math/rev/core/dvd_vari.hpp>
#include <stan/math/rev/core/dvv_vari.hpp>
#include <stan/math/rev/core/dvv_vari.hpp>
#include <stan/math/rev/core/empty_nested.hpp>
#include <stan/math/rev/core/gevv_vvv_vari.hpp>
#include <stan/math/rev/core/grad.hpp>
#include <stan/math/rev/core/matrix_vari.hpp>
#include <stan/math/rev/core/matrix_vari.hpp>
#include <stan/math/rev/core/nested_size.hpp>
#include <stan/math/rev/core/operator_addition.hpp>
#include <stan/math/rev/core/operator_addition.hpp>
#include <stan/math/rev/core/operator_divide_equal.hpp>
#include <stan/math/rev/core/operator_divide_equal.hpp>
#include <stan/math/rev/core/operator_division.hpp>
#include <stan/math/rev/core/operator_division.hpp>
#include <stan/math/rev/core/operator_equal.hpp>
#include <stan/math/rev/core/operator_equal.hpp>
#include <stan/math/rev/core/operator_greater_than.hpp>
#include <stan/math/rev/core/operator_greater_than.hpp>
#include <stan/math/rev/core/operator_greater_than_or_equal.hpp>
#include <stan/math/rev/core/operator_greater_than_or_equal.hpp>
#include <stan/math/rev/core/operator_less_than.hpp>
#include <stan/math/rev/core/operator_less_than.hpp>
#include <stan/math/rev/core/operator_less_than_or_equal.hpp>
#include <stan/math/rev/core/operator_less_than_or_equal.hpp>
#include <stan/math/rev/core/operator_minus_equal.hpp>
#include <stan/math/rev/core/operator_minus_equal.hpp>
#include <stan/math/rev/core/operator_multiplication.hpp>
#include <stan/math/rev/core/operator_multiplication.hpp>
#include <stan/math/rev/core/operator_multiply_equal.hpp>
#include <stan/math/rev/core/operator_multiply_equal.hpp>
#include <stan/math/rev/core/operator_not_equal.hpp>
#include <stan/math/rev/core/operator_not_equal.hpp>
#include <stan/math/rev/core/operator_plus_equal.hpp>
#include <stan/math/rev/core/operator_plus_equal.hpp>
#include <stan/math/rev/core/operator_subtraction.hpp>
#include <stan/math/rev/core/operator_subtraction.hpp>
#include <stan/math/rev/core/operator_unary_decrement.hpp>
#include <stan/math/rev/core/operator_unary_decrement.hpp>
#include <stan/math/rev/core/operator_unary_increment.hpp>
#include <stan/math/rev/core/operator_unary_increment.hpp>
#include <stan/math/rev/core/operator_unary_negative.hpp>
#include <stan/math/rev/core/operator_unary_negative.hpp>
#include <stan/math/rev/core/operator_unary_not.hpp>
#include <stan/math/rev/core/operator_unary_not.hpp>
#include <stan/math/rev/core/operator_unary_plus.hpp>
#include <stan/math/rev/core/operator_unary_plus.hpp>
#include <stan/math/rev/core/precomp_v_vari.hpp>
#include <stan/math/rev/core/precomp_v_vari.hpp>
#include <stan/math/rev/core/precomp_vv_vari.hpp>
#include <stan/math/rev/core/precomp_vv_vari.hpp>
#include <stan/math/rev/core/precomp_vvv_vari.hpp>
#include <stan/math/rev/core/precomp_vvv_vari.hpp>
#include <stan/math/rev/core/precomputed_gradients.hpp>
#include <stan/math/rev/core/precomputed_gradients.hpp>
#include <stan/math/rev/core/print_stack.hpp>
#include <stan/math/rev/core/recover_memory.hpp>
#include <stan/math/rev/core/recover_memory_nested.hpp>
#include <stan/math/rev/core/set_zero_all_adjoints.hpp>
#include <stan/math/rev/core/start_nested.hpp>
#include <stan/math/rev/core/std_isinf.hpp>
#include <stan/math/rev/core/std_isnan.hpp>
#include <stan/math/rev/core/std_numeric_limits.hpp>
#include <stan/math/rev/core/std_numeric_limits.hpp>
#include <stan/math/rev/core/stored_gradient_vari.hpp>
#include <stan/math/rev/core/stored_gradient_vari.hpp>
#include <stan/math/rev/core/v_vari.hpp>
#include <stan/math/rev/core/v_vari.hpp>
#include <stan/math/rev/core/var.hpp>
#include <stan/math/rev/core/vari.hpp>
#include <stan/math/rev/core/vd_vari.hpp>
#include <stan/math/rev/core/vd_vari.hpp>
#include <stan/math/rev/core/vdd_vari.hpp>
#include <stan/math/rev/core/vdd_vari.hpp>
#include <stan/math/rev/core/vdv_vari.hpp>
#include <stan/math/rev/core/vdv_vari.hpp>
#include <stan/math/rev/core/vector_vari.hpp>
#include <stan/math/rev/core/vector_vari.hpp>
#include <stan/math/rev/core/vv_vari.hpp>
#include <stan/math/rev/core/vv_vari.hpp>
#include <stan/math/rev/core/vvd_vari.hpp>
#include <stan/math/rev/core/vvd_vari.hpp>
#include <stan/math/rev/core/vvv_vari.hpp>
#include <stan/math/rev/core/vvv_vari.hpp>
#include <stan/math/rev/mat/err/check_pos_definite.hpp>
#include <stan/math/rev/mat/fun/columns_dot_product.hpp>
#include <stan/math/rev/mat/fun/columns_dot_self.hpp>
#include <stan/math/rev/mat/fun/crossprod.hpp>
#include <stan/math/rev/mat/fun/determinant.hpp>
#include <stan/math/rev/mat/fun/divide.hpp>
#include <stan/math/rev/mat/fun/dot_product.hpp>
#include <stan/math/rev/mat/fun/dot_self.hpp>
#include <stan/math/rev/mat/fun/Eigen_NumTraits.hpp>
#include <stan/math/rev/mat/fun/grad.hpp>
#include <stan/math/rev/mat/fun/initialize_variable.hpp>
#include <stan/math/rev/mat/fun/LDLT_alloc.hpp>
#include <stan/math/rev/mat/fun/LDLT_factor.hpp>
#include <stan/math/rev/mat/fun/log_determinant.hpp>
#include <stan/math/rev/mat/fun/log_determinant_ldlt.hpp>
#include <stan/math/rev/mat/fun/log_determinant_spd.hpp>
#include <stan/math/rev/mat/fun/log_softmax.hpp>
#include <stan/math/rev/mat/fun/log_sum_exp.hpp>
#include <stan/math/rev/mat/fun/mdivide_left.hpp>
#include <stan/math/rev/mat/fun/mdivide_left_ldlt.hpp>
#include <stan/math/rev/mat/fun/mdivide_left_spd.hpp>
#include <stan/math/rev/mat/fun/mdivide_left_tri.hpp>
#include <stan/math/rev/mat/fun/multiply.hpp>
#include <stan/math/rev/mat/fun/multiply_lower_tri_self_transpose.hpp>
#include <stan/math/rev/mat/fun/quad_form.hpp>
#include <stan/math/rev/mat/fun/quad_form_sym.hpp>
#include <stan/math/rev/mat/fun/rows_dot_product.hpp>
#include <stan/math/rev/mat/fun/sd.hpp>
#include <stan/math/rev/mat/fun/softmax.hpp>
#include <stan/math/rev/mat/fun/sort_asc.hpp>
#include <stan/math/rev/mat/fun/sort_desc.hpp>
#include <stan/math/rev/mat/fun/squared_distance.hpp>
#include <stan/math/rev/mat/fun/stan_print.hpp>
#include <stan/math/rev/mat/fun/sum.hpp>
#include <stan/math/rev/mat/fun/tcrossprod.hpp>
#include <stan/math/rev/mat/fun/to_var.hpp>
#include <stan/math/rev/mat/fun/trace_gen_inv_quad_form_ldlt.hpp>
#include <stan/math/rev/mat/fun/trace_gen_quad_form.hpp>
#include <stan/math/rev/mat/fun/trace_inv_quad_form_ldlt.hpp>
#include <stan/math/rev/mat/fun/trace_quad_form.hpp>
#include <stan/math/rev/mat/fun/typedefs.hpp>
#include <stan/math/rev/mat/fun/variance.hpp>
#include <stan/math/rev/scal/fun/abs.hpp>
#include <stan/math/rev/scal/fun/acos.hpp>
#include <stan/math/rev/scal/fun/acosh.hpp>
#include <stan/math/rev/scal/fun/as_bool.hpp>
#include <stan/math/rev/scal/fun/asin.hpp>
#include <stan/math/rev/scal/fun/asinh.hpp>
#include <stan/math/rev/scal/fun/atan.hpp>
#include <stan/math/rev/scal/fun/atan2.hpp>
#include <stan/math/rev/scal/fun/atanh.hpp>
#include <stan/math/rev/scal/fun/bessel_first_kind.hpp>
#include <stan/math/rev/scal/fun/bessel_second_kind.hpp>
#include <stan/math/rev/scal/fun/binary_log_loss.hpp>
#include <stan/math/rev/scal/fun/boost_fpclassify.hpp>
#include <stan/math/rev/scal/fun/boost_isfinite.hpp>
#include <stan/math/rev/scal/fun/boost_isinf.hpp>
#include <stan/math/rev/scal/fun/boost_isnan.hpp>
#include <stan/math/rev/scal/fun/boost_isnormal.hpp>
#include <stan/math/rev/scal/fun/calculate_chain.hpp>
#include <stan/math/rev/scal/fun/cbrt.hpp>
#include <stan/math/rev/scal/fun/ceil.hpp>
#include <stan/math/rev/scal/fun/cos.hpp>
#include <stan/math/rev/scal/fun/cosh.hpp>
#include <stan/math/rev/scal/fun/digamma.hpp>
#include <stan/math/rev/scal/fun/erf.hpp>
#include <stan/math/rev/scal/fun/erfc.hpp>
#include <stan/math/rev/scal/fun/exp.hpp>
#include <stan/math/rev/scal/fun/exp2.hpp>
#include <stan/math/rev/scal/fun/expm1.hpp>
#include <stan/math/rev/scal/fun/fabs.hpp>
#include <stan/math/rev/scal/fun/falling_factorial.hpp>
#include <stan/math/rev/scal/fun/fdim.hpp>
#include <stan/math/rev/scal/fun/floor.hpp>
#include <stan/math/rev/scal/fun/fma.hpp>
#include <stan/math/rev/scal/fun/fmax.hpp>
#include <stan/math/rev/scal/fun/fmin.hpp>
#include <stan/math/rev/scal/fun/fmod.hpp>
#include <stan/math/rev/scal/fun/gamma_p.hpp>
#include <stan/math/rev/scal/fun/gamma_q.hpp>
#include <stan/math/rev/scal/fun/grad_inc_beta.hpp>
#include <stan/math/rev/scal/fun/hypot.hpp>
#include <stan/math/rev/scal/fun/ibeta.hpp>
#include <stan/math/rev/scal/fun/if_else.hpp>
#include <stan/math/rev/scal/fun/inc_beta.hpp>
#include <stan/math/rev/scal/fun/inv.hpp>
#include <stan/math/rev/scal/fun/inv_cloglog.hpp>
#include <stan/math/rev/scal/fun/inv_logit.hpp>
#include <stan/math/rev/scal/fun/inv_sqrt.hpp>
#include <stan/math/rev/scal/fun/inv_square.hpp>
#include <stan/math/rev/scal/fun/is_inf.hpp>
#include <stan/math/rev/scal/fun/is_nan.hpp>
#include <stan/math/rev/scal/fun/is_uninitialized.hpp>
#include <stan/math/rev/scal/fun/lgamma.hpp>
#include <stan/math/rev/scal/fun/lmgamma.hpp>
#include <stan/math/rev/scal/fun/log.hpp>
#include <stan/math/rev/scal/fun/log10.hpp>
#include <stan/math/rev/scal/fun/log1m.hpp>
#include <stan/math/rev/scal/fun/log1m_exp.hpp>
#include <stan/math/rev/scal/fun/log1p.hpp>
#include <stan/math/rev/scal/fun/log1p_exp.hpp>
#include <stan/math/rev/scal/fun/log2.hpp>
#include <stan/math/rev/scal/fun/log_diff_exp.hpp>
#include <stan/math/rev/scal/fun/log_falling_factorial.hpp>
#include <stan/math/rev/scal/fun/log_mix.hpp>
#include <stan/math/rev/scal/fun/log_rising_factorial.hpp>
#include <stan/math/rev/scal/fun/log_sum_exp.hpp>
#include <stan/math/rev/scal/fun/modified_bessel_first_kind.hpp>
#include <stan/math/rev/scal/fun/modified_bessel_second_kind.hpp>
#include <stan/math/rev/scal/fun/multiply_log.hpp>
#include <stan/math/rev/scal/fun/owens_t.hpp>
#include <stan/math/rev/scal/fun/Phi.hpp>
#include <stan/math/rev/scal/fun/Phi_approx.hpp>
#include <stan/math/rev/scal/fun/pow.hpp>
#include <stan/math/rev/scal/fun/primitive_value.hpp>
#include <stan/math/rev/scal/fun/rising_factorial.hpp>
#include <stan/math/rev/scal/fun/round.hpp>
#include <stan/math/rev/scal/fun/sin.hpp>
#include <stan/math/rev/scal/fun/sinh.hpp>
#include <stan/math/rev/scal/fun/sqrt.hpp>
#include <stan/math/rev/scal/fun/square.hpp>
#include <stan/math/rev/scal/fun/step.hpp>
#include <stan/math/rev/scal/fun/tan.hpp>
#include <stan/math/rev/scal/fun/tanh.hpp>
#include <stan/math/rev/scal/fun/tgamma.hpp>
#include <stan/math/rev/scal/fun/trunc.hpp>
#include <stan/math/rev/scal/fun/value_of.hpp>
#include <stan/math/rev/scal/fun/value_of_rec.hpp>

#include <stan/model/prob_grad.hpp>
#include <stan/services/command.hpp>

#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>

#endif
