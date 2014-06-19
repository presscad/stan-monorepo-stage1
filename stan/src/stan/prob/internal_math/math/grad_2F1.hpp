#ifndef __STAN__PROB__INTERNAL_MATH__MATH__GRAD_2F1_HPP__
#define __STAN__PROB__INTERNAL_MATH__MATH__GRAD_2F1_HPP__

#include <math.h>
#include <stan/agrad/fwd/functions/fabs.hpp>
#include <stan/agrad/fwd/operators.hpp>
#include <stan/agrad/rev/functions/fabs.hpp>
#include <stan/agrad/rev/operators.hpp>

namespace stan {
    
  namespace math {

    // Gradient of the hypergeometric function 2F1(a, b | c | z) with respect to a and c
    template<typename T>
    void grad2F1(T& gradA, T& gradC, T a, T b, T c, T z, T precision = 1e-6)
    {
          
      using stan::agrad::fabs;
      using std::fabs;

      gradA = 0;
      gradC = 0;
          
      T gradAold = 0;
      T gradCold = 0;
          
      int k = 0;
      T tDak = 1.0 / (a - 1);
          
      while( (fabs(tDak * (a + (k - 1)) ) > precision) || (k == 0) )
        {
              
          const T r = ( (a + k) / (c + k) ) * ( (b + k) / (T)(k + 1) ) * z;
          tDak = r * tDak * (a + (k - 1)) / (a + k);

          if(r == 0) break;
              
          gradAold = r * gradAold + tDak;
          gradCold = r * gradCold - tDak * ((a + k) / (c + k));
              
          gradA += gradAold;
          gradC += gradCold;
              
          ++k;
              
          if(k > 200) break;

        }
          
    }
      
      
  }

}

#endif
