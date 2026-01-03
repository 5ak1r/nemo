#ifndef MATRIX_H
#define MATRIX_H

#include <iomanip>
#include <ostream>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

#include "matrix_helpers.hpp"

/*
- optimise determinant perchance
- inverse
- eigenvalues
*/

namespace math {

// matrix class
template<typename T>
class Matrix {
  static_assert(std::is_arithmetic<T>::value, "Matrix<T> requires an arithmetic type");

public:
  Matrix(int rows, int cols) : mRows(rows), mCols(cols), mSize(rows * cols), mData(mSize, T{}) {
    if (mRows <= 0 || mCols <= 0)
      throw std::invalid_argument("Rows and Columns must be greater than zero");
  }

  Matrix(int rows, int cols, std::vector<T> data) : mRows(rows), mCols(cols), mSize(rows * cols) {
    if (mRows <= 0 || mCols <= 0)
      throw std::invalid_argument("Rows and Columns must be greater than zero");
    if (data.size() != mSize)
      throw std::invalid_argument("Data does not match row and column size");

    mData = data;
  }

  static Matrix identity(int n) {
    Matrix I(n, n);

    for (int i = 0; i < n; i++) {
      I.mData[i * n + i] = T{1};
    }

    return I;
  }

  // getters
  int rows() const { return mRows; }
  int cols() const { return mCols; }
  int size() const { return mSize; }
  std::vector<T> data() const { return mData; }
  bool isSquare() const { return mRows == mCols; }

  int getRow(int idx) const { return idx / mCols; }
  int getCol(int idx) const { return idx % mCols; }

  // helpers
  void swapRows(int r1, int r2) {
    if (r1 == r2) return;

    if (r1 < 0 || r1 >= mRows || r2 < 0 || r2 >= mRows)
      throw std::out_of_range("Row index out of bounds");

    for (int c = 0; c < mCols; c++)
      std::swap((*this)(r1, c), (*this)(r2, c));
  }

  Matrix<T> adjugate() const {
    if (!isSquare())
      throw std::invalid_argument("Cannot compute the adjugate of a non-square matrix");

    return matrix::adjugate(*this);
  }

  // we don't need to convert data types as the determinant matches the type of the data
  Matrix<T> cofactors() const {
    return matrix::cofactors(*this);
  }

  auto determinant() const {
    return matrix::determinant(*this);
  }

  auto inverse() const {
    return matrix::inverse(*this);
  }

  Matrix<T> transpose() const {
    return matrix::transpose(*this);
  }

  // operator overloads
  // 2d indexing
  T& operator()(int i, int j) {
    if (i < 0 || i >= mRows || j < 0 || j >= mCols)
      throw std::out_of_range("Matrix index out of range");

    return mData[i * mCols + j];
  }

  T operator()(int i, int j) const {
    if (i < 0 || i >= mRows || j < 0 || j >= mCols)
      throw std::out_of_range("Matrix index out of range");

    return mData[i * mCols + j];
  }

  // 1d indexing
  T& operator()(int ij) {
    if (ij < 0 || ij >= mSize)
      throw std::out_of_range("Matrix index out of range");

    return mData[ij];
  }

  T operator()(int ij) const {
    if (ij < 0 || ij >= mSize)
      throw std::out_of_range("Matrix index out of range");

    return mData[ij];
  }

  template<typename T2>
  Matrix& operator+=(const Matrix<T2>& other) {
    static_assert(std::is_convertible<T2, T>::value, "Incompatible typing");

    if (mRows != other.rows() || mCols != other.cols())
      throw std::invalid_argument("Matrix dimensions must be equal");

    for (int i = 0; i < mSize; i++) mData[i] += static_cast<T>(other(i));

    return *this;
  }

  template<typename T2>
  Matrix& operator-=(const Matrix<T2>& other) {
    static_assert(std::is_convertible<T2, T>::value, "Incompatible typing");

    if (mRows != other.rows() || mCols != other.cols())
      throw std::invalid_argument("Matrix dimensions must be equal");

    for (int i = 0; i < mSize; i++) mData[i] -= static_cast<T>(other(i));

    return *this;
  }

  template<typename T2>
  Matrix& operator*=(const Matrix<T2>& other) {
    static_assert(std::is_convertible<T2, T>::value, "Incompatible typing");

    if (mCols != other.rows())
      throw std::invalid_argument("Other matrix column count must equal row count");

    *this = matrix::multiply(*this, other);
    return *this;
  }

private:
  int mRows;
  int mCols;
  int mSize;
  std::vector<T> mData;
};

// more operator overloads
template<typename T1, typename T2>
auto operator+(const Matrix<T1>& a, const Matrix<T2>& b) {
  using T3 = std::common_type_t<T1, T2>;

  if (a.rows() != b.rows() || a.cols() != b.cols())
    throw std::invalid_argument("Matrix dimensions must be equal");

  Matrix<T3> result(a.rows(), a.cols());

  for (int i = 0; i < a.size(); i++) {
    result(i) = static_cast<T3>(a(i)) + static_cast<T3>(b(i));
  }

  return result;
}

template<typename T1, typename T2>
auto operator-(const Matrix<T1>& a, const Matrix<T2>& b) {
  using T3 = std::common_type_t<T1, T2>;

  if (a.rows() != b.rows() || a.cols() != b.cols())
    throw std::invalid_argument("Matrix dimensions must be equal");

  Matrix<T3> result(a.rows(), b.cols());

  for (int i = 0; i < a.size(); i++) {
    result(i) = static_cast<T3>(a(i) - static_cast<T3>(b(i)));
  }

  return result;
}

template<typename T1, typename T2>
auto operator*(const T1& scalar, const Matrix<T2>& matrix) {
  using T3 = std::common_type_t<T1, T2>;

  Matrix<T3> result(matrix.rows(), matrix.cols());

  for (int i = 0; i < matrix.size(); i++) {
    result(i) = static_cast<T3>(scalar) * static_cast<T3>(matrix(i));
  }

  return result;
}

template<typename T1, typename T2>
auto operator*(const Matrix<T1>& a, const Matrix<T2>& b) {
  using T3 = std::common_type_t<T1, T2>;

  if (a.cols() != b.rows())
    throw std::invalid_argument("Other matrix column count must equal row count");

  Matrix<T3> res = matrix::multiply(a, b);
  return res;
}

template<typename T1, typename T2>
bool operator==(const Matrix<T1>& a, const Matrix<T2>& b) {
  if (a.size() != b.size())
    return false;

  using T3 = std::common_type_t<T1, T2>;

  for (int i = 0; i < a.size(); i++) {
    if (static_cast<T3>(a(i)) != static_cast<T3>(b(i))) return false;
  }

  return true;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
  int width = 0;
  int precision = 6;

  for (int i = 0; i < matrix.size(); i++) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << matrix(i);
    width = std::max(width, static_cast<int>(oss.str().length()));
  }

  for (int i = 0; i < matrix.rows(); i++) {
    for (int j = 0; j < matrix.cols(); j++) {
      os << std::fixed << std::setw(width + 1) << std::setprecision(precision) << matrix(i, j);
    }
    os << "\n";
  }

  return os;
}

}

#endif