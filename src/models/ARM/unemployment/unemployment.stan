data {
  int<lower=0> N; 
  vector[N] y_lag;
  vector[N] y;
}
parameters {
  vector[2] beta;
  real<lower=0> sigma;
} 
model {
  y ~ normal(beta[1] + beta[2] * y_lag,sigma);
}
