functions {
  real poisson_ccdf_log(int n, real x) {
    return -x^2;
  }
}
parameters {
  real y;
}
model {
  y ~ normal(0, 1);
}
