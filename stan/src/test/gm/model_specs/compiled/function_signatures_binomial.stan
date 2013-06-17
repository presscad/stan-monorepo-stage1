data { 
  int d_int;
  int d_int_array[d_int];
  real d_real;
  real d_real_array[d_int];
  matrix[d_int,d_int] d_matrix;
  vector[d_int] d_vector;
  row_vector[d_int] d_row_vector;
}
transformed data {
  int transformed_data_int;
  real transformed_data_real;
  real transformed_data_real_array[d_int];
  matrix[d_int,d_int] transformed_data_matrix;
  vector[d_int] transformed_data_vector;
  row_vector[d_int] transformed_data_row_vector;

  //*** Discrete Probabilities ***
  // Bounded Discrete Probabilities
  transformed_data_real <- binomial_log(d_int, d_int, d_real);
  transformed_data_real <- binomial_log(d_int, d_int, d_vector);
  transformed_data_real <- binomial_log(d_int, d_int, d_row_vector);
  transformed_data_real <- binomial_log(d_int, d_int, d_real_array);
  transformed_data_real <- binomial_log(d_int, d_int_array, d_real);
  transformed_data_real <- binomial_log(d_int, d_int_array, d_vector);
  transformed_data_real <- binomial_log(d_int, d_int_array, d_row_vector);
  transformed_data_real <- binomial_log(d_int, d_int_array, d_real_array);
  transformed_data_real <- binomial_log(d_int_array, d_int, d_real);
  transformed_data_real <- binomial_log(d_int_array, d_int, d_vector);
  transformed_data_real <- binomial_log(d_int_array, d_int, d_row_vector);
  transformed_data_real <- binomial_log(d_int_array, d_int, d_real_array);
  transformed_data_real <- binomial_log(d_int_array, d_int_array, d_real);
  transformed_data_real <- binomial_log(d_int_array, d_int_array, d_vector);
  transformed_data_real <- binomial_log(d_int_array, d_int_array, d_row_vector);
  transformed_data_real <- binomial_log(d_int_array, d_int_array, d_real_array);
  transformed_data_real <- binomial_cdf(d_int, d_int, d_real);
  transformed_data_real <- binomial_cdf(d_int, d_int, d_vector);
  transformed_data_real <- binomial_cdf(d_int, d_int, d_row_vector);
  transformed_data_real <- binomial_cdf(d_int, d_int, d_real_array);
  transformed_data_real <- binomial_cdf(d_int, d_int_array, d_real);
  transformed_data_real <- binomial_cdf(d_int, d_int_array, d_vector);
  transformed_data_real <- binomial_cdf(d_int, d_int_array, d_row_vector);
  transformed_data_real <- binomial_cdf(d_int, d_int_array, d_real_array);
  transformed_data_real <- binomial_cdf(d_int_array, d_int, d_real);
  transformed_data_real <- binomial_cdf(d_int_array, d_int, d_vector);
  transformed_data_real <- binomial_cdf(d_int_array, d_int, d_row_vector);
  transformed_data_real <- binomial_cdf(d_int_array, d_int, d_real_array);
  transformed_data_real <- binomial_cdf(d_int_array, d_int_array, d_real);
  transformed_data_real <- binomial_cdf(d_int_array, d_int_array, d_vector);
  transformed_data_real <- binomial_cdf(d_int_array, d_int_array, d_row_vector);
  transformed_data_real <- binomial_cdf(d_int_array, d_int_array, d_real_array);
  transformed_data_real <- binomial_cdf_log(d_int, d_int, d_real);
  transformed_data_real <- binomial_cdf_log(d_int, d_int, d_vector);
  transformed_data_real <- binomial_cdf_log(d_int, d_int, d_row_vector);
  transformed_data_real <- binomial_cdf_log(d_int, d_int, d_real_array);
  transformed_data_real <- binomial_cdf_log(d_int, d_int_array, d_real);
  transformed_data_real <- binomial_cdf_log(d_int, d_int_array, d_vector);
  transformed_data_real <- binomial_cdf_log(d_int, d_int_array, d_row_vector);
  transformed_data_real <- binomial_cdf_log(d_int, d_int_array, d_real_array);
  transformed_data_real <- binomial_cdf_log(d_int_array, d_int, d_real);
  transformed_data_real <- binomial_cdf_log(d_int_array, d_int, d_vector);
  transformed_data_real <- binomial_cdf_log(d_int_array, d_int, d_row_vector);
  transformed_data_real <- binomial_cdf_log(d_int_array, d_int, d_real_array);
  transformed_data_real <- binomial_cdf_log(d_int_array, d_int_array, d_real);
  transformed_data_real <- binomial_cdf_log(d_int_array, d_int_array, d_vector);
  transformed_data_real <- binomial_cdf_log(d_int_array, d_int_array, d_row_vector);
  transformed_data_real <- binomial_cdf_log(d_int_array, d_int_array, d_real_array);
  transformed_data_real <- binomial_ccdf_log(d_int, d_int, d_real);
  transformed_data_real <- binomial_ccdf_log(d_int, d_int, d_vector);
  transformed_data_real <- binomial_ccdf_log(d_int, d_int, d_row_vector);
  transformed_data_real <- binomial_ccdf_log(d_int, d_int, d_real_array);
  transformed_data_real <- binomial_ccdf_log(d_int, d_int_array, d_real);
  transformed_data_real <- binomial_ccdf_log(d_int, d_int_array, d_vector);
  transformed_data_real <- binomial_ccdf_log(d_int, d_int_array, d_row_vector);
  transformed_data_real <- binomial_ccdf_log(d_int, d_int_array, d_real_array);
  transformed_data_real <- binomial_ccdf_log(d_int_array, d_int, d_real);
  transformed_data_real <- binomial_ccdf_log(d_int_array, d_int, d_vector);
  transformed_data_real <- binomial_ccdf_log(d_int_array, d_int, d_row_vector);
  transformed_data_real <- binomial_ccdf_log(d_int_array, d_int, d_real_array);
  transformed_data_real <- binomial_ccdf_log(d_int_array, d_int_array, d_real);
  transformed_data_real <- binomial_ccdf_log(d_int_array, d_int_array, d_vector);
  transformed_data_real <- binomial_ccdf_log(d_int_array, d_int_array, d_row_vector);
  transformed_data_real <- binomial_ccdf_log(d_int_array, d_int_array, d_real_array);
}
}
parameters {
  real p_real;
  real p_real_array[d_int];
  matrix[d_int,d_int] p_matrix;
  vector[d_int] p_vector;
  row_vector[d_int] p_row_vector;
}
transformed parameters {
  real transformed_param_real;
  real transformed_param_real_array[d_int];
  matrix[d_int,d_int] transformed_param_matrix;
  vector[d_int] transformed_param_vector;
  row_vector[d_int] transformed_param_row_vector;

  //*** Discrete Probabilities ***
  // Bounded Discrete Probabilities
  transformed_param_real <- binomial_log(d_int, d_int, d_real);
  transformed_param_real <- binomial_log(d_int, d_int, p_real);
  transformed_param_real <- binomial_log(d_int, d_int, d_vector);
  transformed_param_real <- binomial_log(d_int, d_int, p_vector);
  transformed_param_real <- binomial_log(d_int, d_int, d_row_vector);
  transformed_param_real <- binomial_log(d_int, d_int, p_row_vector);
  transformed_param_real <- binomial_log(d_int, d_int, d_real_array);
  transformed_param_real <- binomial_log(d_int, d_int, p_real_array);
  transformed_param_real <- binomial_log(d_int, d_int_array, d_real);
  transformed_param_real <- binomial_log(d_int, d_int_array, p_real);
  transformed_param_real <- binomial_log(d_int, d_int_array, d_vector);
  transformed_param_real <- binomial_log(d_int, d_int_array, p_vector);
  transformed_param_real <- binomial_log(d_int, d_int_array, d_row_vector);
  transformed_param_real <- binomial_log(d_int, d_int_array, p_row_vector);
  transformed_param_real <- binomial_log(d_int, d_int_array, d_real_array);
  transformed_param_real <- binomial_log(d_int, d_int_array, p_real_array);
  transformed_param_real <- binomial_log(d_int_array, d_int, d_real);
  transformed_param_real <- binomial_log(d_int_array, d_int, p_real);
  transformed_param_real <- binomial_log(d_int_array, d_int, d_vector);
  transformed_param_real <- binomial_log(d_int_array, d_int, p_vector);
  transformed_param_real <- binomial_log(d_int_array, d_int, d_row_vector);
  transformed_param_real <- binomial_log(d_int_array, d_int, p_row_vector);
  transformed_param_real <- binomial_log(d_int_array, d_int, d_real_array);
  transformed_param_real <- binomial_log(d_int_array, d_int, p_real_array);
  transformed_param_real <- binomial_log(d_int_array, d_int_array, d_real);
  transformed_param_real <- binomial_log(d_int_array, d_int_array, p_real);
  transformed_param_real <- binomial_log(d_int_array, d_int_array, d_vector);
  transformed_param_real <- binomial_log(d_int_array, d_int_array, p_vector);
  transformed_param_real <- binomial_log(d_int_array, d_int_array, d_row_vector);
  transformed_param_real <- binomial_log(d_int_array, d_int_array, p_row_vector);
  transformed_param_real <- binomial_log(d_int_array, d_int_array, d_real_array);
  transformed_param_real <- binomial_log(d_int_array, d_int_array, p_real_array);
  transformed_param_real <- binomial_cdf(d_int, d_int, d_real);
  transformed_param_real <- binomial_cdf(d_int, d_int, p_real);
  transformed_param_real <- binomial_cdf(d_int, d_int, d_vector);
  transformed_param_real <- binomial_cdf(d_int, d_int, p_vector);
  transformed_param_real <- binomial_cdf(d_int, d_int, d_row_vector);
  transformed_param_real <- binomial_cdf(d_int, d_int, p_row_vector);
  transformed_param_real <- binomial_cdf(d_int, d_int, d_real_array);
  transformed_param_real <- binomial_cdf(d_int, d_int, p_real_array);
  transformed_param_real <- binomial_cdf(d_int, d_int_array, d_real);
  transformed_param_real <- binomial_cdf(d_int, d_int_array, p_real);
  transformed_param_real <- binomial_cdf(d_int, d_int_array, d_vector);
  transformed_param_real <- binomial_cdf(d_int, d_int_array, p_vector);
  transformed_param_real <- binomial_cdf(d_int, d_int_array, d_row_vector);
  transformed_param_real <- binomial_cdf(d_int, d_int_array, p_row_vector);
  transformed_param_real <- binomial_cdf(d_int, d_int_array, d_real_array);
  transformed_param_real <- binomial_cdf(d_int, d_int_array, p_real_array);
  transformed_param_real <- binomial_cdf(d_int_array, d_int, d_real);
  transformed_param_real <- binomial_cdf(d_int_array, d_int, p_real);
  transformed_param_real <- binomial_cdf(d_int_array, d_int, d_vector);
  transformed_param_real <- binomial_cdf(d_int_array, d_int, p_vector);
  transformed_param_real <- binomial_cdf(d_int_array, d_int, d_row_vector);
  transformed_param_real <- binomial_cdf(d_int_array, d_int, p_row_vector);
  transformed_param_real <- binomial_cdf(d_int_array, d_int, d_real_array);
  transformed_param_real <- binomial_cdf(d_int_array, d_int, p_real_array);
  transformed_param_real <- binomial_cdf(d_int_array, d_int_array, d_real);
  transformed_param_real <- binomial_cdf(d_int_array, d_int_array, p_real);
  transformed_param_real <- binomial_cdf(d_int_array, d_int_array, d_vector);
  transformed_param_real <- binomial_cdf(d_int_array, d_int_array, p_vector);
  transformed_param_real <- binomial_cdf(d_int_array, d_int_array, d_row_vector);
  transformed_param_real <- binomial_cdf(d_int_array, d_int_array, p_row_vector);
  transformed_param_real <- binomial_cdf(d_int_array, d_int_array, d_real_array);
  transformed_param_real <- binomial_cdf(d_int_array, d_int_array, p_real_array);
  transformed_param_real <- binomial_cdf_log(d_int, d_int, d_real);
  transformed_param_real <- binomial_cdf_log(d_int, d_int, p_real);
  transformed_param_real <- binomial_cdf_log(d_int, d_int, d_vector);
  transformed_param_real <- binomial_cdf_log(d_int, d_int, p_vector);
  transformed_param_real <- binomial_cdf_log(d_int, d_int, d_row_vector);
  transformed_param_real <- binomial_cdf_log(d_int, d_int, p_row_vector);
  transformed_param_real <- binomial_cdf_log(d_int, d_int, d_real_array);
  transformed_param_real <- binomial_cdf_log(d_int, d_int, p_real_array);
  transformed_param_real <- binomial_cdf_log(d_int, d_int_array, d_real);
  transformed_param_real <- binomial_cdf_log(d_int, d_int_array, p_real);
  transformed_param_real <- binomial_cdf_log(d_int, d_int_array, d_vector);
  transformed_param_real <- binomial_cdf_log(d_int, d_int_array, p_vector);
  transformed_param_real <- binomial_cdf_log(d_int, d_int_array, d_row_vector);
  transformed_param_real <- binomial_cdf_log(d_int, d_int_array, p_row_vector);
  transformed_param_real <- binomial_cdf_log(d_int, d_int_array, d_real_array);
  transformed_param_real <- binomial_cdf_log(d_int, d_int_array, p_real_array);
  transformed_param_real <- binomial_cdf_log(d_int_array, d_int, d_real);
  transformed_param_real <- binomial_cdf_log(d_int_array, d_int, p_real);
  transformed_param_real <- binomial_cdf_log(d_int_array, d_int, d_vector);
  transformed_param_real <- binomial_cdf_log(d_int_array, d_int, p_vector);
  transformed_param_real <- binomial_cdf_log(d_int_array, d_int, d_row_vector);
  transformed_param_real <- binomial_cdf_log(d_int_array, d_int, p_row_vector);
  transformed_param_real <- binomial_cdf_log(d_int_array, d_int, d_real_array);
  transformed_param_real <- binomial_cdf_log(d_int_array, d_int, p_real_array);
  transformed_param_real <- binomial_cdf_log(d_int_array, d_int_array, d_real);
  transformed_param_real <- binomial_cdf_log(d_int_array, d_int_array, p_real);
  transformed_param_real <- binomial_cdf_log(d_int_array, d_int_array, d_vector);
  transformed_param_real <- binomial_cdf_log(d_int_array, d_int_array, p_vector);
  transformed_param_real <- binomial_cdf_log(d_int_array, d_int_array, d_row_vector);
  transformed_param_real <- binomial_cdf_log(d_int_array, d_int_array, p_row_vector);
  transformed_param_real <- binomial_cdf_log(d_int_array, d_int_array, d_real_array);
  transformed_param_real <- binomial_cdf_log(d_int_array, d_int_array, p_real_array);
  transformed_param_real <- binomial_ccdf_log(d_int, d_int, d_real);
  transformed_param_real <- binomial_ccdf_log(d_int, d_int, p_real);
  transformed_param_real <- binomial_ccdf_log(d_int, d_int, d_vector);
  transformed_param_real <- binomial_ccdf_log(d_int, d_int, p_vector);
  transformed_param_real <- binomial_ccdf_log(d_int, d_int, d_row_vector);
  transformed_param_real <- binomial_ccdf_log(d_int, d_int, p_row_vector);
  transformed_param_real <- binomial_ccdf_log(d_int, d_int, d_real_array);
  transformed_param_real <- binomial_ccdf_log(d_int, d_int, p_real_array);
  transformed_param_real <- binomial_ccdf_log(d_int, d_int_array, d_real);
  transformed_param_real <- binomial_ccdf_log(d_int, d_int_array, p_real);
  transformed_param_real <- binomial_ccdf_log(d_int, d_int_array, d_vector);
  transformed_param_real <- binomial_ccdf_log(d_int, d_int_array, p_vector);
  transformed_param_real <- binomial_ccdf_log(d_int, d_int_array, d_row_vector);
  transformed_param_real <- binomial_ccdf_log(d_int, d_int_array, p_row_vector);
  transformed_param_real <- binomial_ccdf_log(d_int, d_int_array, d_real_array);
  transformed_param_real <- binomial_ccdf_log(d_int, d_int_array, p_real_array);
  transformed_param_real <- binomial_ccdf_log(d_int_array, d_int, d_real);
  transformed_param_real <- binomial_ccdf_log(d_int_array, d_int, p_real);
  transformed_param_real <- binomial_ccdf_log(d_int_array, d_int, d_vector);
  transformed_param_real <- binomial_ccdf_log(d_int_array, d_int, p_vector);
  transformed_param_real <- binomial_ccdf_log(d_int_array, d_int, d_row_vector);
  transformed_param_real <- binomial_ccdf_log(d_int_array, d_int, p_row_vector);
  transformed_param_real <- binomial_ccdf_log(d_int_array, d_int, d_real_array);
  transformed_param_real <- binomial_ccdf_log(d_int_array, d_int, p_real_array);
  transformed_param_real <- binomial_ccdf_log(d_int_array, d_int_array, d_real);
  transformed_param_real <- binomial_ccdf_log(d_int_array, d_int_array, p_real);
  transformed_param_real <- binomial_ccdf_log(d_int_array, d_int_array, d_vector);
  transformed_param_real <- binomial_ccdf_log(d_int_array, d_int_array, p_vector);
  transformed_param_real <- binomial_ccdf_log(d_int_array, d_int_array, d_row_vector);
  transformed_param_real <- binomial_ccdf_log(d_int_array, d_int_array, p_row_vector);
  transformed_param_real <- binomial_ccdf_log(d_int_array, d_int_array, d_real_array);
  transformed_param_real <- binomial_ccdf_log(d_int_array, d_int_array, p_real_array);
}
model {  
}
