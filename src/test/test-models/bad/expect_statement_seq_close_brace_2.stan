parameters {
  real y;
}
model {
  y ~ normal(0,1);
}
generated quantities {
  real z;
}

