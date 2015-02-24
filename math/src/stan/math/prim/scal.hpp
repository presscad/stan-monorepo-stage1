#ifndef STAN__MATH__PRIM__SCAL_HPP
#define STAN__MATH__PRIM__SCAL_HPP

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
#include <stan/math/prim/scal/err/check_nonzero_size.hpp>
#include <stan/math/prim/scal/err/check_not_nan.hpp>
#include <stan/math/prim/scal/err/check_positive.hpp>
#include <stan/math/prim/scal/err/check_positive_finite.hpp>
#include <stan/math/prim/scal/err/check_positive_size.hpp>
#include <stan/math/prim/scal/err/check_size_match.hpp>
#include <stan/math/prim/scal/err/domain_error.hpp>
#include <stan/math/prim/scal/err/invalid_argument.hpp>
#include <stan/math/prim/scal/err/out_of_range.hpp>
#include <stan/math/prim/scal/fun/F32.hpp>
#include <stan/math/prim/scal/fun/Phi.hpp>
#include <stan/math/prim/scal/fun/Phi_approx.hpp>
#include <stan/math/prim/scal/fun/abs.hpp>
#include <stan/math/prim/scal/fun/as_bool.hpp>
#include <stan/math/prim/scal/fun/bessel_first_kind.hpp>
#include <stan/math/prim/scal/fun/bessel_second_kind.hpp>
#include <stan/math/prim/scal/fun/binary_log_loss.hpp>
#include <stan/math/prim/scal/fun/binomial_coefficient_log.hpp>
#include <stan/math/prim/scal/fun/constants.hpp>
#include <stan/math/prim/scal/fun/corr_constrain.hpp>
#include <stan/math/prim/scal/fun/corr_free.hpp>
#include <stan/math/prim/scal/fun/digamma.hpp>
#include <stan/math/prim/scal/fun/divide.hpp>
#include <stan/math/prim/scal/fun/exp2.hpp>
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
#include <stan/math/prim/scal/fun/identity_constrain.hpp>
#include <stan/math/prim/scal/fun/identity_free.hpp>
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
#include <stan/math/prim/scal/fun/lb_constrain.hpp>
#include <stan/math/prim/scal/fun/lb_free.hpp>
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
#include <stan/math/prim/scal/fun/lub_constrain.hpp>
#include <stan/math/prim/scal/fun/lub_free.hpp>
#include <stan/math/prim/scal/fun/make_nu.hpp>
#include <stan/math/prim/scal/fun/max.hpp>
#include <stan/math/prim/scal/fun/min.hpp>
#include <stan/math/prim/scal/fun/modified_bessel_first_kind.hpp>
#include <stan/math/prim/scal/fun/modified_bessel_second_kind.hpp>
#include <stan/math/prim/scal/fun/modulus.hpp>
#include <stan/math/prim/scal/fun/multiply_log.hpp>
#include <stan/math/prim/scal/fun/owens_t.hpp>
#include <stan/math/prim/scal/fun/positive_constrain.hpp>
#include <stan/math/prim/scal/fun/positive_free.hpp>
#include <stan/math/prim/scal/fun/primitive_value.hpp>
#include <stan/math/prim/scal/fun/prob_constrain.hpp>
#include <stan/math/prim/scal/fun/prob_free.hpp>
#include <stan/math/prim/scal/fun/promote_scalar.hpp>
#include <stan/math/prim/scal/fun/promote_scalar_type.hpp>
#include <stan/math/prim/scal/fun/rising_factorial.hpp>
#include <stan/math/prim/scal/fun/sign.hpp>
#include <stan/math/prim/scal/fun/square.hpp>
#include <stan/math/prim/scal/fun/step.hpp>
#include <stan/math/prim/scal/fun/trigamma.hpp>
#include <stan/math/prim/scal/fun/ub_constrain.hpp>
#include <stan/math/prim/scal/fun/ub_free.hpp>
#include <stan/math/prim/scal/fun/value_of.hpp>
#include <stan/math/prim/scal/fun/value_of_rec.hpp>
#include <stan/math/prim/scal/meta/OperandsAndPartials.hpp>
#include <stan/math/prim/scal/meta/VectorBuilder.hpp>
#include <stan/math/prim/scal/meta/VectorView.hpp>
#include <stan/math/prim/scal/meta/VectorViewMvt.hpp>
#include <stan/math/prim/scal/meta/child_type.hpp>
#include <stan/math/prim/scal/meta/constants.hpp>
#include <stan/math/prim/scal/meta/contains_fvar.hpp>
#include <stan/math/prim/scal/meta/contains_nonconstant_struct.hpp>
#include <stan/math/prim/scal/meta/contains_vector.hpp>
#include <stan/math/prim/scal/meta/error_index.hpp>
#include <stan/math/prim/scal/meta/get.hpp>
#include <stan/math/prim/scal/meta/include_summand.hpp>
#include <stan/math/prim/scal/meta/index_type.hpp>
#include <stan/math/prim/scal/meta/is_constant.hpp>
#include <stan/math/prim/scal/meta/is_constant_struct.hpp>
#include <stan/math/prim/scal/meta/is_fvar.hpp>
#include <stan/math/prim/scal/meta/is_var.hpp>
#include <stan/math/prim/scal/meta/is_var_or_arithmetic.hpp>
#include <stan/math/prim/scal/meta/is_vector.hpp>
#include <stan/math/prim/scal/meta/is_vector_like.hpp>
#include <stan/math/prim/scal/meta/length.hpp>
#include <stan/math/prim/scal/meta/length_mvt.hpp>
#include <stan/math/prim/scal/meta/likely.hpp>
#include <stan/math/prim/scal/meta/max_size.hpp>
#include <stan/math/prim/scal/meta/max_size_mvt.hpp>
#include <stan/math/prim/scal/meta/partials_return_type.hpp>
#include <stan/math/prim/scal/meta/partials_type.hpp>
#include <stan/math/prim/scal/meta/return_type.hpp>
#include <stan/math/prim/scal/meta/scalar_type.hpp>
#include <stan/math/prim/scal/meta/scalar_type_pre.hpp>
#include <stan/math/prim/scal/meta/size_of.hpp>
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
#include <stan/math/prim/scal/prob/neg_binomial_2_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/neg_binomial_2_cdf.hpp>
#include <stan/math/prim/scal/prob/neg_binomial_2_cdf_log.hpp>
#include <stan/math/prim/scal/prob/neg_binomial_2_log.hpp>
#include <stan/math/prim/scal/prob/neg_binomial_2_log_log.hpp>
#include <stan/math/prim/scal/prob/neg_binomial_2_log_rng.hpp>
#include <stan/math/prim/scal/prob/neg_binomial_2_rng.hpp>
#include <stan/math/prim/scal/prob/neg_binomial_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/neg_binomial_cdf.hpp>
#include <stan/math/prim/scal/prob/neg_binomial_cdf_log.hpp>
#include <stan/math/prim/scal/prob/neg_binomial_log.hpp>
#include <stan/math/prim/scal/prob/neg_binomial_rng.hpp>
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
#include <stan/math/prim/scal/prob/student_t_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/student_t_cdf.hpp>
#include <stan/math/prim/scal/prob/student_t_cdf_log.hpp>
#include <stan/math/prim/scal/prob/student_t_log.hpp>
#include <stan/math/prim/scal/prob/student_t_rng.hpp>
#include <stan/math/prim/scal/prob/uniform_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/uniform_cdf.hpp>
#include <stan/math/prim/scal/prob/uniform_cdf_log.hpp>
#include <stan/math/prim/scal/prob/uniform_log.hpp>
#include <stan/math/prim/scal/prob/uniform_rng.hpp>
#include <stan/math/prim/scal/prob/von_mises_log.hpp>
#include <stan/math/prim/scal/prob/von_mises_rng.hpp>
#include <stan/math/prim/scal/prob/weibull_ccdf_log.hpp>
#include <stan/math/prim/scal/prob/weibull_cdf.hpp>
#include <stan/math/prim/scal/prob/weibull_cdf_log.hpp>
#include <stan/math/prim/scal/prob/weibull_log.hpp>
#include <stan/math/prim/scal/prob/weibull_rng.hpp>

#endif
