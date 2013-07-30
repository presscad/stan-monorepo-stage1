data {
  int<lower=0> N; 
  int<lower=0> J; 
  vector[N] y;
  vector[J] county;
} 
parameters {
  real<lower=0> sigma_eta;
  real<lower=0> sigma_y;
  real mu;
  vector[J] eta;
} 
transformed paramaters {
  vector[N] y_hat;
  for (i in 1:N)
    y_hat[i] <- mu + eta[county[i]];
}
model {
  sigma_eta ~ uniform(0, 100);
  sigma_y ~ uniform(0, 100);
  mu ~ normal(0, 0.0001);
  eta ~ normal (0, sigma_eta);
  y ~ normal(y_hat,sigma_y);
}
