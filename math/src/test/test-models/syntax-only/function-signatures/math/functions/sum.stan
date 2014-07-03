data { 
  int d_int;
  int d_int_array[d_int];
  real d_real_array[d_int];
  matrix[d_int,d_int] d_matrix;
  vector[d_int] d_vector;
  row_vector[d_int] d_row_vector;
}

transformed data {
  int transformed_data_int;
  real transformed_data_real;

   transformed_data_real <- sum(d_int_array);
   transformed_data_real <-  sum(d_real_array);
   transformed_data_real <-  sum(d_matrix);
   transformed_data_real <-  sum(d_vector);
   transformed_data_real <-  sum(d_row_vector);
   

}
parameters {
  real p_real;
  real y_p;
  real p_real_array[d_int];
  matrix[d_int,d_int] p_matrix;
  vector[d_int] p_vector;
  row_vector[d_int] p_row_vector;
}
transformed parameters {
  real transformed_param_real;

   transformed_param_real <-  sum(d_int_array);
   transformed_param_real <-  sum(d_real_array);
   transformed_param_real <-  sum(d_matrix);
   transformed_param_real <-  sum(d_vector);
   transformed_param_real <-  sum(d_row_vector);
   transformed_param_real <-  sum(p_real_array);
   transformed_param_real <-  sum(p_matrix);
   transformed_param_real <-  sum(p_vector);
   transformed_param_real <-  sum(p_row_vector);
}
model {  
  y_p ~ normal(0,1);
}
