data { 
  int d_int;
  int d_int_array[d_int];
  real d_real;
  real d_real_array[d_int];
  matrix[d_int,d_int] d_matrix_array[d_int];
  vector[d_int] d_vector_array[d_int];
  row_vector[d_int] d_row_vector_array[d_int];
}
transformed data {
  int transformed_data_int;
  real transformed_data_real;
  real transformed_data_real_array[d_int];
  matrix[d_int,d_int] transformed_data_matrix_array[d_int];
  vector[d_int] transformed_data_vector_array[d_int];
  row_vector[d_int] transformed_data_row_vector_array[d_int];

  transformed_data_real <- multi_student_t_log(d_vector_array[1], d_real, d_vector_array[1], d_matrix_array[1]);
  transformed_data_real <- multi_student_t_log(d_vector_array[1], d_real, d_vector_array, d_matrix_array[1]);
  transformed_data_real <- multi_student_t_log(d_vector_array, d_real, d_vector_array[1], d_matrix_array[1]);
  transformed_data_real <- multi_student_t_log(d_vector_array, d_real, d_vector_array, d_matrix_array[1]);

  transformed_data_real <- multi_student_t_log(d_vector_array[1], d_real, d_row_vector_array[1], d_matrix_array[1]);
  transformed_data_real <- multi_student_t_log(d_vector_array[1], d_real, d_row_vector_array, d_matrix_array[1]);
  transformed_data_real <- multi_student_t_log(d_vector_array, d_real, d_row_vector_array[1], d_matrix_array[1]);
  transformed_data_real <- multi_student_t_log(d_vector_array, d_real, d_row_vector_array, d_matrix_array[1]);

  transformed_data_real <- multi_student_t_log(d_row_vector_array[1], d_real, d_vector_array[1], d_matrix_array[1]);
  transformed_data_real <- multi_student_t_log(d_row_vector_array[1], d_real, d_vector_array, d_matrix_array[1]);
  transformed_data_real <- multi_student_t_log(d_row_vector_array, d_real, d_vector_array[1], d_matrix_array[1]);
  transformed_data_real <- multi_student_t_log(d_row_vector_array, d_real, d_vector_array, d_matrix_array[1]);

  transformed_data_real <- multi_student_t_log(d_row_vector_array[1], d_real, d_row_vector_array[1], d_matrix_array[1]);
  transformed_data_real <- multi_student_t_log(d_row_vector_array[1], d_real, d_row_vector_array, d_matrix_array[1]);
  transformed_data_real <- multi_student_t_log(d_row_vector_array, d_real, d_row_vector_array[1], d_matrix_array[1]);
  transformed_data_real <- multi_student_t_log(d_row_vector_array, d_real, d_row_vector_array, d_matrix_array[1]);

  transformed_data_real <- multi_student_t_log(d_vector_array[1], d_int, d_vector_array[1], d_matrix_array[1]);
  transformed_data_real <- multi_student_t_log(d_vector_array[1], d_int, d_vector_array, d_matrix_array[1]);
  transformed_data_real <- multi_student_t_log(d_vector_array, d_int, d_vector_array[1], d_matrix_array[1]);
  transformed_data_real <- multi_student_t_log(d_vector_array, d_int, d_vector_array, d_matrix_array[1]);

  transformed_data_real <- multi_student_t_log(d_vector_array[1], d_int, d_row_vector_array[1], d_matrix_array[1]);
  transformed_data_real <- multi_student_t_log(d_vector_array[1], d_int, d_row_vector_array, d_matrix_array[1]);
  transformed_data_real <- multi_student_t_log(d_vector_array, d_int, d_row_vector_array[1], d_matrix_array[1]);
  transformed_data_real <- multi_student_t_log(d_vector_array, d_int, d_row_vector_array, d_matrix_array[1]);

  transformed_data_real <- multi_student_t_log(d_row_vector_array[1], d_int, d_vector_array[1], d_matrix_array[1]);
  transformed_data_real <- multi_student_t_log(d_row_vector_array[1], d_int, d_vector_array, d_matrix_array[1]);
  transformed_data_real <- multi_student_t_log(d_row_vector_array, d_int, d_vector_array[1], d_matrix_array[1]);
  transformed_data_real <- multi_student_t_log(d_row_vector_array, d_int, d_vector_array, d_matrix_array[1]);

  transformed_data_real <- multi_student_t_log(d_row_vector_array[1], d_int, d_row_vector_array[1], d_matrix_array[1]);
  transformed_data_real <- multi_student_t_log(d_row_vector_array[1], d_int, d_row_vector_array, d_matrix_array[1]);
  transformed_data_real <- multi_student_t_log(d_row_vector_array, d_int, d_row_vector_array[1], d_matrix_array[1]);
  transformed_data_real <- multi_student_t_log(d_row_vector_array, d_int, d_row_vector_array, d_matrix_array[1]);
}
parameters {
  real p_real;
  real p_real_array[d_int];
  matrix[d_int,d_int] p_matrix_array[d_int];
  vector[d_int] p_vector_array[d_int];
  row_vector[d_int] p_row_vector_array[d_int];
}
transformed parameters {
  real transformed_param_real;
  real transformed_param_real_array[d_int];
  matrix[d_int,d_int] transformed_param_matrix_array[d_int];
  vector[d_int] transformed_param_vector_array[d_int];
  row_vector[d_int] transformed_param_row_vector_array[d_int];

  
  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_real, p_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_real, p_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_real, p_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_real, p_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_real, p_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_real, p_row_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_real, p_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_real, p_row_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_real, p_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_real, p_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_real, p_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_real, p_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_real, p_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_real, p_row_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_real, p_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_real, p_row_vector_array, p_matrix_array[1]);


  //------------------------------------------------------------

  
  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_real, p_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_real, p_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_real, p_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_real, p_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_real, p_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_real, p_row_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_real, p_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_real, p_row_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_real, p_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_real, p_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_real, p_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_real, p_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_real, p_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_real, p_row_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_real, p_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_real, p_row_vector_array, d_matrix_array[1]);


  //------------------------------------------------------------

    transformed_param_real <- multi_student_t_log(p_vector_array[1], d_real, d_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_real, d_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_real, d_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_real, d_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_real, d_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_real, d_row_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_real, d_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_real, d_row_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_real, d_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_real, d_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_real, d_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_real, d_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_real, d_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_real, d_row_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_real, d_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_real, d_row_vector_array, p_matrix_array[1]);


  //------------------------------------------------------------

  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_real, d_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_real, d_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_real, d_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_real, d_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_real, d_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_real, d_row_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_real, d_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_real, d_row_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_real, d_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_real, d_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_real, d_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_real, d_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_real, d_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_real, d_row_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_real, d_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_real, d_row_vector_array, d_matrix_array[1]);


  //------------------------------------------------------------

    
  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_real, p_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_real, p_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_real, p_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_real, p_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_real, p_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_real, p_row_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_real, p_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_real, p_row_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_real, p_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_real, p_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_real, p_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_real, p_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_real, p_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_real, p_row_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_real, p_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_real, p_row_vector_array, p_matrix_array[1]);


  //------------------------------------------------------------

  
  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_real, p_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_real, p_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_real, p_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_real, p_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_real, p_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_real, p_row_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_real, p_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_real, p_row_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_real, p_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_real, p_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_real, p_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_real, p_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_real, p_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_real, p_row_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_real, p_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_real, p_row_vector_array, d_matrix_array[1]);


  //------------------------------------------------------------

    transformed_param_real <- multi_student_t_log(d_vector_array[1], d_real, d_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_real, d_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_real, d_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_real, d_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_real, d_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_real, d_row_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_real, d_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_real, d_row_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_real, d_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_real, d_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_real, d_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_real, d_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_real, d_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_real, d_row_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_real, d_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_real, d_row_vector_array, p_matrix_array[1]);


  //------------------------------------------------------------

  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_real, d_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_real, d_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_real, d_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_real, d_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_real, d_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_real, d_row_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_real, d_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_real, d_row_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_real, d_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_real, d_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_real, d_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_real, d_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_real, d_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_real, d_row_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_real, d_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_real, d_row_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_int, p_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_int, p_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_int, p_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_int, p_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_int, p_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_int, p_row_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_int, p_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_int, p_row_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_int, p_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_int, p_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_int, p_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_int, p_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_int, p_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_int, p_row_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_int, p_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_int, p_row_vector_array, p_matrix_array[1]);


  //------------------------------------------------------------

  
  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_int, p_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_int, p_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_int, p_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_int, p_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_int, p_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_int, p_row_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_int, p_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_int, p_row_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_int, p_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_int, p_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_int, p_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_int, p_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_int, p_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_int, p_row_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_int, p_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_int, p_row_vector_array, d_matrix_array[1]);


  //------------------------------------------------------------

    transformed_param_real <- multi_student_t_log(p_vector_array[1], d_int, d_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_int, d_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_int, d_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_int, d_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_int, d_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_int, d_row_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_int, d_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_int, d_row_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_int, d_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_int, d_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_int, d_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_int, d_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_int, d_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_int, d_row_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_int, d_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_int, d_row_vector_array, p_matrix_array[1]);


  //------------------------------------------------------------

  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_int, d_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_int, d_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_int, d_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_int, d_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_int, d_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array[1], d_int, d_row_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_int, d_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, d_int, d_row_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_int, d_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_int, d_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_int, d_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_int, d_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_int, d_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], d_int, d_row_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_int, d_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, d_int, d_row_vector_array, d_matrix_array[1]);


  //------------------------------------------------------------

    
  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_int, p_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_int, p_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_int, p_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_int, p_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_int, p_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_int, p_row_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_int, p_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_int, p_row_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_int, p_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_int, p_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_int, p_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_int, p_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_int, p_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_int, p_row_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_int, p_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_int, p_row_vector_array, p_matrix_array[1]);


  //------------------------------------------------------------

  
  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_int, p_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_int, p_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_int, p_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_int, p_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_int, p_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_int, p_row_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_int, p_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_int, p_row_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_int, p_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_int, p_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_int, p_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_int, p_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_int, p_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_int, p_row_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_int, p_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_int, p_row_vector_array, d_matrix_array[1]);


  //------------------------------------------------------------

    transformed_param_real <- multi_student_t_log(d_vector_array[1], d_int, d_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_int, d_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_int, d_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_int, d_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_int, d_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_int, d_row_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_int, d_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_int, d_row_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_int, d_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_int, d_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_int, d_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_int, d_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_int, d_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_int, d_row_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_int, d_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_int, d_row_vector_array, p_matrix_array[1]);


  //------------------------------------------------------------

  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_int, d_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_int, d_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_int, d_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_int, d_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_int, d_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array[1], d_int, d_row_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_int, d_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, d_int, d_row_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_int, d_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_int, d_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_int, d_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_int, d_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_int, d_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], d_int, d_row_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_int, d_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, d_int, d_row_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array[1], p_real, p_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array[1], p_real, p_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, p_real, p_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, p_real, p_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_vector_array[1], p_real, p_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array[1], p_real, p_row_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, p_real, p_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, p_real, p_row_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], p_real, p_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], p_real, p_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, p_real, p_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, p_real, p_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], p_real, p_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], p_real, p_row_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, p_real, p_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, p_real, p_row_vector_array, p_matrix_array[1]);


  //------------------------------------------------------------

  
  transformed_param_real <- multi_student_t_log(p_vector_array[1], p_real, p_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array[1], p_real, p_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, p_real, p_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, p_real, p_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_vector_array[1], p_real, p_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array[1], p_real, p_row_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, p_real, p_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, p_real, p_row_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], p_real, p_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], p_real, p_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, p_real, p_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, p_real, p_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], p_real, p_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], p_real, p_row_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, p_real, p_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, p_real, p_row_vector_array, d_matrix_array[1]);


  //------------------------------------------------------------

    transformed_param_real <- multi_student_t_log(p_vector_array[1], p_real, d_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array[1], p_real, d_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, p_real, d_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, p_real, d_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_vector_array[1], p_real, d_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array[1], p_real, d_row_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, p_real, d_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, p_real, d_row_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], p_real, d_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], p_real, d_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, p_real, d_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, p_real, d_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], p_real, d_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], p_real, d_row_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, p_real, d_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, p_real, d_row_vector_array, p_matrix_array[1]);


  //------------------------------------------------------------

  transformed_param_real <- multi_student_t_log(p_vector_array[1], p_real, d_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array[1], p_real, d_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, p_real, d_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, p_real, d_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_vector_array[1], p_real, d_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array[1], p_real, d_row_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, p_real, d_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_vector_array, p_real, d_row_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], p_real, d_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], p_real, d_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, p_real, d_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, p_real, d_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], p_real, d_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array[1], p_real, d_row_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, p_real, d_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(p_row_vector_array, p_real, d_row_vector_array, d_matrix_array[1]);


  //------------------------------------------------------------

    
  transformed_param_real <- multi_student_t_log(d_vector_array[1], p_real, p_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array[1], p_real, p_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, p_real, p_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, p_real, p_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_vector_array[1], p_real, p_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array[1], p_real, p_row_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, p_real, p_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, p_real, p_row_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], p_real, p_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], p_real, p_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, p_real, p_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, p_real, p_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], p_real, p_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], p_real, p_row_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, p_real, p_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, p_real, p_row_vector_array, p_matrix_array[1]);


  //------------------------------------------------------------

  
  transformed_param_real <- multi_student_t_log(d_vector_array[1], p_real, p_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array[1], p_real, p_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, p_real, p_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, p_real, p_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_vector_array[1], p_real, p_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array[1], p_real, p_row_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, p_real, p_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, p_real, p_row_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], p_real, p_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], p_real, p_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, p_real, p_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, p_real, p_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], p_real, p_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], p_real, p_row_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, p_real, p_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, p_real, p_row_vector_array, d_matrix_array[1]);


  //------------------------------------------------------------

    transformed_param_real <- multi_student_t_log(d_vector_array[1], p_real, d_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array[1], p_real, d_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, p_real, d_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, p_real, d_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_vector_array[1], p_real, d_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array[1], p_real, d_row_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, p_real, d_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, p_real, d_row_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], p_real, d_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], p_real, d_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, p_real, d_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, p_real, d_vector_array, p_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], p_real, d_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], p_real, d_row_vector_array, p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, p_real, d_row_vector_array[1], p_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, p_real, d_row_vector_array, p_matrix_array[1]);


  //------------------------------------------------------------

  transformed_param_real <- multi_student_t_log(d_vector_array[1], p_real, d_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array[1], p_real, d_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, p_real, d_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, p_real, d_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_vector_array[1], p_real, d_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array[1], p_real, d_row_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, p_real, d_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_vector_array, p_real, d_row_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], p_real, d_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], p_real, d_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, p_real, d_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, p_real, d_vector_array, d_matrix_array[1]);

  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], p_real, d_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array[1], p_real, d_row_vector_array, d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, p_real, d_row_vector_array[1], d_matrix_array[1]);
  transformed_param_real <- multi_student_t_log(d_row_vector_array, p_real, d_row_vector_array, d_matrix_array[1]);
}


model {
  d_vector_array[1] ~ multi_student_t(d_real, d_vector_array[1], d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_real, d_vector_array, d_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_real, d_vector_array[1], d_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_real, d_vector_array, d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_real, d_row_vector_array[1], d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_real, d_row_vector_array, d_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_real, d_row_vector_array[1], d_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_real, d_row_vector_array, d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_real, d_vector_array[1], d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_real, d_vector_array, d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_real, d_vector_array[1], d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_real, d_vector_array, d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_real, d_row_vector_array[1], d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_real, d_row_vector_array, d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_real, d_row_vector_array[1], d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_real, d_row_vector_array, d_matrix_array[1]);
  

  //------------------------------------------------------------
  //------------------------------------------------------------

  p_vector_array[1] ~ multi_student_t(d_real, p_vector_array[1], p_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(d_real, p_vector_array, p_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_real, p_vector_array[1], p_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_real, p_vector_array, p_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(d_real, p_row_vector_array[1], p_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(d_real, p_row_vector_array, p_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_real, p_row_vector_array[1], p_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_real, p_row_vector_array, p_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_real, p_vector_array[1], p_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_real, p_vector_array, p_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_real, p_vector_array[1], p_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_real, p_vector_array, p_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_real, p_row_vector_array[1], p_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_real, p_row_vector_array, p_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_real, p_row_vector_array[1], p_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_real, p_row_vector_array, p_matrix_array[1]);


  //------------------------------------------------------------

  
  p_vector_array[1] ~ multi_student_t(d_real, p_vector_array[1], d_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(d_real, p_vector_array, d_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_real, p_vector_array[1], d_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_real, p_vector_array, d_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(d_real, p_row_vector_array[1], d_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(d_real, p_row_vector_array, d_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_real, p_row_vector_array[1], d_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_real, p_row_vector_array, d_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_real, p_vector_array[1], d_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_real, p_vector_array, d_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_real, p_vector_array[1], d_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_real, p_vector_array, d_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_real, p_row_vector_array[1], d_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_real, p_row_vector_array, d_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_real, p_row_vector_array[1], d_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_real, p_row_vector_array, d_matrix_array[1]);


  //------------------------------------------------------------

  p_vector_array[1] ~ multi_student_t(d_real, d_vector_array[1], p_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(d_real, d_vector_array, p_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_real, d_vector_array[1], p_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_real, d_vector_array, p_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(d_real, d_row_vector_array[1], p_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(d_real, d_row_vector_array, p_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_real, d_row_vector_array[1], p_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_real, d_row_vector_array, p_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_real, d_vector_array[1], p_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_real, d_vector_array, p_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_real, d_vector_array[1], p_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_real, d_vector_array, p_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_real, d_row_vector_array[1], p_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_real, d_row_vector_array, p_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_real, d_row_vector_array[1], p_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_real, d_row_vector_array, p_matrix_array[1]);


  //------------------------------------------------------------

  p_vector_array[1] ~ multi_student_t(d_real, d_vector_array[1], d_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(d_real, d_vector_array, d_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_real, d_vector_array[1], d_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_real, d_vector_array, d_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(d_real, d_row_vector_array[1], d_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(d_real, d_row_vector_array, d_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_real, d_row_vector_array[1], d_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_real, d_row_vector_array, d_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_real, d_vector_array[1], d_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_real, d_vector_array, d_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_real, d_vector_array[1], d_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_real, d_vector_array, d_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_real, d_row_vector_array[1], d_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_real, d_row_vector_array, d_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_real, d_row_vector_array[1], d_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_real, d_row_vector_array, d_matrix_array[1]);


  //------------------------------------------------------------

    
  d_vector_array[1] ~ multi_student_t(d_real, p_vector_array[1], p_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_real, p_vector_array, p_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_real, p_vector_array[1], p_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_real, p_vector_array, p_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_real, p_row_vector_array[1], p_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_real, p_row_vector_array, p_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_real, p_row_vector_array[1], p_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_real, p_row_vector_array, p_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_real, p_vector_array[1], p_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_real, p_vector_array, p_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_real, p_vector_array[1], p_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_real, p_vector_array, p_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_real, p_row_vector_array[1], p_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_real, p_row_vector_array, p_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_real, p_row_vector_array[1], p_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_real, p_row_vector_array, p_matrix_array[1]);


  //------------------------------------------------------------

  
  d_vector_array[1] ~ multi_student_t(d_real, p_vector_array[1], d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_real, p_vector_array, d_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_real, p_vector_array[1], d_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_real, p_vector_array, d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_real, p_row_vector_array[1], d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_real, p_row_vector_array, d_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_real, p_row_vector_array[1], d_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_real, p_row_vector_array, d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_real, p_vector_array[1], d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_real, p_vector_array, d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_real, p_vector_array[1], d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_real, p_vector_array, d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_real, p_row_vector_array[1], d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_real, p_row_vector_array, d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_real, p_row_vector_array[1], d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_real, p_row_vector_array, d_matrix_array[1]);


  //------------------------------------------------------------

  d_vector_array[1] ~ multi_student_t(d_real, d_vector_array[1], p_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_real, d_vector_array, p_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_real, d_vector_array[1], p_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_real, d_vector_array, p_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_real, d_row_vector_array[1], p_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_real, d_row_vector_array, p_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_real, d_row_vector_array[1], p_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_real, d_row_vector_array, p_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_real, d_vector_array[1], p_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_real, d_vector_array, p_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_real, d_vector_array[1], p_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_real, d_vector_array, p_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_real, d_row_vector_array[1], p_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_real, d_row_vector_array, p_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_real, d_row_vector_array[1], p_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_real, d_row_vector_array, p_matrix_array[1]);


  //------------------------------------------------------------

  d_vector_array[1] ~ multi_student_t(d_real, d_vector_array[1], d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_real, d_vector_array, d_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_real, d_vector_array[1], d_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_real, d_vector_array, d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_real, d_row_vector_array[1], d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_real, d_row_vector_array, d_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_real, d_row_vector_array[1], d_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_real, d_row_vector_array, d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_real, d_vector_array[1], d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_real, d_vector_array, d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_real, d_vector_array[1], d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_real, d_vector_array, d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_real, d_row_vector_array[1], d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_real, d_row_vector_array, d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_real, d_row_vector_array[1], d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_real, d_row_vector_array, d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_int, d_vector_array[1], d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_int, d_vector_array, d_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_int, d_vector_array[1], d_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_int, d_vector_array, d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_int, d_row_vector_array[1], d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_int, d_row_vector_array, d_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_int, d_row_vector_array[1], d_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_int, d_row_vector_array, d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_int, d_vector_array[1], d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_int, d_vector_array, d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_int, d_vector_array[1], d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_int, d_vector_array, d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_int, d_row_vector_array[1], d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_int, d_row_vector_array, d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_int, d_row_vector_array[1], d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_int, d_row_vector_array, d_matrix_array[1]);
  

  //------------------------------------------------------------
  //------------------------------------------------------------

  p_vector_array[1] ~ multi_student_t(d_int, p_vector_array[1], p_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(d_int, p_vector_array, p_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_int, p_vector_array[1], p_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_int, p_vector_array, p_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(d_int, p_row_vector_array[1], p_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(d_int, p_row_vector_array, p_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_int, p_row_vector_array[1], p_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_int, p_row_vector_array, p_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_int, p_vector_array[1], p_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_int, p_vector_array, p_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_int, p_vector_array[1], p_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_int, p_vector_array, p_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_int, p_row_vector_array[1], p_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_int, p_row_vector_array, p_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_int, p_row_vector_array[1], p_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_int, p_row_vector_array, p_matrix_array[1]);


  //------------------------------------------------------------

  
  p_vector_array[1] ~ multi_student_t(d_int, p_vector_array[1], d_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(d_int, p_vector_array, d_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_int, p_vector_array[1], d_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_int, p_vector_array, d_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(d_int, p_row_vector_array[1], d_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(d_int, p_row_vector_array, d_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_int, p_row_vector_array[1], d_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_int, p_row_vector_array, d_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_int, p_vector_array[1], d_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_int, p_vector_array, d_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_int, p_vector_array[1], d_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_int, p_vector_array, d_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_int, p_row_vector_array[1], d_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_int, p_row_vector_array, d_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_int, p_row_vector_array[1], d_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_int, p_row_vector_array, d_matrix_array[1]);


  //------------------------------------------------------------

  p_vector_array[1] ~ multi_student_t(d_int, d_vector_array[1], p_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(d_int, d_vector_array, p_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_int, d_vector_array[1], p_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_int, d_vector_array, p_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(d_int, d_row_vector_array[1], p_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(d_int, d_row_vector_array, p_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_int, d_row_vector_array[1], p_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_int, d_row_vector_array, p_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_int, d_vector_array[1], p_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_int, d_vector_array, p_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_int, d_vector_array[1], p_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_int, d_vector_array, p_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_int, d_row_vector_array[1], p_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_int, d_row_vector_array, p_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_int, d_row_vector_array[1], p_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_int, d_row_vector_array, p_matrix_array[1]);


  //------------------------------------------------------------

  p_vector_array[1] ~ multi_student_t(d_int, d_vector_array[1], d_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(d_int, d_vector_array, d_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_int, d_vector_array[1], d_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_int, d_vector_array, d_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(d_int, d_row_vector_array[1], d_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(d_int, d_row_vector_array, d_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_int, d_row_vector_array[1], d_matrix_array[1]);
  p_vector_array ~ multi_student_t(d_int, d_row_vector_array, d_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_int, d_vector_array[1], d_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_int, d_vector_array, d_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_int, d_vector_array[1], d_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_int, d_vector_array, d_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_int, d_row_vector_array[1], d_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(d_int, d_row_vector_array, d_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_int, d_row_vector_array[1], d_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(d_int, d_row_vector_array, d_matrix_array[1]);


  //------------------------------------------------------------

    
  d_vector_array[1] ~ multi_student_t(d_int, p_vector_array[1], p_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_int, p_vector_array, p_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_int, p_vector_array[1], p_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_int, p_vector_array, p_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_int, p_row_vector_array[1], p_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_int, p_row_vector_array, p_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_int, p_row_vector_array[1], p_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_int, p_row_vector_array, p_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_int, p_vector_array[1], p_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_int, p_vector_array, p_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_int, p_vector_array[1], p_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_int, p_vector_array, p_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_int, p_row_vector_array[1], p_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_int, p_row_vector_array, p_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_int, p_row_vector_array[1], p_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_int, p_row_vector_array, p_matrix_array[1]);


  //------------------------------------------------------------

  
  d_vector_array[1] ~ multi_student_t(d_int, p_vector_array[1], d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_int, p_vector_array, d_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_int, p_vector_array[1], d_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_int, p_vector_array, d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_int, p_row_vector_array[1], d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_int, p_row_vector_array, d_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_int, p_row_vector_array[1], d_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_int, p_row_vector_array, d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_int, p_vector_array[1], d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_int, p_vector_array, d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_int, p_vector_array[1], d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_int, p_vector_array, d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_int, p_row_vector_array[1], d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_int, p_row_vector_array, d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_int, p_row_vector_array[1], d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_int, p_row_vector_array, d_matrix_array[1]);


  //------------------------------------------------------------

  d_vector_array[1] ~ multi_student_t(d_int, d_vector_array[1], p_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_int, d_vector_array, p_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_int, d_vector_array[1], p_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_int, d_vector_array, p_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_int, d_row_vector_array[1], p_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_int, d_row_vector_array, p_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_int, d_row_vector_array[1], p_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_int, d_row_vector_array, p_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_int, d_vector_array[1], p_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_int, d_vector_array, p_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_int, d_vector_array[1], p_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_int, d_vector_array, p_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_int, d_row_vector_array[1], p_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_int, d_row_vector_array, p_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_int, d_row_vector_array[1], p_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_int, d_row_vector_array, p_matrix_array[1]);


  //------------------------------------------------------------

  d_vector_array[1] ~ multi_student_t(d_int, d_vector_array[1], d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_int, d_vector_array, d_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_int, d_vector_array[1], d_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_int, d_vector_array, d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_int, d_row_vector_array[1], d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(d_int, d_row_vector_array, d_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_int, d_row_vector_array[1], d_matrix_array[1]);
  d_vector_array ~ multi_student_t(d_int, d_row_vector_array, d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_int, d_vector_array[1], d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_int, d_vector_array, d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_int, d_vector_array[1], d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_int, d_vector_array, d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_int, d_row_vector_array[1], d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(d_int, d_row_vector_array, d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_int, d_row_vector_array[1], d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(d_int, d_row_vector_array, d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(p_real, d_vector_array[1], d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(p_real, d_vector_array, d_matrix_array[1]);
  d_vector_array ~ multi_student_t(p_real, d_vector_array[1], d_matrix_array[1]);
  d_vector_array ~ multi_student_t(p_real, d_vector_array, d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(p_real, d_row_vector_array[1], d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(p_real, d_row_vector_array, d_matrix_array[1]);
  d_vector_array ~ multi_student_t(p_real, d_row_vector_array[1], d_matrix_array[1]);
  d_vector_array ~ multi_student_t(p_real, d_row_vector_array, d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(p_real, d_vector_array[1], d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(p_real, d_vector_array, d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(p_real, d_vector_array[1], d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(p_real, d_vector_array, d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(p_real, d_row_vector_array[1], d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(p_real, d_row_vector_array, d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(p_real, d_row_vector_array[1], d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(p_real, d_row_vector_array, d_matrix_array[1]);
  

  //------------------------------------------------------------
  //------------------------------------------------------------

  p_vector_array[1] ~ multi_student_t(p_real, p_vector_array[1], p_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(p_real, p_vector_array, p_matrix_array[1]);
  p_vector_array ~ multi_student_t(p_real, p_vector_array[1], p_matrix_array[1]);
  p_vector_array ~ multi_student_t(p_real, p_vector_array, p_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(p_real, p_row_vector_array[1], p_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(p_real, p_row_vector_array, p_matrix_array[1]);
  p_vector_array ~ multi_student_t(p_real, p_row_vector_array[1], p_matrix_array[1]);
  p_vector_array ~ multi_student_t(p_real, p_row_vector_array, p_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(p_real, p_vector_array[1], p_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(p_real, p_vector_array, p_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(p_real, p_vector_array[1], p_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(p_real, p_vector_array, p_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(p_real, p_row_vector_array[1], p_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(p_real, p_row_vector_array, p_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(p_real, p_row_vector_array[1], p_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(p_real, p_row_vector_array, p_matrix_array[1]);


  //------------------------------------------------------------

  
  p_vector_array[1] ~ multi_student_t(p_real, p_vector_array[1], d_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(p_real, p_vector_array, d_matrix_array[1]);
  p_vector_array ~ multi_student_t(p_real, p_vector_array[1], d_matrix_array[1]);
  p_vector_array ~ multi_student_t(p_real, p_vector_array, d_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(p_real, p_row_vector_array[1], d_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(p_real, p_row_vector_array, d_matrix_array[1]);
  p_vector_array ~ multi_student_t(p_real, p_row_vector_array[1], d_matrix_array[1]);
  p_vector_array ~ multi_student_t(p_real, p_row_vector_array, d_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(p_real, p_vector_array[1], d_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(p_real, p_vector_array, d_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(p_real, p_vector_array[1], d_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(p_real, p_vector_array, d_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(p_real, p_row_vector_array[1], d_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(p_real, p_row_vector_array, d_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(p_real, p_row_vector_array[1], d_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(p_real, p_row_vector_array, d_matrix_array[1]);


  //------------------------------------------------------------

  p_vector_array[1] ~ multi_student_t(p_real, d_vector_array[1], p_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(p_real, d_vector_array, p_matrix_array[1]);
  p_vector_array ~ multi_student_t(p_real, d_vector_array[1], p_matrix_array[1]);
  p_vector_array ~ multi_student_t(p_real, d_vector_array, p_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(p_real, d_row_vector_array[1], p_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(p_real, d_row_vector_array, p_matrix_array[1]);
  p_vector_array ~ multi_student_t(p_real, d_row_vector_array[1], p_matrix_array[1]);
  p_vector_array ~ multi_student_t(p_real, d_row_vector_array, p_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(p_real, d_vector_array[1], p_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(p_real, d_vector_array, p_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(p_real, d_vector_array[1], p_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(p_real, d_vector_array, p_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(p_real, d_row_vector_array[1], p_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(p_real, d_row_vector_array, p_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(p_real, d_row_vector_array[1], p_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(p_real, d_row_vector_array, p_matrix_array[1]);


  //------------------------------------------------------------

  p_vector_array[1] ~ multi_student_t(p_real, d_vector_array[1], d_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(p_real, d_vector_array, d_matrix_array[1]);
  p_vector_array ~ multi_student_t(p_real, d_vector_array[1], d_matrix_array[1]);
  p_vector_array ~ multi_student_t(p_real, d_vector_array, d_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(p_real, d_row_vector_array[1], d_matrix_array[1]);
  p_vector_array[1] ~ multi_student_t(p_real, d_row_vector_array, d_matrix_array[1]);
  p_vector_array ~ multi_student_t(p_real, d_row_vector_array[1], d_matrix_array[1]);
  p_vector_array ~ multi_student_t(p_real, d_row_vector_array, d_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(p_real, d_vector_array[1], d_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(p_real, d_vector_array, d_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(p_real, d_vector_array[1], d_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(p_real, d_vector_array, d_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(p_real, d_row_vector_array[1], d_matrix_array[1]);
  p_row_vector_array[1] ~ multi_student_t(p_real, d_row_vector_array, d_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(p_real, d_row_vector_array[1], d_matrix_array[1]);
  p_row_vector_array ~ multi_student_t(p_real, d_row_vector_array, d_matrix_array[1]);


  //------------------------------------------------------------

    
  d_vector_array[1] ~ multi_student_t(p_real, p_vector_array[1], p_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(p_real, p_vector_array, p_matrix_array[1]);
  d_vector_array ~ multi_student_t(p_real, p_vector_array[1], p_matrix_array[1]);
  d_vector_array ~ multi_student_t(p_real, p_vector_array, p_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(p_real, p_row_vector_array[1], p_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(p_real, p_row_vector_array, p_matrix_array[1]);
  d_vector_array ~ multi_student_t(p_real, p_row_vector_array[1], p_matrix_array[1]);
  d_vector_array ~ multi_student_t(p_real, p_row_vector_array, p_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(p_real, p_vector_array[1], p_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(p_real, p_vector_array, p_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(p_real, p_vector_array[1], p_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(p_real, p_vector_array, p_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(p_real, p_row_vector_array[1], p_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(p_real, p_row_vector_array, p_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(p_real, p_row_vector_array[1], p_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(p_real, p_row_vector_array, p_matrix_array[1]);


  //------------------------------------------------------------

  
  d_vector_array[1] ~ multi_student_t(p_real, p_vector_array[1], d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(p_real, p_vector_array, d_matrix_array[1]);
  d_vector_array ~ multi_student_t(p_real, p_vector_array[1], d_matrix_array[1]);
  d_vector_array ~ multi_student_t(p_real, p_vector_array, d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(p_real, p_row_vector_array[1], d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(p_real, p_row_vector_array, d_matrix_array[1]);
  d_vector_array ~ multi_student_t(p_real, p_row_vector_array[1], d_matrix_array[1]);
  d_vector_array ~ multi_student_t(p_real, p_row_vector_array, d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(p_real, p_vector_array[1], d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(p_real, p_vector_array, d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(p_real, p_vector_array[1], d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(p_real, p_vector_array, d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(p_real, p_row_vector_array[1], d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(p_real, p_row_vector_array, d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(p_real, p_row_vector_array[1], d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(p_real, p_row_vector_array, d_matrix_array[1]);


  //------------------------------------------------------------

  d_vector_array[1] ~ multi_student_t(p_real, d_vector_array[1], p_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(p_real, d_vector_array, p_matrix_array[1]);
  d_vector_array ~ multi_student_t(p_real, d_vector_array[1], p_matrix_array[1]);
  d_vector_array ~ multi_student_t(p_real, d_vector_array, p_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(p_real, d_row_vector_array[1], p_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(p_real, d_row_vector_array, p_matrix_array[1]);
  d_vector_array ~ multi_student_t(p_real, d_row_vector_array[1], p_matrix_array[1]);
  d_vector_array ~ multi_student_t(p_real, d_row_vector_array, p_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(p_real, d_vector_array[1], p_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(p_real, d_vector_array, p_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(p_real, d_vector_array[1], p_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(p_real, d_vector_array, p_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(p_real, d_row_vector_array[1], p_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(p_real, d_row_vector_array, p_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(p_real, d_row_vector_array[1], p_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(p_real, d_row_vector_array, p_matrix_array[1]);


  //------------------------------------------------------------

  d_vector_array[1] ~ multi_student_t(p_real, d_vector_array[1], d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(p_real, d_vector_array, d_matrix_array[1]);
  d_vector_array ~ multi_student_t(p_real, d_vector_array[1], d_matrix_array[1]);
  d_vector_array ~ multi_student_t(p_real, d_vector_array, d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(p_real, d_row_vector_array[1], d_matrix_array[1]);
  d_vector_array[1] ~ multi_student_t(p_real, d_row_vector_array, d_matrix_array[1]);
  d_vector_array ~ multi_student_t(p_real, d_row_vector_array[1], d_matrix_array[1]);
  d_vector_array ~ multi_student_t(p_real, d_row_vector_array, d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(p_real, d_vector_array[1], d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(p_real, d_vector_array, d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(p_real, d_vector_array[1], d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(p_real, d_vector_array, d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(p_real, d_row_vector_array[1], d_matrix_array[1]);
  d_row_vector_array[1] ~ multi_student_t(p_real, d_row_vector_array, d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(p_real, d_row_vector_array[1], d_matrix_array[1]);
  d_row_vector_array ~ multi_student_t(p_real, d_row_vector_array, d_matrix_array[1]);
}
