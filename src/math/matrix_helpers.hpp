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
auto Determinant(const Matrix<T>& mat) {
  PLU<T> plu = DoolittleLU<T>(mat);
  auto& U = plu.upper;

  using T3 = std::common_type_t<T, float>;

  T3 res = T3{1};
  for (int i = 0; i < mat.rows(); i++) {
    res *= U(i, i);
  }

  if (plu.swaps % 2 != 0) res = -res;

  return res;
}

template<typename T>
Matrix<T> Transpose(const Matrix<T>& mat) {
  std::vector<T> transposed;
  transposed.reserve(mat.size());

  if (mat.rows() == 1 || mat.cols() == 1)
    return Matrix<T>(mat.cols(), mat.rows(), mat.data());

  for (int i = 0; i < mat.cols(); i++) {
    for (int j = 0; j < mat.rows(); j++) {
      transposed.push_back(mat(j, i));
    }
  }

  return Matrix<T>(mat.cols(), mat.rows(), transposed);
}

template<typename T>
Matrix<T> Adjugate(const Matrix<T>& mat) {
  if (!mat.isSquare())
    throw std::invalid_argument("Cannot compute the cofactor of a non-square matrix");

  Matrix<T> result(mat.rows(), mat.cols());

  for (int i = 0; i < mat.size(); i++) {
    Matrix<T> temp(mat.rows() - 1, mat.cols() - 1);
    int pos = 0;

    int iRow = mat.whichRow(i);
    int iCol = mat.whichCol(i);

    for (int j = 0; j < mat.size(); j++) {
      int jRow = mat.whichRow(j);
      int jCol = mat.whichCol(j);

      if (iRow != jRow && iCol != jCol) {
        temp(pos++) = mat(j);
      }
    }

    auto tempDet = Determinant(temp);
    if ((iRow + iCol) % 2 != 0) tempDet = -tempDet;

    result(i) = tempDet;
  }

  return result;
}

template<typename T>
Matrix<T> Cofactors(const Matrix<T>& mat) {
  if (!mat.isSquare())
    throw std::invalid_argument("Cannot compute the adjugate of a non-square matrix");

  return Transpose(Adjugate(mat));
}

template<typename T>
auto Inverse(const Matrix<T>& mat) {
  if (!mat.isSquare())
    throw std::invalid_argument("Cannot compute the inverse of a non-square matrix");

  auto det = Determinant(mat);

  if (det == 0)
    throw std::invalid_argument("Cannot compute the inverse of a matrix with 0 determinant");

  auto det_recip = 1.0 / det;
  auto inverse = det_recip * Adjugate(mat);

  return inverse;
}

// modified from https://www.geeksforgeeks.org/cpp/cpp-matrix-multiplication/
template<typename T1, typename T2>
auto Multiply(const Matrix<T1>& a, const Matrix<T2>& b) {
  using T3 = std::common_type_t<T1, T2>;

  std::vector<T3> result;
  result.reserve(a.rows() * b.cols());

  for (int i = 0; i < a.rows(); i++) {
    for (int j = 0; j < b.cols(); j++) {
      T3 sum = T3{};

      for (int k = 0; k < a.cols(); k++) {
        sum += static_cast<T3>(a(i, k)) * static_cast<T3>(b(k, j));
      }

      result.push_back(sum);
    }
  }

  return Matrix<T3>(a.rows(), b.cols(), std::move(result));
}

template<typename T>
Matrix<T> RemoveMatrixRow(const Matrix<T>& mat, int idx) {
  if (idx < 0 || idx > mat.rows())
    throw std::invalid_argument("Row index out of bounds");

  std::vector<T> result;
  result.reserve((mat.rows() - 1) * mat.cols());

  std::vector<T> data = mat.data();

  // insert everything up to the row, and then skip the row and insert and rest
  result.insert(result.end(), data.begin(), data.begin() + idx * mat.cols());
  result.insert(result.end(), data.begin() + (idx + 1) * mat.cols(), data.end());

  return Matrix<T>(mat.rows() - 1, mat.cols(), result);
}

template<typename T>
Matrix<T> RemoveMatrixCol(const Matrix<T>& mat, int idx) {
  if (idx < 0 || idx > mat.cols())
    throw std::invalid_argument("Column index out of bounds");

  std::vector<T> result;
  result.reserve(mat.rows() * (mat.cols() - 1));

  for (int row = 0; row < mat.rows(); row++) {
    for (int col = 0; col < mat.cols(); col++) {
      if (col == idx) continue;
      result.push_back(mat(row, col));
    }
  }

  return Matrix<T>(mat.rows(), mat.cols() - 1, result);
}

}
}