# Leuk: Cox regression 
# URL of OpenBugs' implementation: 
#   http://www.openbugs.info/Examples/Leuk.html
data {
  int(0,) N;
  int(0,) NT;
  int(0,) obs_t[N]; 
  int(0,) t[NT + 1]; 
  int(0,) fail[N]; 
  real Z[N]; 
}

transformed data {
  int Y[N, NT];
  int dN[N, NT]; 
  real c;
  real r; 
  for(i in 1:N) {
    for(j in 1:NT) {
      Y[i, j] <- int_step(obs_t[i] - t[j] + .000000001);
      dN[i, j] <- Y[i, j] * fail[i] * int_step(t[j + 1] - obs_t[i] - .000000001);
    }
  }
  c <- 0.001; 
  r <- 0.1; 
}

parameters {
  real beta; 
  real(0,) dL0[NT]; 
} 

model {
  real zero; 
  zero <- 0;
  beta ~ normal(0, 1000);
  for(j in 1:NT) {
    dL0[j] ~ gamma(r * (t[j + 1] - t[j]) * c, c);
    for(i in 1:N) {
      // dN[i, j] ~ poisson(Y[i, j] * exp(beta * Z[i]) * dL0[j]); 
      lp__ <- lp__ + if_else(Y[i, j], poisson_log(dN[i, j], Y[i, j] * exp(beta * Z[i]) * dL0[j]), zero); 
      ## how about if_else(a, poisson_log(...), 0)? 
      // lp__ <- lp__ + if_else(Y[i, j], poisson_log(dN[i, j], Y[i, j] * exp(beta * Z[i]) * dL0[j]), 0); 

    }     
    // Survivor function = exp(-Integral{l0(u)du})^exp(beta*z)    
    // S.treat[j] <- pow(exp(-sum(dL0[1:j])), exp(beta * -0.5));
    // S.placebo[j] <- pow(exp(-sum(dL0[1:j])), exp(beta * 0.5));	
  }
}
