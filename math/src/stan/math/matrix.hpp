#ifndef __STAN__MATH__MATRIX_H__
#define __STAN__MATH__MATRIX_H__

#include <stdexcept>
#include <vector>

#define EIGEN_DENSEBASE_PLUGIN "stan/math/EigenDenseBaseAddons.hpp"
#include <Eigen/Dense>


namespace stan {
  
  namespace math {

    /**
     * This is a traits structure for Eigen matrix types.
     *
     * @tparam T Underlying scalar type.
     */ 
    template<typename T>
    struct EigenType {

      /** Type of scalar. 
       */
      typedef T scalar;

      /**
       * Type of Eigen matrix.
       */
      typedef Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic>  matrix;

      /**
       * Type of Eigen column vector.
       */
      typedef Eigen::Matrix<T,Eigen::Dynamic,1>  vector;

      /**
       * Type of Eigen row vector.
       */
      typedef Eigen::Matrix<T,1,Eigen::Dynamic>  row_vector;

      /**
       * Type of Eigen diagonal matrix.
       */
      typedef Eigen::DiagonalMatrix<T,Eigen::Dynamic> diagonal_matrix;

      /**
       * Type of Eigen array shaped like a (column) vector.
       */
      typedef Eigen::Array<T,1,Eigen::Dynamic> array_vector;
      
      /**
       * Type of Eigen array shaped like a row vector.
       */
      typedef Eigen::Array<T,Eigen::Dynamic,1> array_row_vector;

      /**
       * Type of Eigen array shaped like a matrix.
       */
      typedef Eigen::Array<T,Eigen::Dynamic,Eigen::Dynamic> array_matrix;
    };      
    
    /**
     * Type for matrix of double values.
     */
    typedef EigenType<double>::matrix matrix_d;

    /**
     * Type for (column) vector of double values.
     */
    typedef EigenType<double>::vector vector_d;

    /**
     * Type for (row) vector of double values.
     */
    typedef EigenType<double>::row_vector row_vector_d;



    namespace {

      template <typename T>
      void resize(Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic>& x, 
                  const std::vector<size_t>& dims, 
                  size_t pos) {
        x.resize(dims[pos],dims[pos+1]);
      }

      template <typename T>
      void resize(Eigen::Matrix<T,Eigen::Dynamic,1>& x, 
                  const std::vector<size_t>& dims, 
                  size_t pos) {
        x.resize(dims[pos]);
      }

      template <typename T>
      void resize(Eigen::Matrix<T,1,Eigen::Dynamic>& x, 
                  const std::vector<size_t>& dims, 
                  size_t pos) {
        x.resize(dims[pos]);
      }


      void resize(double x, 
                  const std::vector<size_t>& dims, 
                  size_t pos) {
        // no-op
      }

      template <typename T>
      void resize(std::vector<T>& x, 
                  const std::vector<size_t>& dims, 
                  size_t pos) {
        x.resize(dims[pos]);
        ++pos;
        if (pos >= dims.size()) return; // skips lowest loop to scalar
        for (size_t i = 0; i < x.size(); ++i)
          resize(x[i],dims,pos);
      }

    }

    /**
     * Recursively resize the specified vector of vectors,
     * which must bottom out at scalar values, Eigen vectors
     * or Eigen matrices.
     *
     * @param x Array-like object to resize.
     * @param dims New dimensions.
     * @tparam T Type of object being resized.
     */
    template <typename T>
    inline void resize(T& x, std::vector<size_t> dims) {
      resize(x,dims,0U);
    }

    // polymorphic gets with bounds checking


    namespace {
      
      inline
      void check_range(size_t max,
                       size_t i, 
                       const std::string& msg,
                       size_t idx) {
        if (i < 1 || i > max) {
          std::stringstream s;
          s << "INDEX OPERATOR [] OUT OF BOUNDS"
            << "; index=" << i
            << "; lower bound=1"
            << "; upper bound=" << max
            << "; index position=" << idx
            << "; " << msg
            << std::endl;
          throw std::out_of_range(s.str());
        }
      }

    }

    /**
     * Return a reference to the value of the specified vector at the
     * specified base-one index.  If the index is out of range, throw
     * a <code>std::out_of_range</code> exception with the specified
     * error message and index indicated.
     *
     * @param x Vector from which to get a value.
     * @param i Index into vector plus 1.
     * @param error_msg Error message if the index is out of range.
     * @param idx Nested index level to report in error message if
     * the index is out of range.
     * @return Value of vector at <code>i - 1</code>
     * @tparam T type of value.
     */
    template <typename T>
    inline
    T& get_base1(std::vector<T>& x, 
                 size_t i, 
                 const std::string& error_msg,
                 size_t idx) {
      check_range(x.size(),i,error_msg,idx);
      return x[i - 1];
    }

    /**
     * Return a reference to the value of the specified vector at the
     * specified base-one indexes.  If an index is out of range, throw
     * a <code>std::out_of_range</code> exception with the specified
     * error message and index indicated.
     *
     * @param x Vector from which to get a value.
     * @param i1 First index plus 1.
     * @param i2 Second index plus 1.
     * @param error_msg Error message if an index is out of range.
     * @param idx Nested index level to report in error message if
     * the index is out of range.
     * @return Value of vector at indexes.
     * @tparam T type of value.
     */
    template <typename T>
    inline
    T& get_base1(std::vector<std::vector<T> >& x, 
                 size_t i1, 
                 size_t i2,
                 const std::string& error_msg,
                 size_t idx) {
      check_range(x.size(),i1,error_msg,idx);
      return get_base1(x[i1 - 1],i2,error_msg,idx+1);
    }

    /**
     * Return a reference to the value of the specified vector at the
     * specified base-one indexes.  If an index is out of range, throw
     * a <code>std::out_of_range</code> exception with the specified
     * error message and index indicated.
     *
     * @param x Vector from which to get a value.
     * @param i1 First index plus 1.
     * @param i2 Second index plus 1.
     * @param i3 Third index plus 1.
     * @param error_msg Error message if an index is out of range.
     * @param idx Nested index level to report in error message if
     * the index is out of range.
     * @return Value of vector at indexes.
     * @tparam T type of value.
     */
    template <typename T>
    inline
    T& get_base1(std::vector<std::vector<std::vector<T> > >& x, 
                 size_t i1, 
                 size_t i2,
                 size_t i3,
                 const std::string& error_msg,
                 size_t idx) {
      check_range(x.size(),i1,error_msg,idx);
      return get_base1(x[i1 - 1],i2,i3,error_msg,idx+1);
    }

    /**
     * Return a reference to the value of the specified vector at the
     * specified base-one indexes.  If an index is out of range, throw
     * a <code>std::out_of_range</code> exception with the specified
     * error message and index indicated.
     *
     * @param x Vector from which to get a value.
     * @param i1 First index plus 1.
     * @param i2 Second index plus 1.
     * @param i3 Third index plus 1.
     * @param i4 Fourth index plus 1.
     * @param error_msg Error message if an index is out of range.
     * @param idx Nested index level to report in error message if
     * the index is out of range.
     * @return Value of vector at indexes.
     * @tparam T type of value.
     */
    template <typename T>
    inline
    T& get_base1(std::vector<std::vector<std::vector<std::vector<T> > > >& x, 
                 size_t i1, 
                 size_t i2,
                 size_t i3,
                 size_t i4,
                 const std::string& error_msg,
                 size_t idx) {
      check_range(x.size(),i1,error_msg,idx);
      return get_base1(x[i1 - 1],i2,i3,i4,error_msg,idx+1);
    }

    /**
     * Return a reference to the value of the specified vector at the
     * specified base-one indexes.  If an index is out of range, throw
     * a <code>std::out_of_range</code> exception with the specified
     * error message and index indicated.
     *
     * @param x Vector from which to get a value.
     * @param i1 First index plus 1.
     * @param i2 Second index plus 1.
     * @param i3 Third index plus 1.
     * @param i4 Fourth index plus 1.
     * @param i5 Fifth index plus 1.
     * @param error_msg Error message if an index is out of range.
     * @param idx Nested index level to report in error message if
     * the index is out of range.
     * @return Value of vector at indexes.
     * @tparam T type of value.
     */
    template <typename T>
    inline
    T& get_base1(std::vector<std::vector<std::vector<std::vector<std::vector<T> > > > >& x, 
                 size_t i1, 
                 size_t i2,
                 size_t i3,
                 size_t i4,
                 size_t i5,
                 const std::string& error_msg,
                 size_t idx) {
      check_range(x.size(),i1,error_msg,idx);
      return get_base1(x[i1 - 1],i2,i3,i4,i5,error_msg,idx+1);
    }

    /**
     * Return a reference to the value of the specified vector at the
     * specified base-one indexes.  If an index is out of range, throw
     * a <code>std::out_of_range</code> exception with the specified
     * error message and index indicated.
     *
     * @param x Vector from which to get a value.
     * @param i1 First index plus 1.
     * @param i2 Second index plus 1.
     * @param i3 Third index plus 1.
     * @param i4 Fourth index plus 1.
     * @param i5 Fifth index plus 1.
     * @param i6 Sixth index plus 1.
     * @param error_msg Error message if an index is out of range.
     * @param idx Nested index level to report in error message if
     * the index is out of range.
     * @return Value of vector at indexes.
     * @tparam T type of value.
     */
    template <typename T>
    inline
    T& get_base1(std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<T> > > > > >& x, 
                 size_t i1, 
                 size_t i2,
                 size_t i3,
                 size_t i4,
                 size_t i5,
                 size_t i6,
                 const std::string& error_msg,
                 size_t idx) {
      check_range(x.size(),i1,error_msg,idx);
      return get_base1(x[i1 - 1],i2,i3,i4,i5,i6,error_msg,idx+1);
    }


    /**
     * Return a reference to the value of the specified vector at the
     * specified base-one indexes.  If an index is out of range, throw
     * a <code>std::out_of_range</code> exception with the specified
     * error message and index indicated.
     *
     * @param x Vector from which to get a value.
     * @param i1 First index plus 1.
     * @param i2 Second index plus 1.
     * @param i3 Third index plus 1.
     * @param i4 Fourth index plus 1.
     * @param i5 Fifth index plus 1.
     * @param i6 Sixth index plus 1.
     * @param i7 Seventh index plus 1.
     * @param error_msg Error message if an index is out of range.
     * @param idx Nested index level to report in error message if
     * the index is out of range.
     * @return Value of vector at indexes.
     * @tparam T type of value.
     */
    template <typename T>
    inline
    T& get_base1(std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<T> > > > > > >& x, 
                 size_t i1, 
                 size_t i2,
                 size_t i3,
                 size_t i4,
                 size_t i5,
                 size_t i6,
                 size_t i7,
                 const std::string& error_msg,
                 size_t idx) {
      check_range(x.size(),i1,error_msg,idx);
      return get_base1(x[i1 - 1],i2,i3,i4,i5,i6,i7,error_msg,idx+1);
    }


    /**
     * Return a reference to the value of the specified vector at the
     * specified base-one indexes.  If an index is out of range, throw
     * a <code>std::out_of_range</code> exception with the specified
     * error message and index indicated.
     *
     * @param x Vector from which to get a value.
     * @param i1 First index plus 1.
     * @param i2 Second index plus 1.
     * @param i3 Third index plus 1.
     * @param i4 Fourth index plus 1.
     * @param i5 Fifth index plus 1.
     * @param i6 Sixth index plus 1.
     * @param i7 Seventh index plus 1.
     * @param i8 Eigth index plus 1.
     * @param error_msg Error message if an index is out of range.
     * @param idx Nested index level to report in error message if
     * the index is out of range.
     * @return Value of vector at indexes.
     * @tparam T type of value.
     */
    template <typename T>
    inline
    T& get_base1(std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<T> > > > > > > >& x, 
                 size_t i1, 
                 size_t i2,
                 size_t i3,
                 size_t i4,
                 size_t i5,
                 size_t i6,
                 size_t i7,
                 size_t i8,
                 const std::string& error_msg,
                 size_t idx) {
      check_range(x.size(),i1,error_msg,idx);
      return get_base1(x[i1 - 1],i2,i3,i4,i5,i6,i7,i8,error_msg,idx+1);
    }



    /**
     * Return a copy of the row of the specified vector at the specified
     * base-one row index.  If the index is out of range, throw a
     * <code>std::out_of_range</code> exception with the specified
     * error message and index indicated.
     *
     * <b>Warning</b>:  Because a copy is involved, it is inefficient
     * to access element of matrices by first using this method
     * to get a row then using a second call to get the value at 
     a specified column.
     *
     * @param x Matrix from which to get a row
     * @param m Index into matrix plus 1.
     * @param error_msg Error message if the index is out of range.
     * @param idx Nested index level to report in error message if
     * the index is out of range.
     * @return Row of matrix at <code>i - 1</code>.
     * @tparam T type of value.
     */
    template <typename T>
    inline
    Eigen::Matrix<T,1,Eigen::Dynamic>
    get_base1(Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic>& x,
              size_t m,
              const std::string& error_msg,
              size_t idx) {
      check_range(x.rows(),m,error_msg,idx);
      return x.row(m - 1);
    }

    /**
     * Return a reference to the value of the specified matrix at the specified
     * base-one row and column indexes.  If either index is out of range,
     * throw a <code>std::out_of_range</code> exception with the
     * specified error message and index indicated.
     *
     * @param x Matrix from which to get a row
     * @param m Row index plus 1.
     * @param n Column index plus 1.
     * @param error_msg Error message if either index is out of range.
     * @param idx Nested index level to report in error message if
     * either index is out of range.
     * @return Value of matrix at row <code>m - 1</code> and column
     * <code>n - 1</code>.
     * @tparam T type of value.
     */
    template <typename T>
    inline
    T& get_base1(Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic>& x,
                 size_t m,
                 size_t n,
                 const std::string& error_msg,
                 size_t idx) {
      check_range(x.rows(),m,error_msg,idx);
      check_range(x.cols(),n,error_msg,idx + 1);
      return x(m - 1, n - 1);
    }

    /**
     * Return a reference to the value of the specified column vector
     * at the specified base-one index.  If the index is out of range,
     * throw a <code>std::out_of_range</code> exception with the
     * specified error message and index indicated.
     *
     * @param x Column vector from which to get a value.
     * @param m Row index plus 1.
     * @param error_msg Error message if the index is out of range.
     * @param idx Nested index level to report in error message if
     * the index is out of range.
     * @return Value of column vector at row <code>m - 1</code>.
     * @tparam T type of value.
     */
    template <typename T>
    inline
    T& get_base1(Eigen::Matrix<T,Eigen::Dynamic,1>& x,
                 size_t m,
                 const std::string& error_msg,
                 size_t idx) {
      check_range(x.size(),m,error_msg,idx);
      return x(m - 1);
      
    }

    /**
     * Return a reference to the value of the specified row vector
     * at the specified base-one index.  If the index is out of range,
     * throw a <code>std::out_of_range</code> exception with the
     * specified error message and index indicated.
     *
     * @param x Row vector from which to get a value.
     * @param n Column index plus 1.
     * @param error_msg Error message if the index is out of range.
     * @param idx Nested index level to report in error message if
     * the index is out of range.
     * @return Value of row vector at column <code>n - 1</code>.
     * @tparam T type of value.
     */
    template <typename T>
    inline
    T& get_base1(Eigen::Matrix<T,1,Eigen::Dynamic>& x,
                 size_t n,
                 const std::string& error_msg,
                 size_t idx) {
      check_range(x.size(),n,error_msg,idx);
      return x(n - 1);
    }


    // int returns

    /**
     * Return the number of rows in the specified 
     * column vector.
     * @param v Specified vector.
     * @return Number of rows in the vector.
     */
    inline size_t rows(const vector_d& v) {
      return v.size();
    }
    /**
     * Return the number of rows in the specified 
     * row vector.  The return value is always 1.
     * @param rv Specified vector.
     * @return Number of rows in the vector.
     */
    inline size_t rows(const row_vector_d& rv) {
      return 1;
    }
    /**
     * Return the number of rows in the specified matrix.
     * @param m Specified matrix.
     * @return Number of rows in the vector.
     * 
     */
    inline size_t rows(const matrix_d& m) {
      return m.rows();
    }

    /**
     * Return the number of columns in the specified
     * column vector.  The return value is always 1.
     * @param v Specified vector.
     * @return Number of columns in the vector.
     */
    inline size_t cols(const vector_d& v) {
      return 1;
    }
    /**
     * Return the number of columns in the specified
     * row vector.  
     * @param rv Specified vector.
     * @return Number of columns in the vector.
     */
    inline size_t cols(const row_vector_d& rv) {
      return rv.size();
    }
    /**
     * Return the number of columns in the specified matrix.
     * @param m Specified matrix.
     * @return Number of columns in the matrix.
     */
    inline size_t cols(const matrix_d& m) {
      return m.cols();
    }
    

    // scalar returns

    /**
     * Returns the determinant of the specified
     * square matrix.
     * @param m Specified matrix.
     * @return Determinant of the matrix.
     */
    inline double determinant(const matrix_d& m) {
      return m.determinant();
    }

    /**
     * Returns the dot product of the specified column vectors.
     * @param v1 First vector.
     * @param v2 Second vector.
     * @return Dot product of the vectors.
     */
    inline double dot_product(vector_d v1, vector_d v2) {
      return v1.dot(v2);
    }
    /**
     * Returns the dot product of the specified column vector
     * and row vector.
     * @param v First vector.
     * @param rv Second vector.
     * @return Dot product of the vectors.
     */
    inline double dot_product(const vector_d& v, const row_vector_d& rv) {
      return v.dot(rv);
    }
    /**
     * Returns the dot product of the specified row vector
     * and column vector.
     * @param rv First vector.
     * @param v Second vector.
     * @return Dot product of the vectors.
     */
    inline double dot_product(const row_vector_d& rv, const vector_d& v) {
      return rv.dot(v);
    }
    /**
     * Returns the dot product of the specified row vectors.
     * @param rv1 First vector.
     * @param rv2 Second vector.
     * @return Dot product of the vectors.
     */
    inline double dot_product(const row_vector_d& rv1, 
                              const row_vector_d& rv2) {
      return rv1.dot(rv2);
    }

    /**
     * Returns the minimum coefficient in the specified
     * column vector.
     * @param v Specified vector.
     * @return Minimum coefficient value in the vector.
     */
    inline double min(const vector_d& v) {
      return v.minCoeff();
    }
    /**
     * Returns the minimum coefficient in the specified
     * row vector.
     * @param rv Specified vector.
     * @return Minimum coefficient value in the vector.
     */
    inline double min(const row_vector_d& rv) {
      return rv.minCoeff();
    }
    /**
     * Returns the minimum coefficient in the specified
     * matrix.
     * @param m Specified matrix.
     * @return Minimum coefficient value in the matrix.
     */
    inline double min(const matrix_d& m) {
      return m.minCoeff();
    }

    /**
     * Returns the maximum coefficient in the specified
     * column vector.
     * @param v Specified vector.
     * @return Maximum coefficient value in the vector.
     */
    inline double max(const vector_d& v) {
      return v.maxCoeff();
    }
    /**
     * Returns the maximum coefficient in the specified
     * row vector.
     * @param rv Specified vector.
     * @return Maximum coefficient value in the vector.
     */
    inline double max(const row_vector_d& rv) {
      return rv.maxCoeff();
    }
    /**
     * Returns the maximum coefficient in the specified
     * matrix.
     * @param m Specified matrix.
     * @return Maximum coefficient value in the matrix.
     */
    inline double max(const matrix_d& m) {
      return m.maxCoeff();
    }

    /**
     * Returns the sample mean (i.e., average) of the coefficients
     * in the specified standard vector.
     * @param v Specified vector.
     * @return Sample mean of vector coefficients.
     */
    template <typename T>
    inline double mean(const std::vector<T>& v) {
      double sum(0);
      for (size_t i = 0; i < v.size(); ++i)
        sum += v[i];
      return sum / v.size();
    }

    /**
     * Returns the sample mean (i.e., average) of the coefficients
     * in the specified column vector.
     * @param v Specified vector.
     * @return Sample mean of vector coefficients.
     */
    inline double mean(const vector_d& v) {
      return v.mean();
    }
    /**
     * Returns the sample mean (i.e., average) of the coefficients
     * in the specified row vector.
     * @param rv Specified vector.
     * @return Sample mean of vector coefficients.
     */
    inline double mean(const row_vector_d& rv) {
      return rv.mean();
    }
    /**
     * Returns the sample mean (i.e., average) of the coefficients
     * in the specified matrix.
     * @param m Specified matrix.
     * @return Sample mean of matrix coefficients.
     */
    inline double mean(const matrix_d& m) {
      return m.mean();
    }

    /**
     * Returns the sample variance (divide by length - 1) of the
     * coefficients in the specified column vector.
     * @param v Specified vector.
     * @return Sample variance of vector.
     */
    template <typename T>
    inline double variance(const std::vector<T>& v) {
      T v_mean = mean(v);
      T sum_sq_diff = 0;
      for (int i = 0; i < v.size(); ++i) {
        T diff = v[i] - v_mean;
        sum_sq_diff += diff * diff;
      }
      return sum_sq_diff / (v.size() - 1);
    }

    /**
     * Returns the sample variance (divide by length - 1) of the
     * coefficients in the specified column vector.
     * @param v Specified vector.
     * @return Sample variance of vector.
     */
    inline double variance(const vector_d& v) {
      double mean = v.mean();
      double sum_sq_diff = 0;
      for (int i = 0; i < v.size(); ++i) {
        double diff = v[i] - mean;
        sum_sq_diff += diff * diff;
      }
      return sum_sq_diff / (v.size() - 1);
    }
    /**
     * Returns the sample variance (divide by length - 1) of the
     * coefficients in the specified row vector.
     * @param rv Specified vector.
     * @return Sample variance of vector.
     */
    inline double variance(const row_vector_d& rv) {
      double mean = rv.mean();
      double sum_sq_diff = 0;
      for (int i = 0; i < rv.size(); ++i) {
        double diff = rv[i] - mean;
        sum_sq_diff += diff * diff;
      }
      return sum_sq_diff / (rv.size() - 1);
    }
    /**
     * Returns the sample variance (divide by length - 1) of the
     * coefficients in the specified matrix.
     * @param m Specified matrix.
     * @return Sample variance of matrix.
     */
    inline double variance(const matrix_d& m) {
      double mean = m.mean();
      double sum_sq_diff = 0;
      for (int j = 0; j < m.cols(); ++j) { 
        for (int i = 0; i < m.rows(); ++i) {
          double diff = m(i,j) - mean;
          sum_sq_diff += diff * diff;
        }
      }
      return sum_sq_diff / (m.size() - 1);
    }

    /**
     * Returns the unbiased sample standard deviation of the
     * coefficients in the specified column vector.
     * @param v Specified vector.
     * @return Sample variance of vector.
     */
    template <typename T>
    inline double sd(const std::vector<T>& v) {
      return sqrt(variance(v));
    }

    /**
     * Returns the unbiased sample standard deviation of the
     * coefficients in the specified column vector.
     * @param v Specified vector.
     * @return Sample variance of vector.
     */
    inline double sd(const vector_d& v) {
      return sqrt(variance(v));
    }
    /**
     * Returns the unbiased sample standard deviation of the
     * coefficients in the specified row vector.
     * @param rv Specified vector.
     * @return Sample variance of vector.
     */
    inline double sd(const row_vector_d& rv) {
      return sqrt(variance(rv));
    }
    /**
     * Returns the unbiased sample standard deviation of the
     * coefficients in the specified matrix.
     * @param m Specified matrix.
     * @return Sample variance of matrix.
     */
    inline double sd(const matrix_d& m) {
      return sqrt(variance(m));
    }

    /**
     * Return the sum of the values in the specified
     * standard vector.
     *
     * @param xs Standard vector to sum.
     * @return Sum of elements.
     * @tparam T Type of elements summed.
     */
    template <typename T>
    inline T sum(const std::vector<T>& xs) {
      T sum(0);
      for (size_t i = 0; i < xs.size(); ++i)
        sum += xs[i];
      return sum;
    }

    /**
     * Returns the sum of the coefficients of the specified
     * column vector.
     * @param v Specified vector.
     * @return Sum of coefficients of vector.
     */
    inline double sum(const vector_d& v) {
      return v.sum();
    }
    /**
     * Returns the sum of the coefficients of the specified
     * row vector.
     * @param rv Specified vector.
     * @return Sum of coefficients of vector.
     */
    inline double sum(const row_vector_d& rv) {
      return rv.sum();
    }
    /**
     * Returns the sum of the coefficients of the specified
     * matrix
     * @param m Specified matrix.
     * @return Sum of coefficients of matrix.
     */
    inline double sum(const matrix_d& m) {
      return m.sum();
    }

    
    /**
     * Returns the product of the coefficients of the specified
     * column vector.
     * @param v Specified vector.
     * @return Product of coefficients of vector.
     */
    inline double prod(const vector_d& v) {
      return v.prod();
    }
    /**
     * Returns the product of the coefficients of the specified
     * row vector.
     * @param rv Specified vector.
     * @return Product of coefficients of vector.
     */
    inline double prod(const row_vector_d& rv) {
      return rv.prod();
    }
    /**
     * Returns the product of the coefficients of the specified
     * matrix.
     * @param m Specified matrix.
     * @return Product of coefficients of matrix.
     */
    inline double prod(const matrix_d& m) {
      return m.prod();
    }

    /**
     * Returns the trace of the specified matrix.  The trace
     * is defined as the sum of the elements on the diagonal.
     * The matrix is not required to be square.
     *
     * @param m Specified matrix.
     * @return Trace of the matrix.
     */
    inline double trace(const matrix_d& m) {
      return m.trace();
    }


    // vector and matrix returns

    /**
     * Return the sum of the specified column vectors.
     * The two vectors must have the same size.
     * @param v1 First vector.
     * @param v2 Second vector.
     * @return Sum of the two vectors.
     * @throw std::invalid_argument if v1 and v2 are not the same size.
     */
    inline vector_d add(const vector_d& v1, vector_d& v2) {
      if (v1.size() != v2.size()) 
        throw std::invalid_argument ("v1.size() != v2.size()");
      return v1 + v2;
    }
    /**
     * Return the sum of the specified row vectors.  The
     * two vectors must have the same size.
     * @param rv1 First vector.
     * @param rv2 Second vector.
     * @return Sum of the two vectors.
     * @throw std::invalid_argument if rv1 and rv2 are not the same size.
     */
    inline row_vector_d add(const row_vector_d& rv1, 
                            const row_vector_d& rv2) {
      if (rv1.size() != rv2.size()) 
        throw std::invalid_argument ("rv1.size() != rv2.size()");
      return rv1 + rv2;
    }
    /**
     * Return the sum of the specified matrices.  The two matrices
     * must have the same dimensions.
     * @param m1 First matrix.
     * @param m2 Second matrix.
     * @return Sum of the two vectors.
     * @throw std::invalid_argument if m1 and m2 are not the same size.
     */
    inline matrix_d add(const matrix_d& m1, const matrix_d& m2) {
      if (m1.rows() != m2.rows() || m1.cols() != m2.cols())
        throw std::invalid_argument ("dimensions of m1 and m2 do not match");
      return m1 + m2;
    }

    /**
     * Return the element-wise logarithm of the matrix or vector.
     *
     * @param m The matrix or vector.
     * @return ret(i,j) = log(m(i,j))
     */
    template<int Rows, int Cols>
    inline Eigen::Matrix<double,Rows,Cols> log(const Eigen::Matrix<double,Rows,Cols>& m) {
      return m.array().log().matrix();
    }

    /**
     * Return the element-wise exponentiation of the matrix or vector.
     *
     * @param m The matrix or vector.
     * @return ret(i,j) = exp(m(i,j))
     */
    template<int Rows, int Cols>
    inline Eigen::Matrix<double,Rows,Cols> exp(const Eigen::Matrix<double,Rows,Cols>& m) {
      return m.array().exp().matrix();
    }

    /**
     * Return the sum of a matrix or vector and a scalar.
     * @param m Matrix or vector.
     * @param c Scalar.
     * @return The matrix or vector plus the scalar.
     */
    template<int Rows, int Cols>
    inline Eigen::Matrix<double,Rows,Cols> add(const Eigen::Matrix<double,Rows,Cols>& m, const double& c) {
      return (m.array() + c).matrix();
    }
    /**
     * Return the sum of a scalar and a matrix or vector.
     * @param c Scalar.
     * @param m Matrix or vector.
     * @return Scalar plus the matrix or vector.
     */
    template<int Rows, int Cols>
    inline Eigen::Matrix<double,Rows,Cols> add(const double& c, const Eigen::Matrix<double,Rows,Cols>& m) {
      return (c + m.array()).matrix();
    }

    /**
     * Return the difference between the first specified column vector
     * and the second.  The two vectors must have the same size.
     * @param v1 First vector.
     * @param v2 Second vector.
     * @return First vector minus the second vector.
     * @throw std::invalid_argument if v1 and v2 are not the same size.
     */
    inline vector_d subtract(const vector_d& v1, const vector_d& v2) {
      if (v1.size() != v2.size())
        throw std::invalid_argument ("v1.size() != v2.size()");
      return v1 - v2;
    }
    /**
     * Return the difference between the first specified row vector and
     * the second.  The two vectors must have the same size.
     * @param rv1 First vector.
     * @param rv2 Second vector.
     * @return First vector minus the second vector.
     * @throw std::invalid_argument if rv1 and rv2 are not the same size.
     */
    inline row_vector_d subtract(const row_vector_d& rv1,
                                 const row_vector_d& rv2) {
      if (rv1.size() != rv2.size())
        throw std::invalid_argument ("rv1.size() != rv2.size()");
      return rv1 - rv2;
    }
    /**
     * Return the difference between the first specified matrix and
     * the second.  The two matrices must have the same dimensions.
     * @param m1 First matrix.
     * @param m2 Second matrix.
     * @return First matrix minus the second matrix.
     * @throw std::invalid_argument if m1 and m2 are not the same size.
     */
    inline matrix_d subtract(const matrix_d& m1, const matrix_d& m2) {
      if (m1.rows() != m2.rows() || m1.cols() != m2.cols())
        throw std::invalid_argument ("dimensions of m1 and m2 do not match");
      return m1 - m2;
    }

    /**
     * Return the difference between a matrix or vector and a scalar.
     * @param m Matrix or vector.
     * @param c Scalar.
     * @return The matrix or vector minus the scalar.
     */
    template<int Rows, int Cols>
    inline Eigen::Matrix<double,Rows,Cols> subtract(const Eigen::Matrix<double,Rows,Cols>& m, double c) {
      return (m.array() - c).matrix();
    }
    /**
     * Return the difference between a scalar and a matrix or vector.
     * @param c Scalar.
     * @param m Matrix or vector.
     * @return Scalar minus the matrix or vector.
     */
    template<int Rows, int Cols>
    inline Eigen::Matrix<double,Rows,Cols> subtract(double c, const Eigen::Matrix<double,Rows,Cols>& m) {
      return (c - m.array()).matrix();
    }

    /**
     * Return the negation of the specified column vector.  The result
     * is the same as multiplying by the scalar <code>-1</code>.
     * @param v Specified vector.  
     * @return The negation of the vector.
     */
    inline vector_d minus(const vector_d& v) {
      return -v;
    }
    /**
     * Return the negation of the specified row vector.  The result is
     * the same as multiplying by the scalar <code>-1</code>.
     * @param rv Specified vector.
     * @return The negation of the vector.
     */
    inline row_vector_d minus(const row_vector_d& rv) {
      return -rv;
    }
    /**
     * Return the negation of the specified matrix.  The result is the same
     * as multiplying by the scalar <code>-1</code>.
     * @param m Specified matrix.
     * @return The negation of the matrix.
     */
    inline matrix_d minus(const matrix_d& m) {
      return -m;
    }

    /**
     * Return the division of the specified column vector by
     * the specified scalar.
     * @param v Specified vector.
     * @param c Specified scalar.
     * @return Vector divided by the scalar.
     */
    inline vector_d divide(const vector_d& v, double c) {
      return v / c;
    }
    /**
     * Return the division of the specified row vector by
     * the specified scalar.
     * @param rv Specified vector.
     * @param c Specified scalar.
     * @return Vector divided by the scalar.
     */
    inline row_vector_d divide(const row_vector_d& rv, double c) {
      return rv / c;
    }
    /**
     * Return the division of the specified matrix by the specified
     * scalar.
     * @param m Specified matrix.
     * @param c Specified scalar.
     * @return Matrix divided by the scalar.
     */
    inline matrix_d divide(const matrix_d& m, double c) {
      return m / c;
    }

    /**
     * Return the element-wise product of the specified vectors.
     * @param v1 First vector.
     * @param v2 Second vector.
     * @return Elementwise product of the vectors.
     */
    inline vector_d elt_multiply(const vector_d& v1, const vector_d& v2) {
      if (v1.size() != v2.size()) {
        std::stringstream msg;
        msg << "vectors must have same dimensions, v1.size()=" << v1.size()
            << ", v2.size()=" << v2.size() << std::endl;
        throw std::domain_error(msg.str());
      }
      vector_d prod(v1.size());
      for (int i = 0; i < v1.size(); ++i)
        prod(i) = v1(i) * v2(i);
      return prod;
    }
    /**
     * Return the element-wise product of the specified row vectors.
     * @param v1 First row vector.
     * @param v2 Second row vector.
     * @return Elementwise product of the vectors.
     */
    inline vector_d elt_multiply(const row_vector_d& v1, const row_vector_d& v2) {
      if (v1.size() != v2.size()) {
        std::stringstream msg;
        msg << "vectors must have same dimensions, v1.size()=" << v1.size()
            << ", v2.size()=" << v2.size() << std::endl;
        throw std::domain_error(msg.str());
      }
      row_vector_d prod(v1.size());
      for (int i = 0; i < v1.size(); ++i)
        prod(i) = v1(i) * v2(i);
      return prod;
    }
    /**
     * Return the element-wise product of the specified matrices.
     * @param m1 First matrix.
     * @param m2 Second matrix.
     * @return Elementwise product of the matrices.
     */
    inline matrix_d elt_multiply(const matrix_d& m1, const matrix_d& m2) {
      if (m1.rows() != m2.rows()
          || m1.cols() != m2.cols()) {
        std::stringstream msg;
        msg << "vectors must have same dimensions"
          << "; m1.rows()=" << m1.rows() 
          << ", m2.rows()=" << m2.rows()
          << ", m1.cols()=" << m1.cols()
          << ", m2.cols()=" << m2.cols()
          << std::endl;
          throw std::domain_error(msg.str());
      }
      matrix_d prod(m1.rows(),m1.cols());
      for (int j = 0; j < m1.cols(); ++j)
        for (int i = 0; i < m1.rows(); ++i)
          prod(i,j) = m1(i,j) * m2(i,j);
      return prod;
    }


    /**
     * Return the element-wise divsion of the specified vectors.
     * @param v1 First vector.
     * @param v2 Second vector.
     * @return Elementwise division of the vectors.
     */
    inline vector_d elt_divide(const vector_d& v1, const vector_d& v2) {
      if (v1.size() != v2.size()) {
        std::stringstream msg;
        msg << "require vectors to be same size for element-wise division;"
            << " found v1.size()=" << v1.size()
            << ", v2.size()=" << v2.size()
            << std::endl;
        throw std::domain_error(msg.str());
      }
      vector_d prod(v1.size());
      for (int i = 0; i < v1.size(); ++i)
        prod(i) = v1(i) / v2(i);
      return prod;
    }
    /**
     * Return the element-wise division of the specified row vectors.
     * @param v1 First row vector.
     * @param v2 Second row vector.
     * @return Elementwise division of the vectors.
     */
    inline vector_d elt_divide(const row_vector_d& v1, const row_vector_d& v2) {
      if (v1.size() != v2.size()) {
        std::stringstream msg;
        msg << "require vectors to be same size for element-wise division;"
            << " found v1.size()=" << v1.size()
            << ", v2.size()=" << v2.size()
            << std::endl;
        throw std::domain_error(msg.str());
      }
      row_vector_d prod(v1.size());
      for (int i = 0; i < v1.size(); ++i)
        prod(i) = v1(i) / v2(i);
      return prod;
    }
    /**
     * Return the element-wise division of the specified matrices.
     * @param m1 First matrix.
     * @param m2 Second matrix.
     * @return Elementwise division of the matrices.
     */
    inline matrix_d elt_divide(const matrix_d& m1, const matrix_d& m2) {
      if (m1.rows() != m2.rows() 
          || m1.cols() != m2.cols()) {
        std::stringstream msg;
        msg << "require matrices to be same dimensions for element-wise division;"
            << " found m1.rows()=" << m1.rows() << ", m1.cols()=" << m1.cols()
            << "; m2.rows()=" << m2.rows() << ", m2.cols()=" << m2.cols()
            << std::endl;
        throw std::domain_error(msg.str());

      }
      matrix_d prod(m1.rows(),m1.cols());
      for (int j = 0; j < m2.cols(); ++j)
        for (int i = 0; i < m1.rows(); ++i)
          prod(i,j) = m1(i,j) / m2(i,j);
      return prod;
    }

    /**
     * Return the product of the of the specified column
     * vector and specified scalar.
     * @param v Specified vector.
     * @param c Specified scalar.
     * @return Product of vector and scalar.
     */
    inline vector_d multiply(const vector_d& v, double c) {
      return c * v;
    }
    /**
     * Return the product of the of the specified row
     * vector and specified scalar.
     * @param rv Specified vector.
     * @param c Specified scalar.
     * @return Product of vector and scalar.
     */
    inline row_vector_d multiply(const row_vector_d& rv, double c) {
      return c * rv;
    }
    /**
     * Return the product of the of the specified matrix
     * and specified scalar.
     * @param m Matrix.
     * @param c Scalar.
     * @return Product of matrix and scalar.
     */
    inline matrix_d multiply(const matrix_d& m, double c) {
      return c * m;
    }
    /**
     * Return the scalar product of the specified row vector and
     * specified column vector.  The return is the same as the dot
     * product.  The two vectors must be the same size.
     * @param rv Row vector.
     * @param v Column vector.
     * @return Scalar result of multiplying row vector by column vector.
     * @throw std::invalid_argument if rv and v are not the same size.
     */
    inline double multiply(const row_vector_d& rv, const vector_d& v) {
      if (rv.size() != v.size()) 
        throw std::invalid_argument ("rv.size() != v.size()");
      return rv.dot(v);
    }
    /**
     * Return the product of the specified column vector
     * and specified row vector.  The two vectors may be of any size.
     * @param v Column vector.
     * @param rv Row vector.
     * @return Product of column vector and row vector.
     */
    inline matrix_d multiply(const vector_d& v, const row_vector_d& rv) {
      return v * rv;
    }
    /**
     * Return the product of the specified matrix and
     * column vector.  The number of cols of the matrix must be
     * the same as the size of the vector.
     * @param m Matrix.
     * @param v Column vector.
     * @return Product of matrix and vector.
     * @throw std::invalid_argument if number of columns of the matrix
     *    is not the same size as the vector.
     */
    inline vector_d multiply(const matrix_d& m, const vector_d& v) {
      if (m.cols() != v.size())
        throw std::invalid_argument ("m.cols() != v.size()");
      return m * v;
    }
    /**
     * Return the product of the specifieid row vector and specified
     * matrix.  The number of rows of the matrix must be the same
     * as the size of the vector.
     * @param rv Row vector.
     * @param m Matrix.
     * @return Product of vector and matrix.
     * @throw std::invalid_argument if size of the row vector is not the
     *    number of rows of the matrix.
     */
    inline row_vector_d multiply(const row_vector_d& rv, const matrix_d& m) {
      if (rv.size() != m.rows())
        throw std::invalid_argument ("rv.size() != m.rows()");
      return rv * m;
    }
    /**
     * Return the product of the specified matrices.  The number of
     * columns in the first matrix must be the same as the number of rows
     * in the second matrix.
     * @param m1 First matrix.
     * @param m2 Second matrix.
     * @return The product of the first and second matrices.
     * @throw std::invalid_argument if the number of columns of m1 does not match
     *   the number of rows of m2.
     */
    inline matrix_d multiply(const matrix_d& m1, const matrix_d& m2) {
      if (m1.cols() != m2.rows())
        throw std::invalid_argument ("m1.cols() != m2.rows()");
      return m1 * m2;
    }

    /**
     * Return the product of the specified scalar and vector.
     * @param c Scalar.
     * @param v Vector.
     * @return Product of scalar and vector.
     */
    inline vector_d multiply(double c, const vector_d& v) {
      return c * v;
    }
    /**
     * Return the product of the specified scalar and row vector.
     * @param c Scalar.
     * @param rv Row vector.
     * @return Product of scalar and row vector.
     */
    inline row_vector_d multiply(double c, const row_vector_d& rv) {
      return c * rv;
    }
    /**
     * Return the product of the specified scalar and matrix.
     * @param c Scalar.
     * @param m Matrix
     * @return Product of scalar and matrix.
     */
    inline matrix_d multiply(double c, const matrix_d& m) {
      return c * m;
    }



    /**
     * Return the specified row of the specified matrix, using
     * start-at-1 indexing.  
     *
     * This is equivalent to calling <code>m.row(i - 1)</code> and
     * assigning the resulting template expression to a row vector.
     * 
     * @param m Matrix.
     * @param i Row index.
     * @return Specified row of the matrix.
     */
    inline row_vector_d row(const matrix_d& m, size_t i) {
      return m.row(i - 1);
    }

    /**
     * Return the specified column of the specified matrix
     * using start-at-1 indexing.
     *
     * This is equivalent to calling <code>m.col(i - 1)</code> and
     * assigning the resulting template expression to a column vector.
     * 
     * @param m Matrix.
     * @param j Column index.
     * @return Specified column of the matrix.
     */
    inline vector_d col(const matrix_d& m, size_t j) {
      return m.col(j - 1);
    }

    /**
     * Return a column vector of the diagonal elements of the
     * specified matrix.  The matrix is not required to be square.
     * @param m Specified matrix.  
     * @return Diagonal of the matrix.
     */
    inline vector_d diagonal(const matrix_d& m) {
      return m.diagonal();
    }

    /**
     * Return a square diagonal matrix with the specified vector of
     * coefficients as the diagonal values.
     * @param v Specified vector.
     * @return Diagonal matrix with vector as diagonal values.
     */
    inline matrix_d diag_matrix(const vector_d& v) {
      return v.asDiagonal();
    }

    /**
     * Return the transposition of the specified column
     * vector.
     * @param v Specified vector.
     * @return Transpose of the vector.
     */
    inline row_vector_d transpose(const vector_d& v) {
      return v.transpose();
    }
    /**
     * Return the transposition of the specified row
     * vector.
     * @param rv Specified vector.
     * @return Transpose of the vector.
     */
    inline vector_d transpose(const row_vector_d& rv) {
      return rv.transpose();
    }
    /**
     * Return the transposition of the specified matrix.
     * @param m Specified matrix.
     * @return Transpose of the matrix.
     */
    inline matrix_d transpose(const matrix_d& m) {
      return m.transpose();
    }

    /**
     * Returns the inverse of the specified matrix.
     * @param m Specified matrix.
     * @return Inverse of the matrix.
     */
    inline matrix_d inverse(const matrix_d& m) {
      return m.inverse();
    }

    /**
     * Return the real component of the eigenvalues of the specified
     * matrix in descending order of magnitude.
     * <p>See <code>eigen_decompose()</code> for more information.
     * @param m Specified matrix.
     * @return Eigenvalues of matrix.
     */
    inline vector_d eigenvalues(const matrix_d& m) {
      // false == no vectors
      Eigen::EigenSolver<matrix_d> solver(m,false);
      // FIXME: test imag() all 0?
      return solver.eigenvalues().real();
    }

    /**
     * Return a matrix whose columns are the real components of the
     * eigenvectors of the specified matrix.
     * <p>See <code>eigen_decompose()</code> for more information.
     * @param m Specified matrix.
     * @return Eigenvectors of matrix.
     */
    inline matrix_d eigenvectors(const matrix_d& m) {
      Eigen::EigenSolver<matrix_d> solver(m);
      return solver.eigenvectors().real();
    }
    /**
     * Assign the real components of the eigenvalues and eigenvectors
     * of the specified matrix to the specified references.
     * <p>Given an input matrix \f$A\f$, the
     * eigenvalues will be found in \f$D\f$ in descending order of
     * magnitude.  The eigenvectors will be written into
     * the columns of \f$V\f$.  If \f$A\f$ is invertible, then
     * <p>\f$A = V \times \mbox{\rm diag}(D) \times V^{-1}\f$, where
     $ \f$\mbox{\rm diag}(D)\f$ is the square diagonal matrix with
     * diagonal elements \f$D\f$ and \f$V^{-1}\f$ is the inverse of
     * \f$V\f$.
     * @param m Specified matrix.
     * @param eigenvalues Column vector reference into which
     * eigenvalues are written.
     * @param eigenvectors Matrix reference into which eigenvectors
     * are written.
     */
    inline void eigen_decompose(const matrix_d& m,
                                vector_d& eigenvalues,
                                matrix_d& eigenvectors) {
      Eigen::EigenSolver<matrix_d> solver(m);
      eigenvalues = solver.eigenvalues().real();
      eigenvectors = solver.eigenvectors().real();
    }

    /**
     * Return the eigenvalues of the specified symmetric matrix
     * in descending order of magnitude.  This function is more
     * efficient than the general eigenvalues function for symmetric
     * matrices.
     * <p>See <code>eigen_decompose()</code> for more information.
     * @param m Specified matrix.
     * @return Eigenvalues of matrix.
     */
    inline vector_d eigenvalues_sym(const matrix_d& m) {
      Eigen::SelfAdjointEigenSolver<matrix_d> solver(m,Eigen::EigenvaluesOnly);
      return solver.eigenvalues().real();
    }
    /**
     * Return a matrix whose rows are the real components of the
     * eigenvectors of the specified symmetric matrix.  This function
     * is more efficient than the general eigenvectors function for
     * symmetric matrices.
     * <p>See <code>eigen_decompose()</code> for more information.
     * @param m Symmetric matrix.
     * @return Eigenvectors of matrix.
     */
    inline matrix_d eigenvectors_sym(const matrix_d& m) {
      Eigen::SelfAdjointEigenSolver<matrix_d> solver(m);
      return solver.eigenvectors().real();
    }
    /**
     * Assign the real components of the eigenvalues and eigenvectors
     * of the specified symmetric matrix to the specified references.
     * <p>See <code>eigen_decompose()</code> for more information on the
     * values.
     * @param m Symmetric matrix.  This function is more efficient
     * than the general decomposition method for symmetric matrices.
     * @param eigenvalues Column vector reference into which
     * eigenvalues are written.
     * @param eigenvectors Matrix reference into which eigenvectors
     * are written.
     */
    inline void eigen_decompose_sym(const matrix_d& m,
                                    vector_d& eigenvalues,
                                    matrix_d& eigenvectors) {
      Eigen::SelfAdjointEigenSolver<matrix_d> solver(m);
      eigenvalues = solver.eigenvalues().real();
      eigenvectors = solver.eigenvectors().real();
    }


    /**
     * Return the lower-triangular Cholesky factor (i.e., matrix
     * square root) of the specified square, symmetric matrix.  The return
     * value \f$L\f$ will be a lower-traingular matrix such that the
     * original matrix \f$A\f$ is given by
     * <p>\f$A = L \times L^T\f$.
     * @param m Symmetrix matrix.
     * @return Square root of matrix.
     * @throw std::invalid_argument if m is not a square matrix
     */
    inline matrix_d cholesky_decompose(const matrix_d& m) {
      if (m.rows() != m.cols())
        throw std::invalid_argument ("m must be a square matrix");
      Eigen::LLT<matrix_d> llt(m.rows());
      llt.compute(m);
      return llt.matrixL();
    }

    /**
     * Return the vector of the singular values of the specified matrix
     * in decreasing order of magnitude.
     * <p>See the documentation for <code>svd()</code> for
     * information on the signular values.
     * @param m Specified matrix.
     * @return Singular values of the matrix.
     */
    inline vector_d singular_values(const matrix_d& m) {
      Eigen::JacobiSVD<matrix_d> svd(m); // no U or V
      return svd.singularValues();
    }      

    /**
     * Assign the real components of a singular value decomposition
     * of the specified matrix to the specified references.  
     * <p>Thesingular values \f$S\f$ are assigned to a vector in 
     * decreasing order of magnitude.  The left singular vectors are
     * found in the columns of \f$U\f$ and the right singular vectors
     * in the columns of \f$V\f$.
     * <p>The original matrix is recoverable as
     * <p>\f$A = U \times \mbox{\rm diag}(S) \times V^T\f$, where
     * \f$\mbox{\rm diag}(S)\f$ is the square diagonal matrix with
     * diagonal elements \f$S\f$.
     * <p>If \f$A\f$ is an \f$M \times N\f$ matrix
     * and \f$K = \mbox{\rm min}(M,N)\f$, 
     * then \f$U\f$ is an \f$M \times K\f$ matrix,  
     * \f$S\f$ is a length \f$K\f$ column vector, and 
     * \f$V\f$ is an \f$N \times K\f$ matrix.
     * @param m Matrix to decompose.
     * @param u Left singular vectors.
     * @param v Right singular vectors.
     * @param s Singular values.
     */
    inline void svd(const matrix_d& m,
                    matrix_d& u,
                    matrix_d& v,
                    vector_d& s) {
      static const unsigned int THIN_SVD_OPTIONS
        = Eigen::ComputeThinU | Eigen::ComputeThinV;
      Eigen::JacobiSVD<matrix_d> svd(m, THIN_SVD_OPTIONS);
      u = svd.matrixU();
      v = svd.matrixV();
      s = svd.singularValues();
    }

  }

}

#endif

