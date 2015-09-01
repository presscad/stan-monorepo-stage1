
data { 
  int d_int;
  matrix[d_int,d_int] d_matrix;
}

transformed data {
  matrix[d_int, d_int] transformed_d_matrix;
  vector[d_int] transformed_data_vector_w;
  int transformed_data_array_v[d_int];
  int transformed_data_array_u[d_int];
  int transformed_data_array_z[d_int];

  transformed_d_matrix <- csr_to_dense_matrix(
    d_int, d_int,
    transformed_data_vector_w,
    transformed_data_array_v,
    transformed_data_array_u,
    transformed_data_array_z
  );
}

parameters {
  real y_p;
  matrix[d_int,d_int] p_matrix;
}

transformed parameters {
  matrix[d_int, d_int] transformed_p_matrix;
  vector[d_int] transformed_param_vector_w;

  transformed_p_matrix <- csr_to_dense_matrix(
    d_int, d_int,
    transformed_param_vector_w,
    transformed_data_array_v,
    transformed_data_array_u,
    transformed_data_array_z
  );
}

model {  
  y_p ~ normal(0,1);
}
