data {
  int<lower=0> N;
  int<lower=0> n[N];
  int<lower=0> r[N];
  real x[N];
}
transformed data {
  real mean_x;
  real centered_x[N];

  mean_x <- mean(x);
  for (i in 1:N)
    centered_x[i] <- x[i] - mean_x;
}
parameters {
  real alpha_star;
  real beta;
}
transformed parameters {
  real p[N];
  for (i in 1:N) 
    p[i] <- inv_cloglog(alpha_star + beta*centered_x[i]);
}


model {
  alpha_star ~ normal(0.0, 1.0E4);	
  beta ~ normal(0.0, 1.0E4);
  r ~ binomial(n, p);
}


generated quantities {
  real alpha; 
  real llike[N];
  real rhat[N];
  alpha <- alpha_star - beta*mean_x;              
  for (i in 1:N) {
    // log likelihood for sample i & saturated log-likelihood:
    llike[i]  <- r[i]*log(p[i]) + (n[i]-r[i])*log(1-p[i]);  
    // llike.sat[i] <- r[i]*log(r[i]/n[i]) + (n[i]-r[i])*log(1-r[i]/n[i]);
    rhat[i] <- p[i]*n[i];  // fitted values
  }
  //D <- 2 * (sum(llike.sat[]) - sum(llike[]));
} 

