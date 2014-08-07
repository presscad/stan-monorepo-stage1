data { 
  int d_int;
  matrix[d_int,d_int] d_matrix;
}

transformed data {
  vector[d_int] transformed_data_vector;

  transformed_data_vector <- diagonal(d_matrix);
}
parameters {
  real y_p;
  matrix[d_int,d_int] p_matrix;
}
transformed parameters {
  vector[d_int] transformed_param_vector;

  transformed_param_vector <- diagonal(d_matrix);
  transformed_param_vector <- diagonal(p_matrix);
}
model {  
  y_p ~ normal(0,1);
}
