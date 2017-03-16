#ifndef STAN_MATH_PRIM_MAT_FUN_TO_MATRIX_HPP
#define STAN_MATH_PRIM_MAT_FUN_TO_MATRIX_HPP

#include <stan/math/prim/mat/fun/Eigen.hpp>
#include <Eigen/Dense>
#include <vector>

namespace stan {
  namespace math {
    /**
     * Returns a matrix with dynamic dimensions constructed from
     * an Eigen matrix which is either
     * a row vector, column vector, or matrix.
     * The runtime dimensions will be the same as the input.
     *
     * @tparam T type of the scalar
     * @tparam R number of rows
     * @tparam C number of columns
     * @param x matrix
     * @return the matrix representation of the input
     */
    template <typename T, int R, int C>
    inline Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>
    to_matrix(const Eigen::Matrix<T, R, C>& x) {
      return x;
    }

    /**
     * Returns a matrix representation of a standard vector of Eigen
     * row vectors with the same dimensions and indexing order.
     *
     * @tparam T type of the scalar
     * @param x Eigen vector of vectors of scalar values
     * @return the matrix representation of the input
     */
    template <typename T>
    inline Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>
    to_matrix(const
              std::vector<Eigen::Matrix<T, 1, Eigen::Dynamic> >& x) {
      size_t rows = x.size();
      if (rows != 0) {
        size_t cols = x[0].size();
        Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>
          result(rows, cols);
        for (size_t i=0, ij=0; i < cols; i++)
          for (size_t j=0; j < rows; j++, ij++)
            result(ij) = x[j][i];
        return result;
      } else {
        return Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> (0, 0);
      }
    }

    /**
     * Returns a matrix representation of the standard vector of
     * standard vectors with the same dimensions and indexing order.
     *
     * @tparam T type of the scalar
     * @param x vector of vectors of scalar values
     * @return the matrix representation of the input
     */
    template <typename T>
    inline Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>
    to_matrix(const std::vector< std::vector<T> >& x) {
      size_t rows = x.size();
      if (rows != 0) {
        size_t cols = x[0].size();
        Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>
          result(rows, cols);
        for (size_t i=0, ij=0; i < cols; i++)
          for (size_t j=0; j < rows; j++, ij++)
            result(ij) = x[j][i];
        return result;
      } else {
        return Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> (0, 0);
      }
    }

    /**
     * Returns a matrix representation of a standard vector of
     * standard vectors of integers with the same dimensions and
     * indexing order.
     *
     * @param x vector of vectors of integer values
     * @return the matrix representation of the input,
     * ints promoted to doubles
     */
    inline Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>
    to_matrix(const std::vector< std::vector<int> >& x) {
      size_t rows = x.size();
      if (rows != 0) {
        size_t cols = x[0].size();
        Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>
          result(rows, cols);
        for (size_t i=0, ij=0; i < cols; i++)
          for (size_t j=0; j < rows; j++, ij++)
            result(ij) = x[j][i];
        return result;
      } else {
        return Eigen::Matrix<double, Eigen::Dynamic,
                             Eigen::Dynamic> (0, 0);
      }
    }
    
    /**
     * Returns a matrix representation of the vector in column-major
     * order with the specified number of rows and columns.
     *
     * @tparam T type of the scalar
     * @param x matrix
     * @param m rows
     * @param n columns
     * @return Reshaped inputted matrix
     * @throw <code>std::invalid_argument</code> if the sizes
     * do not match
     */
    template <typename T, int R, int C>
    inline Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>
    to_matrix(const Eigen::Matrix<T, R, C>& x, int m, int n) {
      static const char* fun = "to_matrix(matrix)";
      check_size_match(fun, "rows * columns", m * n, "vector size",
                       x.size());
      Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> y = x;
      y.resize(m, n);
      return y;
    }

    /**
     * Returns a matrix representation of the vector in column-major
     * order with the specified number of rows and columns.
     *
     * @tparam T type of the scalar
     * @param x vector of values
     * @param m rows
     * @param n columns
     * @return the matrix representation of the input
     * @throw <code>std::invalid_argument</code>
     * if the sizes do not match
     */
    template <typename T>
    inline Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>
    to_matrix(const std::vector<T>& x, int m, int n) {
      static const char* fun = "to_matrix(array)";
      check_size_match(fun, "rows * columns", m * n, "vector size",
                       x.size());
      return Eigen::Map<const
                        Eigen::Matrix<T, Eigen::Dynamic,
                                      Eigen::Dynamic> >(&x[0], m, n);
    }
   
    /**
     * Returns a matrix representation of the vector in column-major
     * order with the specified number of rows and columns.
     *
     * @param x vector of values
     * @param m rows
     * @param n columns
     * @return the matrix representation of the input
     * @throw <code>std::invalid_argument</code>
     * if the sizes do not match
     */
    inline Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>
    to_matrix(const std::vector<int>& x, int m, int n) {
      static const char* fun = "to_matrix(array)";
      int size = x.size();
      check_size_match(fun, "rows * columns", m * n,
                       "vector size", size);
      Eigen::Matrix<double,
                    Eigen::Dynamic, Eigen::Dynamic> result(m, n);
      double* datap = result.data();
      for (int i=0; i < size; i++)
        datap[i] = x[i];
      return result;
    }

    /**
     * Returns a matrix representation of the vector in column-major
     * order with the specified number of rows and columns.
     *
     * @tparam T type of the scalar
     * @param x matrix
     * @param m rows
     * @param n columns
     * @param cm column-major indicator:
     * if 1, output matrix is transversed in column-major order,
     * if 0, output matrix is transversed in row-major order,
     * otherwise function throws std::invalid_argument
     * @return Reshaped inputted matrix
     * @throw <code>std::invalid_argument</code>
     * if the sizes do not match
     */
    template <typename T, int R, int C>
    inline Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>
    to_matrix(const Eigen::Matrix<T, R, C>& x, int m, int n, int cm) {
      if (cm == 1)
        return to_matrix(x, m, n);
      else if (cm == 0) {
        check_size_match("to_matrix", "rows * columns", m * n,
                         "matrix size", x.size());
        Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>
          result(m, n);
        for (size_t i=0, ij=0; i < m; i++)
          for (size_t j=0; j < n; j++, ij++)
            result(i, j) = x(ij);
        return result;
      }
      else {
        invalid_argument("to_matrix", "cm", cm,
                         "column-major indicator",
                         "must equal 0 or 1");
        return Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> (0, 0);
      }
    }

    /**
     * Returns a matrix representation of the vector in column-major
     * order with the specified number of rows and columns.
     *
     * @tparam T type of the scalar
     * @param x vector of values
     * @param m rows
     * @param n columns
     * @param cm column-major indicator:
     * if 1, output matrix is transversed in column-major order,
     * if 0, output matrix is transversed in row-major order,
     * otherwise function throws std::invalid_argument
     * @return the matrix representation of the input
     * @throw <code>std::invalid_argument</code>
     * if the sizes do not match
     */
    template <typename T>
    inline
    Eigen::Matrix<typename 
      boost::math::tools::promote_args<T, double>::type,
      Eigen::Dynamic, Eigen::Dynamic>
    to_matrix(const std::vector<T>& x, int m, int n, int cm) {
      if (cm == 1)
        return to_matrix(x, m, n);
      else if (cm == 0) {
        check_size_match("to_matrix", "rows * columns", m * n,
                         "matrix size", x.size());
        Eigen::Matrix<typename
          boost::math::tools::promote_args<T, double>::type,
          Eigen::Dynamic, Eigen::Dynamic>
          result(m, n);
        for (size_t i=0, ij=0; i < m; i++)
          for (size_t j=0; j < n; j++, ij++)
            result(i, j) = x[ij];
        return result;
      }
      else {
        invalid_argument("to_matrix", "cm", cm,
                         "column-major indicator",
                         "must equal 0 or 1");
        return Eigen::Matrix<typename
                boost::math::tools::promote_args<T, double>::type,
                Eigen::Dynamic, Eigen::Dynamic> (0, 0);
      }
    }

  }
}
#endif
