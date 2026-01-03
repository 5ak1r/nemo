#include <cassert>
#include <stdexcept>
#include <vector>

#include "lu_decomp.hpp"

namespace math {

template<typename T>
struct Matrix;

namespace matrix {

// LU Decomposition! Much faster :)
template<typename T>
auto determinant(const Matrix<T>& matrix) {
  PLU<T> plu = DoolittleLU<T>(matrix);
  auto& U = plu.upper;

  using T3 = std::common_type_t<T, float>;

  T3 res = T3{1};
  for (int i = 0; i < matrix.rows(); i++) {
    res *= U(i, i);
  }

  if (plu.swaps % 2 != 0) res = -res;

  return res;
}

template<typename T>
Matrix<T> transpose(const Matrix<T>& matrix) {
  std::vector<T> transposed;
  transposed.reserve(matrix.size());

  if (matrix.rows() == 1 || matrix.cols() == 1)
    return Matrix<T>(matrix.cols(), matrix.rows(), matrix.data());

  for (int i = 0; i < matrix.cols(); i++) {
    for (int j = 0; j < matrix.rows(); j++) {
      transposed.push_back(matrix(j, i));
    }
  }

  return Matrix<T>(matrix.cols(), matrix.rows(), transposed);
}

template<typename T>
Matrix<T> adjugate(const Matrix<T>& matrix) {
  if (!matrix.isSquare())
    throw std::invalid_argument("Cannot compute the cofactor of a non-square matrix");

  Matrix<T> result(matrix.rows(), matrix.cols());

  for (int i = 0; i < matrix.size(); i++) {
    Matrix<T> temp(matrix.rows() - 1, matrix.cols() - 1);
    int pos = 0;

    int iRow = matrix.getRow(i);
    int iCol = matrix.getCol(i);

    for (int j = 0; j < matrix.size(); j++) {
      int jRow = matrix.getRow(j);
      int jCol = matrix.getCol(j);

      if (iRow != jRow && iCol != jCol) {
        temp(pos++) = matrix(j);
      }
    }

    auto tempDet = determinant(temp);
    if ((iRow + iCol) % 2 != 0) tempDet = -tempDet;

    result(i) = tempDet;
  }

  return result;
}

template<typename T>
Matrix<T> cofactors(const Matrix<T>& matrix) {
  if (!matrix.isSquare())
    throw std::invalid_argument("Cannot compute the adjugate of a non-square matrix");

  return transpose(adjugate(matrix));
}

template<typename T>
auto inverse(const Matrix<T>& matrix) {
  if (!matrix.isSquare())
    throw std::invalid_argument("Cannot compute the inverse of a non-square matrix");

  auto det = determinant(matrix);

  if (det == 0)
    throw std::invalid_argument("Cannot compute the inverse of a matrix with 0 determinant");

  auto det_recip = 1.0 / det;
  auto inverse = det_recip * adjugate(matrix);

  return inverse;
}

// modified from https://www.geeksforgeeks.org/cpp/cpp-matrix-multiplication/
template<typename T1, typename T2>
auto multiply(const Matrix<T1>& a, const Matrix<T2>& b) {
  using T3 = std::common_type_t<T1, T2>;

  std::vector<T3> result;
  result.reserve(a.rows() * b.cols());

  for (int i = 0; i < a.rows(); i++) {
    for (int j = 0; j < b.cols(); j++) {
      T3 sum = T3{};

      for (int k = 0; k < a.cols(); k++) {
        sum += a(i, k) * b(k, j);
      }

      result.push_back(sum);
    }
  }

  return Matrix<T3>(a.rows(), b.cols(), std::move(result));
}

}
}