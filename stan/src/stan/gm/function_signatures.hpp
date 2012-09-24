// included from constructor for function_signatures() in src/stan/gm/ast.hpp

std::vector<expr_type> vector_types;
vector_types.push_back(DOUBLE_T);                  // scalar
vector_types.push_back(expr_type(DOUBLE_T,1U));    // std vector
vector_types.push_back(VECTOR_T);                  // Eigen vector
vector_types.push_back(ROW_VECTOR_T);              // Eigen row vector


add_unary("abs");
add("abs",INT_T,INT_T);
add_unary("acos");
add_unary("acosh");
add("add",VECTOR_T,VECTOR_T,VECTOR_T);
add("add",ROW_VECTOR_T,ROW_VECTOR_T,ROW_VECTOR_T);
add("add",MATRIX_T,MATRIX_T,MATRIX_T);
add("add",VECTOR_T,VECTOR_T,DOUBLE_T);
add("add",ROW_VECTOR_T,ROW_VECTOR_T,DOUBLE_T);
add("add",MATRIX_T,MATRIX_T,DOUBLE_T);
add("add",VECTOR_T,DOUBLE_T,VECTOR_T);
add("add",ROW_VECTOR_T,DOUBLE_T,ROW_VECTOR_T);
add("add",MATRIX_T,DOUBLE_T,MATRIX_T);
add_unary("asin");
add_unary("asinh");
add_unary("atan");
add_binary("atan2");
add_unary("atanh");
for (size_t i = 0; i < vector_types.size(); ++i) {
  add("bernoulli_log",DOUBLE_T,INT_T,vector_types[i]);
  add("bernoulli_log",DOUBLE_T,expr_type(INT_T,1U),vector_types[i]);
}
for (size_t i = 0; i < vector_types.size(); ++i) {
  add("bernoulli_logit_log",DOUBLE_T,INT_T,vector_types[i]);
  add("bernoulli_logit_log",DOUBLE_T,expr_type(INT_T,1U),vector_types[i]);
}
add("beta_binomial_log",DOUBLE_T,INT_T,INT_T,DOUBLE_T,DOUBLE_T);
for (size_t i = 0; i < vector_types.size(); ++i)
  for (size_t j = 0; j < vector_types.size(); ++j)
    for (size_t k = 0; k < vector_types.size(); ++k)
      add("beta_log",
          DOUBLE_T, // result
          vector_types[i], vector_types[j], vector_types[k]); // args
add("binary_log_loss",DOUBLE_T,INT_T,DOUBLE_T);
add_binary("binomial_coefficient_log");
add("binomial_log",DOUBLE_T,INT_T,INT_T,DOUBLE_T);
add("categorical_log",DOUBLE_T,INT_T,VECTOR_T);
for (size_t i = 0; i < vector_types.size(); ++i)
  for (size_t j = 0; j < vector_types.size(); ++j)
    for (size_t k = 0; k < vector_types.size(); ++k)
      add("cauchy_log",
          DOUBLE_T, // result
          vector_types[i], vector_types[j], vector_types[k]); // args
add_unary("cbrt");
add_unary("ceil");
add("cholesky_decompose",MATRIX_T,MATRIX_T);
add_binary("chi_square_log");
add("col",VECTOR_T,MATRIX_T,INT_T);
add("cols",INT_T,VECTOR_T);
add("cols",INT_T,ROW_VECTOR_T);
add("cols",INT_T,MATRIX_T);
add_unary("cos");
add_unary("cosh");
add("determinant",DOUBLE_T,MATRIX_T);
add("diagonal",VECTOR_T,MATRIX_T);
add("diag_matrix",MATRIX_T,VECTOR_T);
add("dirichlet_log",DOUBLE_T,VECTOR_T,VECTOR_T);
add("divide",DOUBLE_T,DOUBLE_T,DOUBLE_T);
add("divide",VECTOR_T,VECTOR_T,DOUBLE_T);
add("divide",ROW_VECTOR_T,ROW_VECTOR_T,DOUBLE_T);
add("divide",MATRIX_T,MATRIX_T,DOUBLE_T);
add("dot_product",DOUBLE_T,VECTOR_T,VECTOR_T);
add("dot_product",DOUBLE_T,ROW_VECTOR_T,ROW_VECTOR_T);
add("dot_product",DOUBLE_T,VECTOR_T,ROW_VECTOR_T);
add("dot_product",DOUBLE_T,ROW_VECTOR_T,VECTOR_T);
add("dot_product",DOUBLE_T,expr_type(DOUBLE_T,1U),expr_type(DOUBLE_T,1U)); // vectorized
add("dot_self",DOUBLE_T,VECTOR_T);
add("dot_self",DOUBLE_T,ROW_VECTOR_T);
for (size_t i = 0; i < vector_types.size(); ++i)
  for (size_t j = 0; j < vector_types.size(); ++j)
    for (size_t k = 0; k < vector_types.size(); ++k)
      add("double_exponential_log",
          DOUBLE_T, // result
          vector_types[i], vector_types[j], vector_types[k]); // args
add_nullary("e");
add("eigenvalues",VECTOR_T,MATRIX_T);
add("eigenvalues_sym",VECTOR_T,MATRIX_T);
add("eigenvectors",MATRIX_T,MATRIX_T);
add("eigenvectors_sym",MATRIX_T,MATRIX_T);
add("elt_divide",VECTOR_T,VECTOR_T,VECTOR_T);
add("elt_divide",ROW_VECTOR_T,ROW_VECTOR_T,ROW_VECTOR_T);
add("elt_divide",MATRIX_T,MATRIX_T,MATRIX_T);
add("elt_multiply",VECTOR_T,VECTOR_T,VECTOR_T);
add("elt_multiply",ROW_VECTOR_T,ROW_VECTOR_T,ROW_VECTOR_T);
add("elt_multiply",MATRIX_T,MATRIX_T,MATRIX_T);
add_nullary("epsilon");
add_unary("erf");
add_unary("erfc");
add_unary("exp");
add("exp",VECTOR_T,VECTOR_T);
add("exp",ROW_VECTOR_T,ROW_VECTOR_T);
add("exp",MATRIX_T,MATRIX_T);
add_unary("exp2");
add_unary("expm1");
add_binary("exponential_log");
add_binary("exponential_cdf");
add_unary("fabs");
add_binary("fdim");
add_unary("floor");
add_ternary("fma");
add_binary("fmax");
add_binary("fmin");
add_binary("fmod");
for (size_t i = 0; i < vector_types.size(); ++i)
  for (size_t j = 0; j < vector_types.size(); ++j)
    for (size_t k = 0; k < vector_types.size(); ++k)
      add("gamma_log",
          DOUBLE_T, // result
          vector_types[i], vector_types[j], vector_types[k]); // args
//FIXME: add_ternary("gamma_cdf");
add("hypergeometric_log",DOUBLE_T, INT_T, INT_T, INT_T, INT_T);
add_binary("hypot");
add("if_else",DOUBLE_T,INT_T,DOUBLE_T,DOUBLE_T);
add("int_step",INT_T,DOUBLE_T);
add("int_step",INT_T,INT_T);
add_binary("inv_chi_square_log");
add_unary("inv_cloglog");
for (size_t i = 0; i < vector_types.size(); ++i)
  for (size_t j = 0; j < vector_types.size(); ++j)
    for (size_t k = 0; k < vector_types.size(); ++k)
      add("inv_gamma_log",
          DOUBLE_T, // result
          vector_types[i], vector_types[j], vector_types[k]); // args
add_unary("inv_logit");
add("inv_wishart_log",DOUBLE_T, MATRIX_T,DOUBLE_T,MATRIX_T);
add("inverse",MATRIX_T,MATRIX_T);
add_binary("lbeta");
add_unary("lgamma");
add("lkj_corr_cholesky_log",DOUBLE_T, MATRIX_T,DOUBLE_T);
add("lkj_corr_log",DOUBLE_T, MATRIX_T,DOUBLE_T);
add("lkj_cov_log",DOUBLE_T, MATRIX_T,VECTOR_T,VECTOR_T,DOUBLE_T);
add("lmgamma",DOUBLE_T,INT_T,DOUBLE_T);
add_unary("log");
add("log",VECTOR_T,VECTOR_T);
add("log",ROW_VECTOR_T,ROW_VECTOR_T);
add("log",MATRIX_T,MATRIX_T);
add("log_sum_exp",DOUBLE_T, expr_type(DOUBLE_T,1U));
add_binary("log_sum_exp");
add_nullary("log10");
add_unary("log10");
add_unary("log1m");
add_unary("log1p");
add_unary("log1p_exp");
add_nullary("log2");
add_unary("log2");
add_ternary("logistic_log");
add_unary("logit");
add_ternary("lognormal_cdf");
add_ternary("lognormal_log");
add("max",INT_T,expr_type(INT_T,1));
add("max",DOUBLE_T,expr_type(DOUBLE_T,1));
add("max",DOUBLE_T,VECTOR_T);
add("max",DOUBLE_T,ROW_VECTOR_T);
add("max",DOUBLE_T,MATRIX_T);
add("max",INT_T,INT_T,INT_T);
add("mdivide_left",VECTOR_T,MATRIX_T,VECTOR_T);
add("mdivide_left",MATRIX_T,MATRIX_T,MATRIX_T);
add("mdivide_right",ROW_VECTOR_T,ROW_VECTOR_T,MATRIX_T);
add("mdivide_right",MATRIX_T,MATRIX_T,MATRIX_T);
add("mean",DOUBLE_T,expr_type(DOUBLE_T,1));
add("mean",DOUBLE_T,VECTOR_T);
add("mean",DOUBLE_T,ROW_VECTOR_T);
add("mean",DOUBLE_T,MATRIX_T);
add("min",INT_T,expr_type(INT_T,1));
add("min",DOUBLE_T,expr_type(DOUBLE_T,1));
add("min",DOUBLE_T,VECTOR_T);
add("min",DOUBLE_T,ROW_VECTOR_T);
add("min",DOUBLE_T,MATRIX_T);
add("min",INT_T,INT_T,INT_T);
add("minus",DOUBLE_T,DOUBLE_T);
add("minus",VECTOR_T,VECTOR_T);
add("minus",ROW_VECTOR_T,ROW_VECTOR_T);
add("minus",MATRIX_T,MATRIX_T);
add("multi_normal_cholesky_log",DOUBLE_T, VECTOR_T,VECTOR_T,MATRIX_T);
add("multi_normal_log",DOUBLE_T, VECTOR_T,VECTOR_T,MATRIX_T);
add("multi_student_t_log",DOUBLE_T, VECTOR_T,DOUBLE_T,VECTOR_T,MATRIX_T);
add("multinomial_log",DOUBLE_T, expr_type(INT_T,1U), VECTOR_T);
add("multiply",DOUBLE_T,DOUBLE_T,DOUBLE_T);
add("multiply",VECTOR_T,VECTOR_T,DOUBLE_T);
add("multiply",ROW_VECTOR_T,ROW_VECTOR_T,DOUBLE_T);
add("multiply",MATRIX_T,MATRIX_T,DOUBLE_T);
add("multiply",DOUBLE_T,ROW_VECTOR_T,VECTOR_T);
add("multiply",MATRIX_T,VECTOR_T,ROW_VECTOR_T);  
add("multiply",VECTOR_T,MATRIX_T,VECTOR_T);
add("multiply",ROW_VECTOR_T,ROW_VECTOR_T,MATRIX_T);
add("multiply",MATRIX_T,MATRIX_T,MATRIX_T);
add("multiply",VECTOR_T,DOUBLE_T,VECTOR_T);
add("multiply",ROW_VECTOR_T,DOUBLE_T,ROW_VECTOR_T);
add("multiply",MATRIX_T,DOUBLE_T,MATRIX_T);
add_binary("multiply_log");
add("neg_binomial_log",DOUBLE_T, INT_T,DOUBLE_T,DOUBLE_T);
add_nullary("negative_epsilon");
add_nullary("negative_infinity");
add("normal_cdf",DOUBLE_T, DOUBLE_T,DOUBLE_T,DOUBLE_T);
for (size_t i = 0; i < vector_types.size(); ++i)
  for (size_t j = 0; j < vector_types.size(); ++j)
    for (size_t k = 0; k < vector_types.size(); ++k)
      add("normal_log",
          DOUBLE_T, // result
          vector_types[i], vector_types[j], vector_types[k]); // args
add_nullary("not_a_number");
add("ordered_logistic_log",DOUBLE_T,INT_T,DOUBLE_T,VECTOR_T);
add_ternary("pareto_log");
add_unary("Phi");
add_nullary("pi");
add("poisson_log",DOUBLE_T, INT_T,DOUBLE_T);
add_nullary("positive_infinity");
add_binary("pow");

add("prod",INT_T,expr_type(INT_T,1));
add("prod",DOUBLE_T,expr_type(DOUBLE_T,1));
add("prod",DOUBLE_T,VECTOR_T);
add("prod",DOUBLE_T,ROW_VECTOR_T);
add("prod",DOUBLE_T,MATRIX_T);
add_unary("round");
add("row",ROW_VECTOR_T,MATRIX_T,INT_T);
add("rows",INT_T,VECTOR_T);
add("rows",INT_T,ROW_VECTOR_T);
add("rows",INT_T,MATRIX_T);
add_ternary("scaled_inv_chi_square_log");
add("sd",DOUBLE_T,expr_type(DOUBLE_T,1));
add("sd",DOUBLE_T,VECTOR_T);
add("sd",DOUBLE_T,ROW_VECTOR_T);
add("sd",DOUBLE_T,MATRIX_T);
add_unary("sin");
add("singular_values",VECTOR_T,MATRIX_T);
add_unary("sinh");
add("softmax",VECTOR_T,VECTOR_T);
add_unary("sqrt");
add_nullary("sqrt2");
add_unary("square");
add_unary("step");
add_quaternary("student_t_log");
add("subtract",VECTOR_T,VECTOR_T,VECTOR_T);
add("subtract",ROW_VECTOR_T,ROW_VECTOR_T,ROW_VECTOR_T);
add("subtract",MATRIX_T,MATRIX_T,MATRIX_T);
add("subtract",VECTOR_T,VECTOR_T,DOUBLE_T);
add("subtract",ROW_VECTOR_T,ROW_VECTOR_T,DOUBLE_T);
add("subtract",MATRIX_T,MATRIX_T,DOUBLE_T);
add("subtract",VECTOR_T,DOUBLE_T,VECTOR_T);
add("subtract",ROW_VECTOR_T,DOUBLE_T,ROW_VECTOR_T);
add("subtract",MATRIX_T,DOUBLE_T,MATRIX_T);
add("sum",INT_T,expr_type(INT_T,1));
add("sum",DOUBLE_T,expr_type(DOUBLE_T,1));
add("sum",DOUBLE_T,VECTOR_T);
add("sum",DOUBLE_T,ROW_VECTOR_T);
add("sum",DOUBLE_T,MATRIX_T);
add_unary("tan");
add_unary("tanh");
add_unary("tgamma");
add("trace",DOUBLE_T,MATRIX_T);
add("transpose",ROW_VECTOR_T,VECTOR_T);
add("transpose",VECTOR_T,ROW_VECTOR_T);
add("transpose",MATRIX_T,MATRIX_T);
add_unary("trunc");
add_ternary("uniform_log");
add("variance",DOUBLE_T,expr_type(DOUBLE_T,1));
add("variance",DOUBLE_T,VECTOR_T);
add("variance",DOUBLE_T,ROW_VECTOR_T);
add("variance",DOUBLE_T,MATRIX_T);
add_ternary("weibull_log");
add_ternary("weibull_cdf");
add("wishart_log",DOUBLE_T, MATRIX_T,DOUBLE_T,MATRIX_T);

//------------------------------------------------------------

add("trunc_normal_log",DOUBLE_T, DOUBLE_T,DOUBLE_T,DOUBLE_T,DOUBLE_T,DOUBLE_T);
