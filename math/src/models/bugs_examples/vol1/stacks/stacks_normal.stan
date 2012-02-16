# Stacks: robust regression and ridge regression 
#  http://mathstat.helsinki.fi/openbugs/Examples/Stacks.html

# stacks_normal.stan: normal error term 
# stacks_normal2.stan: normal error term with ridge specification on
# coefficients
# ------
# use `make normal' or `make normal2' to build/run the model 

# stacks_dexp.stan: real exponential error term 
# stacks_dexp2.stan: real exponential error term with ridge regression
# specification on coefficients 
# ------
# use `make dexp' or `make dexp2' to build/run the model 

# stacks_t.stan: student T  error term 
# stacks_t2.stan: student T error term with ridge regression specification on
#  coefficients 
# ------
# use `make t' or `make t2' to build/run the model 

data {
  int(0,) N; 
  int(0,) p; 
  real Y[N]; 
  real z[N, p]; 
  // matrix x[N, p]; 
} 

/*
// to standardize the x's 
transformed data {
  // matrix(N, p) z; 
  real z[N, p]; 
  real m[p];
  real s[p]; 
  for (j in 1:p) { 
    m[j] <- mean(col(x, j)); 
    s[j] <- sd(col(x, j)); 
  } 
  for (i in 1:N) for (j in 1:p) 
    z[i, j] <- (x[i, j] - m[j]) / s[j]; 
} 
*/


parameters {
  real beta0; 
  real beta[p]; 
  real(0,) sigmasq; 
} 

transformed parameters {
  real sigma; 
  sigma <- sqrt(sigmasq); 
} 


model {
  for (n in 1:N) Y[n] ~ normal(beta0 + beta[1] * z[n, 1] + beta[2] * z[n, 2] + beta[3] * z[n, 3], sigma); 
  beta0 ~ normal(0, 316); 
  beta ~ normal(0, 316); 
  sigmasq ~ inv_gamma(.001, .001); 
} 

