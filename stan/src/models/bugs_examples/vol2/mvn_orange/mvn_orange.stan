// Orange Trees (Multi-variate normal) 
// http://www.openbugs.info/Examples/OtreesMVN.html
// refer to ../orange 

data {
  int(0,) K;
  int(0,) N;
  int x[N];
  double Y[K, N]; 
  cov_matrix(3) R;  // R should be positive definite: could cov_matrix be used? 
  // matrix(3, 3) R; 
  cov_matrix(3) mu_var_prior; 
  vector(3) mu_m_prior; 
}

parameters{
  double(0,) sigmasq;
  vector(3)  theta[K]; 
  vector(3)  thetamu; 
  cov_matrix(3) thetavar; 
} 

derived parameters {
  double sigma; 
  double phi[K, 3]; 
  sigma <- sqrt(sigmasq);
} 

model {
  sigmasq ~ inv_gamma(.001, .001); 
  for (k in 1:K) {
    phi[k, 1] <- exp(theta[k, 1]);
    phi[k, 2] <- exp(theta[k, 2]) - 1;
    phi[k, 3] <- -exp(theta[k, 3]);
    for (n in 1:N)  
      Y[k, n] ~ normal(phi[k, 1] / (1 + phi[k, 2] * exp(phi[k, 3] * x[n])), sigma); 

    theta[k] ~ multi_normal(thetamu, thetavar); 
    thetamu ~ multi_normal(mu_m_prior, mu_var_prior); 
    thetavar ~ inv_wishart(3, R); 
  }
}

