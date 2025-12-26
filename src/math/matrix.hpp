#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>
#include <type_traits>
#include <vector>

#include "float3.hpp"

/*
- create a matrix
  - 2d array or flat array with manipulation (index = row * cols + col)
  - mat struct -> rows, cols, data
- access and modify elements
  - check bounds, decide if 0 based
- addition / subtraction
- multiplication / division
- transpose
- determinant, inverse
- eigenvalues
- optimisations (BLAS)
- sparce matrices
*/

namespace math {

template<typename T>
class Matrix {
  static_assert(std::is_arithmetic<T>::value, "Matrix<T> requires an arithmetic type");

public:
  Matrix(int rows, int cols) : mRows(rows), mCols(cols), mSize(rows * cols), mData(mSize) {}

  // setters
  void setData(int pos, T value) {
    if(pos < 0 || pos > mRows * mCols)
      throw std::invalid_argument("Index out of range");

    mData[pos] = value;
  }

  // getters
  int rows() const { return mRows; }
  int cols() const { return mCols; }
  int size() const { return mSize; }
  std::vector<T> data() const { return mData; }

  T& operator()(int i, int j) {
    if(i < 0 || i >= mRows || j < 0 || j >= mCols)
      throw std::out_of_range("Matrix index out of range");

    return mData[i * mCols + j];
  }

  T operator()(int i, int j) const {
    if(i < 0 || i >= mRows || j < 0 || j >= mCols)
      throw std::out_of_range("Matrix index out of range");

    return mData[i * mCols + j];
  }

  template<typename T2>
  Matrix& operator+=(const Matrix<T2>& other) {
    static_assert(std::is_convertible<T2, T>::value, "Incompatible typing");

    if(mRows != other.rows() || mCols != other.cols())
      throw std::invalid_argument("Matrix dimensions must be equal");

    for(int i = 0; i < mSize; i++) mData[i] += static_cast<T>(other.data()[i]);

    return *this;
  }

  template<typename T2>
  Matrix& operator-=(const Matrix<T2>& other) {
    static_assert(std::is_convertible<T2, T>::value, "Incompatible typing");

    if(mRows != other.rows() || mCols != other.cols())
      throw std::invalid_argument("Matrix dimensions must be equal");

    for(int i = 0; i < mSize; i++) mData[i] -= static_cast<T>(other.data()[i]);

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
  typedef typename std::common_type_t<T1, T2> T3;

  if(a.rows() != b.rows() || a.cols() != b.cols())
    throw std::invalid_argument("Matrix dimensions must be equal");

  Matrix<T3> result(a.rows(), a.cols());

  for(int i = 0; i < a.size(); i++) {
    result.setData(i, static_cast<T3>(a.data()[i]) + static_cast<T3>(b.data()[i]));
  }

  return result;
}

template<typename T1, typename T2>
auto operator-(const Matrix<T1>& a, const Matrix<T2>& b) {
  typedef typename std::common_type_t<T1, T2> T3;

  if(a.rows() != b.rows() || a.cols() != b.cols())
    throw std::invalid_argument("Matrix dimensions must be equal");

  Matrix<T3> result(a.rows(), b.cols());

  for(int i = 0; i < a.size(); i++) {
    result.setData(i, static_cast<T3>(a.data()[i] - static_cast<T3>(b.data()[i])));
  }

  return result;
}

}

#endif