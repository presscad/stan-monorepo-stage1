# Jaws: repeated measures analysis of variance
#  http://www.openbugs.info/Examples/Jaws.html


## status: not work (adaption hangs)

data {
  int(0,) N; 
  int(0,) M; 
  vector(M) Y[N]; 
  double age[M]; 
  cov_matrix(4) R; 
} 

transformed data {
  double mean_age;
  mean_age <- mean(age); 
} 


parameters {
  double beta0; 
  double beta1; 
  cov_matrix(4) Sigma; 
} 

model {
  vector(4) mu; 
  for (m in 1:M) mu[m] <- beta0 + beta1 * (age[m] - mean_age); 
  for (n in 1:N) Y[n] ~ multi_normal(mu, Sigma); 

  Sigma ~ inv_wishart(4, R); 
  beta0 ~ normal(0, 32);
  beta1 ~ normal(0, 32);
} 
