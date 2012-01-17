data {
  int(0,) N; //1000, number of students
  int(0,) R; //32, number of patterns of results: 2^T
  int(0,) T; //5, number of questions
  int(0,) culm[R];
  int(0,) response[R,T];
}

transformed data {
  int r[N,T];
  
  for (j in 1:culm[1]) {
    for (k in 1:T) {
      r[j,k] <- response[1,k];
   } 
  }
  for (i in 2:R) {
    for (j in (culm[i-1] + 1):culm[i]) {
      for (k in 1:T) {
        r[j,k] <- response[i,k];
      }
    }
  } 
}
parameters {
  double alpha[T];
  double theta[N];
  double(0,) beta;
}

//transformed parameters {
//  double mean_alpha;
//  double a[T];
//}

model {
  // priors
  for (k in 1:T) {
    alpha[k] ~ normal(0.0,1.0E2);
  }

//  for(k in 1:T) {
//    mean_alpha <- mean(alpha);
//    a[k] <- alpha[k] - mean_alpha;
//   }
  
  for(j in 1:N) { 
    theta[j] ~ normal(0,1);
  }
  
  beta ~ normal(0.0,1.0E2);
  // Rasch model
  for (j in 1:N) {
    for (k in 1:T) {
      r[j,k] ~ bernoulli(inv_logit(beta*theta[j] - alpha[k]));
    }
  }
}

