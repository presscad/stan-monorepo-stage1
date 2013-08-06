data {
  int<lower=0> N; 
  int<lower=0> n_treatment; 
  int<lower=0> n_airport; 
  vector[N] y;
  int airport[N];
  int treatment[N];
} 
parameters {
  vector[n_treatment] g;
  vector[n_airport] d;
  real<lower=0> sigma_y;
  real<lower=0> sigma_d;
  real<lower=0> sigma_g;
  real mu;
  real mu_d;
  real mu_g;
} 
transformed parameters {
  vector[N] y_hat;
  vector[n_treatment] g_adj;
  vector[n_airport] d_adj;
  real mu_adj;
  real mu_g2;
  real mu_d2;
  mu_g2 <- mean(g);
  mu_d2 <- mean(d);
  g_adj <- g - mu_g2;
  d_adj <- d - mu_d2;
  mu_adj <- mu + mu_g2 + mu_d2;
  for (i in 1:N)
    y_hat[i] <- mu + g[treatment[i]] + d[airport[i]];
}
model {
  sigma_y ~ uniform(0, 100);
  sigma_d ~ uniform(0, 100);
  sigma_g ~ uniform(0, 100);
  mu ~ normal(0, 100);
  mu_g ~ normal(0, 100);
  mu_d ~ normal(0, 100);
  g ~ normal(mu_g, sigma_g);
  d ~ normal(mu_d, sigma_d);
  y ~ normal(y_hat, sigma_y);
}
