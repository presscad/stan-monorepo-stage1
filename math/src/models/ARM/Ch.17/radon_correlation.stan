data {
  int<lower=0> N;
  int<lower=0> J;
  vector[N] y;
  int<lower=0,upper=1> x[N];
  int county[N];
}
parameters {
  real<lower=0> sigma;
  real<lower=0> sigma_a;
  real<lower=0> sigma_b;
  real mu_a;
  real mu_b;
  real<lower=-1,upper=1> rho;
  matrix[J,2] B;
}
model {
  vector[N] y_hat;
  vector[J] a;
  vector[J] b;
  matrix[J,2] B_hat;
  matrix[2,2] Sigma_b;

  mu_a ~ normal(0, 100);
  mu_b ~ normal(0, 100);
  rho ~ uniform(-1, 1);

  Sigma_b[1,1] <- pow(sigma_a, 2);
  Sigma_b[2,2] <- pow(sigma_b, 2);
  Sigma_b[1,2] <- rho * sigma_a * sigma_b;
  Sigma_b[2,1] <- Sigma_b[1,2];

  for (j in 1:J) {
    B_hat[j,1] <- mu_a;
    B_hat[j,2] <- mu_b;
    B[j,1:2] ~ multi_normal(B_hat[j,],Sigma_b);
  }

  for (j in 1:J) {
    a[j] <- B[j,1];
    b[j] <- B[j,2];
  }

  for (i in 1:N)
    y_hat[i] <- a[county[i]] + b[county[i]] * x[i]

  y ~ normal(y_hat, sigma);
}
