#ifndef HESSENBERG_H
#define HESSENBERG_H

#include <stdexcept>
#include <type_traits>
#include <vector>

#include "matrix.hpp"
#include "vector.hpp"

// https://en.wikipedia.org/wiki/Hessenberg_matrix
namespace math {
namespace hessenberg {

template<typename T>
auto Omega(const std::vector<T>& vec) {
  static_assert(std::is_arithmetic<T>::value, "Not an arithmetic data type");

  using T3 = std::common_type_t<T, double>;

  double norm = vector::Norm(vec);
  std::vector<T3> e = vector::StandardBasis(0, vec.size());
  std::vector<T3> eNorm = vector::Multiply(e, norm);

  if (vec[0] == T{})
    return vector::Subtract(eNorm, vec);

  return vector::Add(eNorm, vector::Multiply(vec[0] / std::abs(vec[0]), vec));
}

template<typename T>
auto HouseholderMatrix(const Matrix<T>& mat) {
  if (!mat.isSquare())
    throw std::invalid_argument("Cannot compute householder matrix from a non-square matrix");

  using T3 = std::common_type_t<T, double>;

  int size = mat.rows() - 1;

  Matrix<T> I = Matrix<T>::identity(size);
  std::vector<T> A = mat.rows() == 2 ? std::vector<T>(1, mat(2)) : matrix::RemoveMatrixRow(mat, 0).getCol(0);

  Matrix<T3> w(size, 1, static_cast<std::vector<T3>>(Omega(A)));
  Matrix<T3> wT = w.transpose();

  T3 wNorm = static_cast<T3>(vector::Norm(w.data()));
  T3 wNorm2 = wNorm * wNorm;

  Matrix<T3> result = I - 2.0 * ((1.0 / wNorm2) * (w * wT));

  return result;
}

template<typename T>
auto BlockMatrix(const Matrix<T>& mat) {
  if (!mat.isSquare())
    throw std::invalid_argument("Cannot compute the block matrix of a non-square matrix");

  Matrix<T> block(mat.rows() + 1, mat.cols() + 1);

  block(0) = T{1};

  for (int i = 0; i < mat.rows(); i++) {
    for (int j = 0; j < mat.cols(); j++) {
      block(i + 1, j + 1) = mat(i, j);
    }
  }

  return block;
}


}
}

#endif