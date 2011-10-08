#ifndef __STAN__AGRAD__MATRIX_H__
#define __STAN__AGRAD__MATRIX_H__

// global include
#include <Eigen/Dense>
#include <stan/maths/matrix.hpp>
#include <stan/agrad/agrad.hpp>
#include <stan/agrad/special_functions.hpp>

/**
 * (Expert) Numerical traits for algorithmic differentiation variables.
 */
namespace Eigen {

  /**
   * (Expert) Product traits for algorithmic differentiation variables.
   */
  namespace internal {

    template<>  
    struct scalar_product_traits<stan::agrad::var,double> {
      typedef stan::agrad::var ReturnType;
    };

    template<>  
    struct scalar_product_traits<double,stan::agrad::var> {
      typedef stan::agrad::var ReturnType;
    };

  }

  /**
   * Numerical traits template override for Eigen for automatic
   * gradient variables.
   */
  template<> struct NumTraits<stan::agrad::var>
  {
    /**
     * Real-valued variables.
     *
     * Required for numerical traits.
     */
    typedef stan::agrad::var Real;

    /**
     * Non-integer valued variables.
     *
     * Required for numerical traits.
     */
    typedef stan::agrad::var NonInteger;

    /**
     * Nested variables.
     *
     * Required for numerical traits.
     */
    typedef stan::agrad::var Nested;

    /**
     * Return standard library's epsilon for double-precision floating
     * point, <code>std::numeric_limits&lt;double&gt;::epsilon()</code>.
     *
     * @return Same epsilon as a <code>double</code>.
     */
    inline static Real epsilon() { 
      return std::numeric_limits<double>::epsilon(); 
    }

    /**
     * Return dummy precision
     */
    inline static Real dummy_precision() {
      return 1e-12; // copied from NumTraits.h values for double
    }

    /**
     * Return standard library's highest for double-precision floating
     * point, <code>std::numeric_limits&lt;double&gt;::max()</code>.
     *
     * @return Same highest value as a <code>double</code>.
     */
    inline static Real highest() {
      return std::numeric_limits<double>::max();
    }

    /**
     * Return standard library's lowest for double-precision floating
     * point, <code>-std::numeric_limits&lt;double&gt;::max()</code>.
     *
     * @return Same lowest value as a <code>double</code>.
     */    
    inline static Real lowest() {
      return -std::numeric_limits<double>::max();
    }

    /**
     * Properties for automatic differentiation variables
     * read by Eigen matrix library.
     */
    enum {
      IsInteger = 0,
      IsSigned = 1,
      IsComplex = 0,
      RequireInitialization = 0,
      ReadCost = 1,
      AddCost = 1,
      MulCost = 1,
      HasFloatingPoint = 1,
    };
  };

}

namespace stan {

  namespace agrad {

    using stan::agrad::var;

    using stan::maths::matrix_d;
    using stan::maths::vector_d;
    using stan::maths::row_vector_d;

    typedef Eigen::Matrix<var,Eigen::Dynamic,Eigen::Dynamic> matrix_v;
    typedef Eigen::Matrix<var,Eigen::Dynamic,1> vector_v;
    typedef Eigen::Matrix<var,1,Eigen::Dynamic> row_vector_v;

    /**
     * Returns an automatic differentiation variable with the input value.
     *
     * @param x A scalar value
     * @return An automatic differentiation variable with the input value.
     */
    inline var to_var(const double& x) {
      return var(x);
    }
    /**
     * Sets an automatic differentiation variable with the input value.
     *
     * @param x A scalar value
     * @param var_x A reference to an automatic differentiation variable
     *   which will have the value of x.
     */
    inline void to_var(const double& x, var& var_x) {
      var_x = x;
    }
    /**
     * Returns an automatic differentiation variable with the input value.
     *
     * @param x An automatic differentiation variable.
     * @return An automatic differentiation variable with the input value.
     */    
    inline var to_var(const var& x) {
      return (x);
    }
    /**
     * Sets an automatic differentiation variable with the input value.
     *
     * @param var_in An automatic differentiation variable.
     * @param var_out A reference to an automatic differentiation variable
     *   which will be set to the input value.
     */
    inline void to_var(const var& var_in, var& var_out) {
      var_out = var_in;
    }
    /**
     * Returns a Matrix with automatic differentiation variables.
     *
     * @param m A Matrix with scalars
     * @return A Matrix with automatic differentiation variables
     */
    inline matrix_v to_var (const matrix_d& m) {
      matrix_v m_v(m.rows(), m.cols());
      for (int i = 0; i < m.rows(); ++i)
	for (int j = 0; j < m.cols(); ++j)
	  m_v(i,j) = m(i,j);
      return m_v;
    }
    
    /**
     * Sets a Matrix with automatic differentiation variables.
     *
     * @param m A Matrix of scalars.
     * @param m_v A Matrix with automatic differentiation variables
     *    assigned with values of m.
     */
    inline matrix_v to_var (const matrix_d& m, matrix_v& m_v) {
      m_v.resize(m.rows(), m.cols());
      for (int i = 0; i < m.rows(); ++i)
	for (int j = 0; j < m.cols(); ++j)
	  m_v(i,j) = m(i,j);
      return m_v;
    }
    /**
     * Returns a Matrix with automatic differentiation variables.
     * 
     * @param m A Matrix with automatic differentiation variables.
     */
    inline matrix_v to_var(const matrix_v& m) {
      return m;
    }
    /**
     * Sets a Matirx with automatic differentiation variables.
     *
     * @param m_in A Matrix of automatic differentiation variables.
     * @param m_out A Matrix of automatic differentiation variables
     *    assigned with values of m_in.
     */
    inline void to_var (const matrix_v& m_in,
			matrix_v& m_out) {
      m_out = m_in;
    }
    /**
     * Returns a Vector with automatic differentiation variables
     *
     * @param v A Vector of scalars
     * @return A Vector of automatic differentiation variables with
     *   values of v
     */
    inline vector_v to_var(const vector_d& v) {
      vector_v v_v(v.size());
      for (int i = 0; i < v.size(); ++i)
	v_v[i] = v[i];
      return v_v;
    }
    /**
     * Sets a Vector with automatic differentation variables.
     *
     * @param v A Vector of scalars.
     * @param v_v A Vector of automatic differentation variables with
     *   values of v.
     */
    inline void to_var(const vector_d& v,
		       vector_v& v_v) {
      v_v.resize(v.size());
      for (int i = 0; i < v.size(); ++i)
	v_v[i] = v[i];
    }
    /**
     * Returns a Vector with automatic differentiation variables
     *
     * @param v A Vector of automatic differentiation variables
     * @return A Vector of automatic differentiation variables with
     *   values of v
     */
    inline vector_v to_var(const vector_v& v) {
      return v;
    }
    /**
     * Sets a Vector with automatic differentiation variables
     *
     * @param v_in A Vector of automatic differentiation variables
     * @param v_out A Vector of automatic differentiation variables
     *    with values of v_in
     */
    inline void to_var(const vector_v& v_in,
			 vector_v& v_out) {
      v_out = v_in;
    }
    /**
     * Returns a row vector with automatic differentiation variables
     *
     * @param rv A row vector of scalars
     * @return A row vector of automatic differentation variables with 
     *   values of rv.
     */
    inline row_vector_v to_var(const row_vector_d& rv) {
      row_vector_v rv_v(rv.size());
      for (int i = 0; i < rv.size(); ++i)
	rv_v[i] = rv[i];
      return rv_v;
    }
    /**
     * Sets a row vector with automatic differentiation variables
     *
     * @param rv A row vector of scalars
     * @param rv_v A row vector of automatic differentiation variables
     *   with values set to rv.
     */
    inline void to_var(const row_vector_d& rv,
			  row_vector_v& rv_v) {
      rv_v.resize(rv.size());
      for (int i = 0; i < rv.size(); ++i)
	rv_v[i] = rv[i];
    }
    /**
     * Returns a row vector with automatic differentiation variables
     *
     * @param rv A row vector with automatic differentiation variables
     * @return A row vector with automatic differentiation variables
     *    with values of rv.
     */
    inline row_vector_v to_var(const row_vector_v& rv) {
      return rv;
    }
    /**
     * Sets a row vector with automatic differentiation variables
     *
     * @param rv_in A row vector with automatic differentiation variables
     * @param rv_out A row vector with automatic differentiation variables
     *    with values of rv_in
     */
    inline void to_var(const row_vector_v& rv_in,
		       row_vector_v& rv_out) {
      rv_out = rv_in;
    }

    // int returns
    /**
     * Return the number of rows in the specified 
     * column vector.
     * @param v Specified vector.
     * @return Number of rows in the vector.
     */
    inline unsigned int rows(const vector_v& v) {
      return v.size();
    }
    /**
     * Return the number of rows in the specified 
     * row vector.  The return value is always 1.
     * @param rv Specified vector.
     * @return Number of rows in the vector.
     */
    inline unsigned int rows(const row_vector_v& rv) {
      return 1;
    }
    /**
     * Return the number of rows in the specified matrix.
     * @param m Specified matrix.
     * @return Number of rows in the vector.
     * 
     */
    inline unsigned int rows(const matrix_v& m) {
      return m.rows();
    }

    /**
     * Return the number of columns in the specified
     * column vector.  The return value is always 1.
     * @param v Specified vector.
     * @return Number of columns in the vector.
     */
    inline unsigned int cols(const vector_v& v) {
      return 1;
    }
    /**
     * Return the number of columns in the specified
     * row vector.  
     * @param rv Specified vector.
     * @return Number of columns in the vector.
     */
    inline unsigned int cols(const row_vector_v& rv) {
      return rv.size();
    }
    /**
     * Return the number of columns in the specified matrix.
     * @param m Specified matrix.
     * @return Number of columns in the matrix.
     */
    inline unsigned int cols(const matrix_v& m) {
      return m.cols();
    }

    // scalar returns

    /**
     * Returns the determinant of the specified
     * square matrix.
     * @param m Specified matrix.
     * @return Determinant of the matrix.
     */
    template <typename T>
    inline var determinant(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>& m) {
      assert (m.rows() == m.cols());
      return to_var(m).determinant();
    }

    /**
     * Returns the dot product of the specified vectors.
     * @param v1 First column vector.
     * @param v2 Second column vector.
     * @return Dot product of the vectors.
     */
    template<typename T1, typename T2>
    inline var dot_product(const Eigen::Matrix<T1, Eigen::Dynamic, 1>& v1, const Eigen::Matrix<T2, Eigen::Dynamic, 1>& v2) {
      assert (v1.size() == v2.size());
      return to_var(v1).dot(to_var(v2));
    }
    /**
     * Returns the dot product of the specified vectors.
     * @param v1 First row vector.
     * @param v2 Second row vector.
     * @return Dot product of the vectors.
     */
    template<typename T1, typename T2>
    inline var dot_product(const Eigen::Matrix<T1, 1, Eigen::Dynamic>& v1, const Eigen::Matrix<T2, 1, Eigen::Dynamic>& v2) {
      assert (v1.size() == v2.size());
      return to_var(v1).dot(to_var(v2));
    }
    /**
     * Returns the dot product of the specified vectors.
     * @param v1 First column vector.
     * @param v2 Second row vector.
     * @return Dot product of the vectors.
     */
    template<typename T1, typename T2>
    inline var dot_product(const Eigen::Matrix<T1, Eigen::Dynamic, 1>& v1, const Eigen::Matrix<T2, 1, Eigen::Dynamic>& v2) {
      assert (v1.size() == v2.size());
      return to_var(v1).dot(to_var(v2));
    }
    /**
     * Returns the dot product of the specified vectors.
     * @param v1 First row vector.
     * @param v2 Second column vector.
     * @return Dot product of the vectors.
     */
    template<typename T1, typename T2>
    inline var dot_product(const Eigen::Matrix<T1, 1, Eigen::Dynamic>& v1, const Eigen::Matrix<T2, Eigen::Dynamic, 1>& v2) {
      assert (v1.size() == v2.size());
      return to_var(v1).dot(to_var(v2));
    }

    /**
     * Returns the minimum coefficient in the specified
     * column vector.
     * @param v Specified vector.
     * @return Minimum coefficient value in the vector.
     */
    template<typename T>
    inline var min(const Eigen::Matrix<T, Eigen::Dynamic, 1>& v) {
      assert(v.size() > 0);
      return to_var(v).minCoeff();
    }
    /**
     * Returns the minimum coefficient in the specified
     * row vector.
     * @param rv Specified vector.
     * @return Minimum coefficient value in the vector.
     */
    template<typename T>
    inline var min(const Eigen::Matrix<T, 1, Eigen::Dynamic>& rv) {
      assert(rv.size() > 0);
      return to_var(rv).minCoeff();
    }
    /**
     * Returns the minimum coefficient in the specified
     * matrix.
     * @param m Specified matrix.
     * @return Minimum coefficient value in the matrix.
     */
    template<typename T>
    inline var min(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>& m) {
      assert(m.size() > 0);
      return to_var(m).minCoeff();
    }

    /**
     * Returns the maximum coefficient in the specified
     * column vector.
     * @param v Specified vector.
     * @return Maximum coefficient value in the vector.
     */
    template<typename T>
    inline var max(const Eigen::Matrix<T, Eigen::Dynamic, 1>& v) {
      return to_var(v).maxCoeff();
    }
    /**
     * Returns the maximum coefficient in the specified
     * row vector.
     * @param rv Specified vector.
     * @return Maximum coefficient value in the vector.
     */
    template<typename T>
    inline var max(const Eigen::Matrix<T, 1, Eigen::Dynamic>& rv) {
      return to_var(rv).maxCoeff();
    }
    /**
     * Returns the maximum coefficient in the specified
     * matrix.
     * @param m Specified matrix.
     * @return Maximum coefficient value in the matrix.
     */
    template<typename T>
    inline var max(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>& m) {
      return to_var(m).maxCoeff();
    }

    /**
     * Returns the sample mean (i.e., average) of the coefficients
     * in the specified column vector.
     * @param v Specified vector.
     * @return Sample mean of vector coefficients.
     */
    inline var mean(const vector_v& v) {
      return v.mean();
    }
    /**
     * Returns the sample mean (i.e., average) of the coefficients
     * in the specified row vector.
     * @param rv Specified vector.
     * @return Sample mean of vector coefficients.
     */
    inline var mean(const row_vector_v& rv) {
      return rv.mean();
    }
    /**
     * Returns the sample mean (i.e., average) of the coefficients
     * in the specified matrix.
     * @param m Specified matrix.
     * @return Sample mean of matrix coefficients.
     */
    inline var mean(const matrix_v& m) {
      return m.mean();
    }

    /**
     * Returns the sample variance (divide by length - 1) of the
     * coefficients in the specified column vector.
     * @param v Specified vector.
     * @return Sample variance of vector.
     */
    inline var variance(const vector_v& v) {
      assert (v.size() > 1);
      var mean = v.mean();
      var sum_sq_diff = 0;
      // FIXME: redefine in terms of vectorized ops
      // (v.array() - mean).square().sum() / (v.size() - 1);
      for (int i = 0; i < v.size(); ++i) {
	var diff = v[i] - mean;
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
    inline var variance(const row_vector_v& rv) {
      assert (rv.size() > 1);
      var mean = rv.mean();
      var sum_sq_diff = 0;
      for (int i = 0; i < rv.size(); ++i) {
	var diff = rv[i] - mean;
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
    inline var variance(const matrix_v& m) {
      var mean = m.mean();
      var sum_sq_diff = 0;
      for (int i = 0; i < m.rows(); ++i) {
	for (int j = 0; j < m.cols(); ++j) { 
	  var diff = m(i,j) - mean;
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
    inline var sd(const vector_v& v) {
      return sqrt(variance(v));
    }
    /**
     * Returns the unbiased sample standard deviation of the
     * coefficients in the specified row vector.
     * @param rv Specified vector.
     * @return Sample variance of vector.
     */
    inline var sd(const row_vector_v& rv) {
      return sqrt(variance(rv));
    }
    /**
     * Returns the unbiased sample standard deviation of the
     * coefficients in the specified matrix.
     * @param m Specified matrix.
     * @return Sample variance of matrix.
     */
    inline var sd(const matrix_v& m) {
      return sqrt(variance(m));
    }

    /**
     * Returns the sum of the coefficients of the specified
     * column vector.
     * @param v Specified vector.
     * @return Sum of coefficients of vector.
     */
    inline var sum(const vector_v& v) {
      return v.sum();
    }
    /**
     * Returns the sum of the coefficients of the specified
     * row vector.
     * @param rv Specified vector.
     * @return Sum of coefficients of vector.
     */
    inline var sum(const row_vector_v& rv) {
      return rv.sum();
    }
    /**
     * Returns the sum of the coefficients of the specified
     * matrix
     * @param m Specified matrix.
     * @return Sum of coefficients of matrix.
     */
    inline var sum(const matrix_v& m) {
      return m.sum();
    }

    /**
     * Returns the product of the coefficients of the specified
     * column vector.
     * @param v Specified vector.
     * @return Product of coefficients of vector.
     */
    inline var prod(const vector_v& v) {
      return v.prod();
    }
    /**
     * Returns the product of the coefficients of the specified
     * row vector.
     * @param rv Specified vector.
     * @return Product of coefficients of vector.
     */
    inline var prod(const row_vector_v& rv) {
      return rv.prod();
    }
    /**
     * Returns the product of the coefficients of the specified
     * matrix.
     * @param m Specified matrix.
     * @return Product of coefficients of matrix.
     */
    inline var prod(const matrix_v& m) {
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
    inline var trace(const matrix_v& m) {
      return m.trace();
    }

    /**
     * Return the sum of the specified column vectors.
     * The two vectors must have the same size.
     * @param v1 First vector.
     * @param v2 Second vector.
     * @return Sum of the two vectors.
     */
    template<typename T1, typename T2>
    inline Eigen::Matrix<var, Eigen::Dynamic, 1> add(const Eigen::Matrix<T1, Eigen::Dynamic, 1>& v1, 
						     const Eigen::Matrix<T2, Eigen::Dynamic, 1>& v2) {
      assert(v1.size() == v2.size());
      return to_var(v1) + to_var(v2);
    }
    /**
     * Return the sum of the specified row vectors.  The
     * two vectors must have the same size.
     * @param rv1 First vector.
     * @param rv2 Second vector.
     * @return Sum of the two vectors.
     */
    template<typename T1, typename T2>
    inline Eigen::Matrix<var, 1, Eigen::Dynamic> add(const Eigen::Matrix<T1, 1, Eigen::Dynamic>& v1, 
						     const Eigen::Matrix<T2, 1, Eigen::Dynamic>& v2) {
      assert(v1.size() == v2.size());
      return to_var(v1) + to_var(v2);
    }

    /**
     * Return the sum of the specified matrices.  The two matrices
     * must have the same dimensions.
     * @param m1 First matrix.
     * @param m2 Second matrix.
     * @return Sum of the two vectors.
     */
    template<typename T1, typename T2>
    inline Eigen::Matrix<var, Eigen::Dynamic, Eigen::Dynamic> add(const Eigen::Matrix<T1, Eigen::Dynamic, Eigen::Dynamic>& m1, 
								  const Eigen::Matrix<T2, Eigen::Dynamic, Eigen::Dynamic>& m2) {
      assert(m1.rows() == m2.rows() && m1.cols() == m2.cols());
      return to_var(m1) + to_var(m2);
    }

    /**
     * Return the difference between the first specified column vector
     * and the second.  The two vectors must have the same size.
     * @param v1 First vector.
     * @param v2 Second vector.
     * @return First vector minus the second vector.
     */
    template<typename T1, typename T2>
    inline Eigen::Matrix<var, Eigen::Dynamic, 1> subtract(const Eigen::Matrix<T1, Eigen::Dynamic, 1>& v1, 
							  const Eigen::Matrix<T2, Eigen::Dynamic, 1>& v2) {
      assert(v1.size() == v2.size());
      return to_var(v1) - to_var(v2);
    }
    /**
     * Return the difference between the first specified row vector
     * and the second.  The two vectors must have the same size.
     * @param v1 First vector.
     * @param v2 Second vector.
     * @return First vector minus the second vector.
     */
    template<typename T1, typename T2>
    inline Eigen::Matrix<var, 1, Eigen::Dynamic> subtract(const Eigen::Matrix<T1, 1, Eigen::Dynamic>& v1, 
							  const Eigen::Matrix<T2, 1, Eigen::Dynamic>& v2) {
      assert(v1.size() == v2.size());
      return to_var(v1) - to_var(v2);
    }

    /**
     * Return the difference between the first specified matrix and
     * the second.  The two matrices must have the same dimensions.
     * @param m1 First matrix.
     * @param m2 Second matrix.
     * @return First matrix minus the second matrix.
     */
    template<typename T1, typename T2>
    inline Eigen::Matrix<var, Eigen::Dynamic, Eigen::Dynamic> subtract(const Eigen::Matrix<T1, Eigen::Dynamic, Eigen::Dynamic>& m1, 
								       const Eigen::Matrix<T2, Eigen::Dynamic, Eigen::Dynamic>& m2) {
      assert(m1.rows() == m2.rows() && m1.cols() == m2.cols());
      return to_var(m1) - to_var(m2);
    }


    /**
     * Return the negation of the specified variable.  The result
     * is the same as multiplying by the scalar <code>-1</code>.
     * @param v Specified variable.  
     * @return The negation of the variable.
     */
    template <typename T>
    inline var minus(const T& v) {
      return -to_var(v);
    }
    /**
     * Return the negation of the specified column vector.  The result
     * is the same as multiplying by the scalar <code>-1</code>.
     * @param v Specified vector.  
     * @return The negation of the vector.
     */
    template <typename T>
    inline vector_v minus(const Eigen::Matrix<T, Eigen::Dynamic, 1>& v) {
      return -to_var(v);
    }
    /**
     * Return the negation of the specified row vector.  The result is
     * the same as multiplying by the scalar <code>-1</code>.
     * @param rv Specified vector.
     * @return The negation of the vector.
     */
    template <typename T>
    inline row_vector_v minus(const Eigen::Matrix<T, 1, Eigen::Dynamic>& rv) {
      return -to_var(rv);
    }
    /**
     * Return the negation of the specified matrix.  The result is the same
     * as multiplying by the scalar <code>-1</code>.
     * @param m Specified matrix.
     * @return The negation of the matrix.
     */
    template <typename T>
    inline matrix_v minus(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>& m) {
      return -to_var(m);
    }

    /**
     * Return the division of the first scalar by
     * the second scalar.
     * @param v Specified vector.
     * @param c Specified scalar.
     * @return Vector divided by the scalar.
     */
    template<typename T1, typename T2>
    inline var divide(const T1& v, const T2& c) {
      return to_var(v) / to_var(c);
    }

    /**
     * Return the division of the specified column vector by
     * the specified scalar.
     * @param v Specified vector.
     * @param c Specified scalar.
     * @return Vector divided by the scalar.
     */
    template<typename T1, typename T2>
    inline vector_v divide(const Eigen::Matrix<T1, Eigen::Dynamic, 1>& v, const T2& c) {
      return to_var(v) / to_var(c);
    }

    /**
     * Return the division of the specified row vector by
     * the specified scalar.
     * @param rv Specified vector.
     * @param c Specified scalar.
     * @return Vector divided by the scalar.
     */
    template<typename T1, typename T2>
    inline row_vector_v divide(const Eigen::Matrix<T1, 1, Eigen::Dynamic>& rv, const T2& c) {
      return to_var(rv) / to_var(c);
    }
    /**
     * Return the division of the specified matrix by the specified
     * scalar.
     * @param m Specified matrix.
     * @param c Specified scalar.
     * @return Matrix divided by the scalar.
     */
    template<typename T1, typename T2>
    inline matrix_v divide(const Eigen::Matrix<T1, Eigen::Dynamic, Eigen::Dynamic>& m, const T2& c) {
      return to_var(m) / to_var(c);
    }
    
    /**
     * Return the product of the of the specified column
     * vector and specified scalar.
     * @param v Specified vector.
     * @param c Specified scalar.
     * @return Product of vector and scalar.
     */
    inline vector_v multiply(const vector_v& v, var c) {
      return v * c;
    }
    /**
     * Return the product of the of the specified column
     * vector and specified scalar.
     * @param v Specified vector.
     * @param c Specified scalar.
     * @return Product of vector and scalar.
     */
    inline vector_v multiply(const vector_v& v, double c) {
      return v * to_var(c);
    }
    /**
     * Return the product of the of the specified column
     * vector and specified scalar.
     * @param v Specified vector.
     * @param c Specified scalar.
     * @return Product of vector and scalar.
     */
    inline vector_v multiply(const vector_d& v, var c) {
      return to_var(v) * c;
    }

    /**
     * Return the product of the of the specified row
     * vector and specified scalar.
     * @param rv Specified vector.
     * @param c Specified scalar.
     * @return Product of vector and scalar.
     */
    inline row_vector_v multiply(const row_vector_v& rv, var c) {
      return rv * c;
    }
    /**
     * Return the product of the of the specified row
     * vector and specified scalar.
     * @param rv Specified vector.
     * @param c Specified scalar.
     * @return Product of vector and scalar.
     */
    inline row_vector_v multiply(const row_vector_v& rv, double c) {
      return rv * to_var(c);
    }
    /**
     * Return the product of the of the specified row
     * vector and specified scalar.
     * @param rv Specified vector.
     * @param c Specified scalar.
     * @return Product of vector and scalar.
     */
    inline row_vector_v multiply(const row_vector_d& rv, var c) {
      return to_var(rv) * c;
    }

    /**
     * Return the product of the of the specified matrix
     * and specified scalar.
     * @param m Matrix.
     * @param c Scalar.
     * @return Product of matrix and scalar.
     */
    inline matrix_v multiply(const matrix_v& m, var c) {
      return m * c;
    }
    /**
     * Return the product of the of the specified matrix
     * and specified scalar.
     * @param m Matrix.
     * @param c Scalar.
     * @return Product of matrix and scalar.
     */
    inline matrix_v multiply(const matrix_v& m, double c) {
      return m * to_var(c);
    }
    /**
     * Return the product of the of the specified matrix
     * and specified scalar.
     * @param m Matrix.
     * @param c Scalar.
     * @return Product of matrix and scalar.
     */
    inline matrix_v multiply(const matrix_d& m, var c) {
      return to_var(m) * c;
    }

    /**
     * Return the scalar product of the specified row vector and
     * specified column vector.  The return is the same as the dot
     * product.  The two vectors must be the same size.
     * @param rv Row vector.
     * @param v Column vector.
     * @return Scalar result of multiplying row vector by column vector.
     */
    inline var multiply(const row_vector_v& rv, const vector_v& v) {
      assert(rv.size() == v.size());
      return rv.dot(v);
    }
    /**
     * Return the scalar product of the specified row vector and
     * specified column vector.  The return is the same as the dot
     * product.  The two vectors must be the same size.
     * @param rv Row vector.
     * @param v Column vector.
     * @return Scalar result of multiplying row vector by column vector.
     */
    inline var multiply(const row_vector_v& rv, const vector_d& v) {
      assert(rv.size() == v.size());
      return rv.dot(to_var(v));
    }
    /**
     * Return the scalar product of the specified row vector and
     * specified column vector.  The return is the same as the dot
     * product.  The two vectors must be the same size.
     * @param rv Row vector.
     * @param v Column vector.
     * @return Scalar result of multiplying row vector by column vector.
     */
    inline var multiply(const row_vector_d& rv, const vector_v& v) {
      assert(rv.size() == v.size());
      return to_var(rv).dot(v);
    }
    

    /**
     * Return the product of the specified column vector
     * and specified row vector.  The two vectors may be of any size.
     * @param v Column vector.
     * @param rv Row vector.
     * @return Product of column vector and row vector.
     */
    inline matrix_v multiply(const vector_v& v, const row_vector_v& rv) {
      return v * rv;
    }
    /**
     * Return the product of the specified column vector
     * and specified row vector.  The two vectors may be of any size.
     * @param v Column vector.
     * @param rv Row vector.
     * @return Product of column vector and row vector.
     */
    inline matrix_v multiply(const vector_v& v, const row_vector_d& rv) {
      return v * to_var(rv);
    }
    /**
     * Return the product of the specified column vector
     * and specified row vector.  The two vectors may be of any size.
     * @param v Column vector.
     * @param rv Row vector.
     * @return Product of column vector and row vector.
     */
    inline matrix_v multiply(const vector_d& v, const row_vector_v& rv) {
      return to_var(v) * rv;
    }

    /**
     * Return the product of the specified matrix and
     * column vector.  The number of rows of the matrix must be
     * the same as the size of the vector.
     * @param m Matrix.
     * @param v Column vector.
     * @return Product of matrix and vector.
     */
    inline vector_v multiply(const matrix_v& m, const vector_v& v) {
      assert(m.rows() == v.size());
      return m * v;
    }
    /**
     * Return the product of the specified matrix and
     * column vector.  The number of rows of the matrix must be
     * the same as the size of the vector.
     * @param m Matrix.
     * @param v Column vector.
     * @return Product of matrix and vector.
     */
    inline vector_v multiply(const matrix_v& m, const vector_d& v) {
      assert(m.rows() == v.size());
      return m * to_var(v);
    }
    /**
     * Return the product of the specified matrix and
     * column vector.  The number of rows of the matrix must be
     * the same as the size of the vector.
     * @param m Matrix.
     * @param v Column vector.
     * @return Product of matrix and vector.
     */
    inline vector_v multiply(const matrix_d& m, const vector_v& v) {
      assert(m.rows() == v.size());
      return to_var(m) * v;
    }

    /**
     * Return the product of the specifieid row vector and specified
     * matrix.  The number of columns of the matrix must be the same
     * as the size of the vector.
     * @param rv Row vector.
     * @param m Matrix.
     * @return Product of vector and matrix.
     */
    inline row_vector_v multiply(const row_vector_v& rv, const matrix_v& m) {
      assert(rv.size() == m.cols());
      return rv * m;
    }
    /**
     * Return the product of the specifieid row vector and specified
     * matrix.  The number of columns of the matrix must be the same
     * as the size of the vector.
     * @param rv Row vector.
     * @param m Matrix.
     * @return Product of vector and matrix.
     */
    inline row_vector_v multiply(const row_vector_v& rv, const matrix_d& m) {
      assert(rv.size() == m.cols());
      return rv * to_var(m);
    }
    /**
     * Return the product of the specifieid row vector and specified
     * matrix.  The number of columns of the matrix must be the same
     * as the size of the vector.
     * @param rv Row vector.
     * @param m Matrix.
     * @return Product of vector and matrix.
     */
    inline row_vector_v multiply(const row_vector_d& rv, const matrix_v& m) {
      assert(rv.size() == m.cols());
      return to_var(rv) * m;
    }

    /**
     * Return the product of the specified matrices.  The number of
     * rows in the first matrix must be the same as the number of columns
     * in the second matrix.
     * @param m1 First matrix.
     * @param m2 Second matrix.
     * @return The product of the first and second matrices.
     */
    inline matrix_v multiply(const matrix_v& m1, const matrix_v& m2) {
      assert(m1.rows() == m2.cols());
      return m1 * m2;
    }
    /**
     * Return the product of the specified matrices.  The number of
     * rows in the first matrix must be the same as the number of columns
     * in the second matrix.
     * @param m1 First matrix.
     * @param m2 Second matrix.
     * @return The product of the first and second matrices.
     */
    inline matrix_v multiply(const matrix_v& m1, const matrix_d& m2) {
      assert(m1.rows() == m2.cols());
      return m1 * to_var(m2);
    }
    /**
     * Return the product of the specified matrices.  The number of
     * rows in the first matrix must be the same as the number of columns
     * in the second matrix.
     * @param m1 First matrix.
     * @param m2 Second matrix.
     * @return The product of the first and second matrices.
     */
    inline matrix_v multiply(const matrix_d& m1, const matrix_v& m2) {
      assert(m1.rows() == m2.cols());
      return to_var(m1) * m2;
    }
    
    /**
     * Return the specified row of the specified matrix.
     * @param m Matrix.
     * @param i Row index.
     * @return Specified row of the matrix.
     */
    inline row_vector_v row(const matrix_v& m, unsigned int i) {
      return m.row(i);
    }

    /**
     * Return the specified column of the specified matrix.
     * @param m Matrix.
     * @param j Column index.
     * @return Specified column of the matrix.
     */
    inline vector_v col(const matrix_v& m, unsigned int j) {
      return m.col(j);
    }

    /**
     * Return a column vector of the diagonal elements of the
     * specified matrix.  The matrix is not required to be square.
     * @param m Specified matrix.  
     * @return Diagonal of the matrix.
     */
    inline vector_v diagonal(const matrix_v& m) {
      return m.diagonal();
    }

    /**
     * Return a square diagonal matrix with the specified vector of
     * coefficients as the diagonal values.
     * @param v Specified vector.
     * @return Diagonal matrix with vector as diagonal values.
     */
    inline matrix_v diag_matrix(const vector_v& v) {
      return v.asDiagonal();
    }

    /**
     * Return the transposition of the specified column
     * vector.
     * @param v Specified vector.
     * @return Transpose of the vector.
     */
    inline row_vector_v transpose(const vector_v& v) {
      return v.transpose();
    }
    /**
     * Return the transposition of the specified row
     * vector.
     * @param rv Specified vector.
     * @return Transpose of the vector.
     */
    inline vector_v transpose(const row_vector_v& rv) {
      return rv.transpose();
    }
    /**
     * Return the transposition of the specified matrix.
     * @param m Specified matrix.
     * @return Transpose of the matrix.
     */
    inline matrix_v transpose(const matrix_v& m) {
      return m.transpose();
    }

    /**
     * Returns the inverse of the specified matrix.
     * @param m Specified matrix.
     * @return Inverse of the matrix.
     */
    inline matrix_v inverse(const matrix_v& m) {
      return m.inverse();
    }

    /**
     * Return the real component of the eigenvalues of the specified
     * matrix in descending order of magnitude.
     * <p>See <code>eigen_decompose()</code> for more information.
     * @param m Specified matrix.
     * @return Eigenvalues of matrix.
     */
    inline vector_v eigenvalues(const matrix_v& m) {
      // false == no vectors
      Eigen::EigenSolver<matrix_v> solver(m,false);
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
    inline matrix_v eigenvectors(const matrix_v& m) {
      Eigen::EigenSolver<matrix_v> solver(m);
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
    inline void eigen_decompose(const matrix_v& m,
				vector_v& eigenvalues,
				matrix_v& eigenvectors) {
      Eigen::EigenSolver<matrix_v> solver(m);
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
    inline vector_v eigenvalues_sym(const matrix_v& m) {
      Eigen::SelfAdjointEigenSolver<matrix_v> solver(m,Eigen::EigenvaluesOnly);
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
    inline matrix_v eigenvectors_sym(const matrix_v& m) {
      Eigen::SelfAdjointEigenSolver<matrix_v> solver(m);
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
    inline void eigen_decompose_sym(const matrix_v& m,
				    vector_v& eigenvalues,
				    matrix_v& eigenvectors) {
      Eigen::SelfAdjointEigenSolver<matrix_v> solver(m);
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
     */
    inline matrix_v cholesky_decompose(const matrix_v& m) {
      assert(m.rows() == m.cols());
      Eigen::LLT<matrix_v> llt(m.rows());
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
    inline vector_v singular_values(const matrix_v& m) {
      Eigen::JacobiSVD<matrix_v> svd(m); // no U or V
      return svd.singularValues();
    }      

    namespace {

      const unsigned int THIN_SVD_OPTIONS
          = Eigen::ComputeThinU | Eigen::ComputeThinV;
    
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
    inline void svd(const matrix_v& m,
		    matrix_v& u,
		    matrix_v& v,
		    vector_v& s) {
      Eigen::JacobiSVD<matrix_v> svd(m, THIN_SVD_OPTIONS);
      u = svd.matrixU();
      v = svd.matrixV();
      s = svd.singularValues();
    }


  }
}

#endif

