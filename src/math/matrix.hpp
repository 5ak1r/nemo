#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <iomanip>
#include <ostream>
#include <stdexcept>
#include <type_traits>
#include <vector>

#include "float3.hpp"

/*
- inverse
- eigenvalues
*/

namespace math {

template<typename T>
class Matrix {
  static_assert(std::is_arithmetic<T>::value, "Matrix<T> requires an arithmetic type");

public:
  Matrix(int rows, int cols) : mRows(rows), mCols(cols), mSize(rows * cols), mData(mSize) {
    if (rows <= 0 || cols <= 0)
      throw std::invalid_argument("Rows and Columns must be greater than zero");
  }

  Matrix(int rows, int cols, std::vector<T> data) : mRows(rows), mCols(cols), mSize(rows * cols) {
    if (rows <= 0 || cols <= 0)
      throw std::invalid_argument("Rows and Columns must be greater than zero");
    if (data.size() != rows * cols)
      throw std::invalid_argument("Data does not match row and column size");

    mData = data;
  }

  // setters
  void setData(int pos, T value) {
    if (pos < 0 || pos > mRows * mCols)
      throw std::invalid_argument("Index out of range");

    mData[pos] = value;
  }

  // getters
  int rows() const { return mRows; }
  int cols() const { return mCols; }
  int size() const { return mSize; }
  std::vector<T> data() const { return mData; }
  bool isSquare() const { return mRows == mCols; }

  std::vector<T> transpose() const {
    std::vector<T> transposed;
    transposed.reserve(mSize);

    if (mRows == 1 || mCols == 1) return mData;

    for (int i = 0; i < mCols; i++) {
      for (int j = 0; j < mRows; j++) {
        transposed.push_back(mData[j * mCols + i]);
      }
    }

    return transposed;
  }

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

  template<typename T2>
  Matrix& operator+=(const Matrix<T2>& other) {
    static_assert(std::is_convertible<T2, T>::value, "Incompatible typing");

    if (mRows != other.rows() || mCols != other.cols())
      throw std::invalid_argument("Matrix dimensions must be equal");

    for (int i = 0; i < mSize; i++) mData[i] += static_cast<T>(other.data()[i]);

    return *this;
  }

  template<typename T2>
  Matrix& operator-=(const Matrix<T2>& other) {
    static_assert(std::is_convertible<T2, T>::value, "Incompatible typing");

    if (mRows != other.rows() || mCols != other.cols())
      throw std::invalid_argument("Matrix dimensions must be equal");

    for (int i = 0; i < mSize; i++) mData[i] -= static_cast<T>(other.data()[i]);

    return *this;
  }

  template<typename T2>
  Matrix& operator*=(const Matrix<T2>& other) {
    static_assert(std::is_convertible<T2, T>::value, "Incompatible typing");

    if (mCols != other.rows())
      throw std::invalid_argument("Other matrix column count must equal row count");

    *this = multiplyM(*this, other);
    return *this;
  }

private:
  int mRows;
  int mCols;
  int mSize;
  std::vector<T> mData;
};

template<typename T1, typename T2>
auto operator+(const Matrix<T1>& a, const Matrix<T2>& b) {
  using T3 = std::common_type_t<T1, T2>;

  if (a.rows() != b.rows() || a.cols() != b.cols())
    throw std::invalid_argument("Matrix dimensions must be equal");

  Matrix<T3> result(a.rows(), a.cols());

  for (int i = 0; i < a.size(); i++) {
    result.setData(i, static_cast<T3>(a.data()[i]) + static_cast<T3>(b.data()[i]));
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
    result.setData(i, static_cast<T3>(a.data()[i] - static_cast<T3>(b.data()[i])));
  }

  return result;
}

template<typename T1, typename T2>
auto operator*(const Matrix<T1>& a, const Matrix<T2>& b) {
  using T3 = std::common_type_t<T1, T2>;

  if (a.cols() != b.rows())
    throw std::invalid_argument("Other matrix column count must equal row count");

  Matrix<T3> res = multiplyM(a, b);
  return res;
}

// recursive so probably incredibly inefficient, symbolab uses upper triangle form (will investigate)
template<typename T>
T det(const Matrix<T>& matrix) {
  if (!matrix.isSquare())
    throw std::invalid_argument("Cannot compute the determinant of a non-square matrix");

  if (matrix.rows() == 1) return matrix.data()[0];
  if (matrix.rows() == 2) return matrix.data()[0] * matrix.data()[3] - matrix.data()[1] * matrix.data()[2]; //(ad - bc)

  T total = 0;

  for (int i = 0; i < matrix.cols(); i++) {
    Matrix<T> temp = Matrix<T>(matrix.rows() - 1, matrix.cols() - 1);
    int pos = 0;

    for (int j = 0; j < matrix.size(); j++) {
      const int row = j / matrix.cols();
      const int col = j % matrix.cols();

      if (row == 0 || col == i) continue;

      temp.setData(pos++, matrix.data()[j]);
    }

    int sign = (i % 2 == 0) ? 1 : -1;
    total += sign * matrix(0, i) * det(temp);
  }

  return total;
}

template<typename T1, typename T2>
auto multiplyM(const Matrix<T1>& a, const Matrix<T2>& b) {
  using T3 = std::common_type_t<T1, T2>;

  std::vector<T3> result;
  result.reserve(a.cols() * b.rows());

  auto bT = b.transpose();

  for (int i = 0; i < a.rows(); i++) {
    for (int j = 0; j < b.cols(); j++) {
      T3 sum = T3{};
      const int start = i * a.cols();
      const int startOther = j * a.cols();

      for (int k = 0; k < a.cols(); k++) {
        sum += a.data()[start + k] * bT[startOther + k];
      }

      result.push_back(sum);
    }
  }

  return Matrix<T3>(a.rows(), b.cols(), std::move(result));
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
  int width = 0;
  int precision = 3;

  for (int i = 0; i < matrix.size(); i++) {
    std::string num = std::to_string(matrix.data()[i]);
    int length = num.length();
    width = std::max(width, length);
    if (num.find('.') != std::string::npos) width -= precision;
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