#ifndef STAN__MATH__PRIM__MAT__FUN__APPEND_ROW_HPP
#define STAN__MATH__PRIM__MAT__FUN__APPEND_ROW_HPP

#include <stan/math/prim/mat/fun/Eigen.hpp>
#include <stan/math/prim/scal/meta/traits.hpp> //stan::return_type
#include <stan/math/prim/mat/err/check_size_match.hpp>
#include <vector>

namespace stan {
  namespace math {
    
    using Eigen::Dynamic;
    using Eigen::Matrix; 
    using std::vector;
    using stan::math::check_size_match;
       
    //matrix append_row(matrix, matrix)
    //matrix append_row(matrix, row_vector)
    //matrix append_row(row_vector, matrix)
    //matrix append_row(row_vector, row_vector)
    template <typename T1, typename T2, int R1, int C1, int R2, int C2>
    inline Matrix<typename return_type<T1, T2>::type, Dynamic, Dynamic>
    append_row(const Matrix<T1, R1, C1> & A,
               const Matrix<T2, R2, C2> & B) {
      int Arows = A.rows();
      int Brows = B.rows();
      int Acols = A.cols();
      int Bcols = B.cols();
      check_size_match("append_row",
                       "columns of A", Acols, 
                       "columns of B", Bcols);
      
      Matrix<typename return_type<T1, T2>::type, Dynamic, Dynamic>
        result(Arows + Brows, Acols);
      for (int j = 0; j < Acols; j++) {
        for (int i = 0; i < Arows; i++)
          result(i, j) = A(i, j);
        for (int i = Arows, k = 0; k < Brows; i++, k++)
          result(i, j) = B(k, j);
      }
      
      return result;
    }
       
    //matrix append_row(matrix, matrix)
    //matrix append_row(matrix, row_vector)
    //matrix append_row(row_vector, matrix)
    //matrix append_row(row_vector, row_vector)
    template <typename T, int R1, int C1, int R2, int C2>
    inline Matrix<T, Dynamic, Dynamic>
    append_row(const Matrix<T, R1, C1> & A,
               const Matrix<T, R2, C2> & B) {
      check_size_match("append_row",
                       "columns of A", A.cols(), 
                       "columns of B", B.cols());
      
      Matrix<T, Dynamic, Dynamic>
        result(A.rows() + B.rows(), A.cols());
      result << A, B;
      return result;
    }
       
    //vector append_row(vector, vector)
    template <typename T>
    inline Matrix<T, Dynamic, 1>
    append_row(const Matrix<T, Dynamic, 1> & A,
               const Matrix<T, Dynamic, 1> & B) {          
      Matrix<T, Dynamic, 1> result(A.size() + B.size());
      result << A, B;
      return result;
    }
    
  }
}
#endif
