#ifndef STAN_MATH_PRIM_MAT_FUN_CSR_MATRIX_TIMES_VECTOR_HPP
#define STAN_MATH_PRIM_MAT_FUN_CSR_MATRIX_TIMES_VECTOR_HPP

#include <stan/math/prim/mat/fun/Eigen.hpp>
#include <stan/math/prim/mat/fun/dot_product.hpp>
#include <stan/math/prim/scal/err/check_size_match.hpp>
#include <stan/math/prim/scal/err/check_positive.hpp>
#include <stan/math/prim/mat/err/check_range.hpp>
#include <stan/math/prim/mat/err/check_ordered.hpp>
#include <boost/math/tools/promotion.hpp>
#include <vector>
#include <iostream>

namespace stan {

  namespace math {
    /** @defgroup csr_format Compressed Sparse Row matrix format.
     *  A compressed Sparse Row (CSR) sparse matrix is defined by four 
     *  component vectors labeled w, v, u, and z.  They are defined as:
     *    - w: the non-zero values in the sparse matrix.
     *    - v: column index for each value in w,  as a result this
     *      is the same length as w.
     *    - u: index of where each row starts in w,  length
     *      is equal to the number of rows plus one.  Last entry is
     *      one-past-the-end in w, following the Eigen spec.
     *    - z: number of non-zero entries in each row of w,  length is
     *      equal to the number of rows.
     *  Indexing is either zero-based or one-based depending on the value of
     *  stan::error_index::value.  Following the definition of the format in 
     *  Eigen, we allow for unused garbage values in w/v which are never read. 
     *  All indexing _internal_ to a given function is zero-based.
     *
     *  With only m/n/w/v/u/z in hand, it is possible to check all
     *  dimensions are sane _except_ the column dimension since it is
     *  implicit.  The error-checking strategy is to check all dimensions
     *  except the column dimension before any work is done inside a
     *  function.  The column index is checked as it is constructed and
     *  used for each entry.  If the column index is not needed it is
     *  not checked.  As a result indexing mistakes might produce non-sensical 
     *  operations but out-of-bounds indexing will be caught.
     *
     *  Except for possible garbage values in w/v/u, memory usage is
     *  calculated from the number of non-zero entries (NNZE) and the number of
     *  rows (NR):  2*NNZE + 2*NR + 1.
     */

    /** Return the multiplication of the sparse matrix (specified by
     * by values and indexing) by the specified dense vector.
     *
     * The sparse matrix X of dimension m by n is represented by the
     * vector w (of values), the integer array v (containing one-based
     * column index of each value), the integer array u (containing
     * one-based indexes of where each row starts in w), and the
     * integer array z (containing the number of non-zero entries in
     * each row of w).
     *
     * @tparam T1 Type of sparse matrix entries.
     * @tparam T2 Type of dense vector entries.
     * @param m Number of rows in matrix.
     * @param n Number of columns in matrix.
     * @param w Vector of non-zero values in matrix.
     * @param v Column index of each non-zero value, same
     *          length as w.
     * @param u Index of where each row starts in w, length equal to
     *          the number of rows plus one.
     * @param z Number of non-zero entries in each row of w, length equal to
     *          the number of rows..
     * @return Dense vector for the product.
     * @throw std::domain_error if m and n are not positive or are nan.
     * @throw std::domain_error if the implied sparse matrix and b are
     *                          not multiplicable.
     * @throw std::domain_error if m/n/w/v/u/z are not internally
     * consistent, as defined by the indexing scheme.  Extractors are
     * defined in Stan which guarantee a consistent set of m/n/w/v/u/z
     * for a given sparse matrix.
     */

    /** \addtogroup csr_format
     */

    template <typename T1, typename T2>
    inline
    Eigen::Matrix<typename boost::math::tools::promote_args<T1, T2>::type,
                  Eigen::Dynamic, 1>
    csr_matrix_times_vector(const int& m,
                            const int& n,
                            const Eigen::Matrix<T1, Eigen::Dynamic, 1>& w,
                            const std::vector<int>& v,
                            const std::vector<int>& u,
                            const std::vector<int>& z,
                            const Eigen::Matrix<T2, Eigen::Dynamic, 1>& b) {
      using stan::math::dot_product;
      using stan::math::check_positive;
      using stan::math::check_size_match;
      using stan::math::check_range;

      check_positive("csr_matrix_times_vector", "m", m);
      check_positive("csr_matrix_times_vector", "n", n);
      check_size_match("csr_matrix_times_vector", "n", n, "b", b.size());
      check_size_match("csr_matrix_times_vector", "m", m, "u", u.size()-1);
      check_size_match("csr_matrix_times_vector", "m", m, "z", z.size());
      check_size_match("csr_matrix_times_vector", "w", w.size(), "v", v.size());
      check_size_match("csr_matrix_times_vector", "u/z",
                       u[m-1] + z[m-1]-1, "v", v.size());
      for (unsigned int i=0; i < v.size(); ++i)
        check_range("csr_matrix_times_vector", "v[]", n, v[i]);

      typedef typename boost::math::tools::promote_args<T1, T2>::type
        fun_scalar_t;
      Eigen::Matrix<fun_scalar_t, Eigen::Dynamic, 1>  result(m);
      result.setZero();
      for (int row = 0; row < m; ++row) {
        int row_end_in_w = (u[row]-stan::error_index::value) + z[row];
        int i = 0;  // index into dot-product segment entries.
        Eigen::Matrix<fun_scalar_t, Eigen::Dynamic, 1> b_sub(z[row]);
        b_sub.setZero();
        for (int nze = u[row] - stan::error_index::value;
             nze < row_end_in_w; ++nze) {
          check_range("csr_matrix_times_vector", "j", n, v[nze]);
          b_sub(i) = b(v[nze]-stan::error_index::value);
          ++i;
        }  // loop skipped when z is zero.
        Eigen::Matrix<T1, Eigen::Dynamic, 1>
          w_sub(w.segment(u[row]-stan::error_index::value, z[row]));
        result(row) = dot_product(w_sub, b_sub);
      }
      return result;
    }

    /** @}*/   // end of csr_format group

  }

}

#endif
