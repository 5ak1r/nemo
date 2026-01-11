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
auto Omega(const std::vector<T>& aPrime) {
  static_assert(std::is_arithmetic<T>::value, "Not an arithmetic data type");

  using T3 = std::common_type_t<T, double>;

  double norm = vector::Norm(aPrime);
  std::vector<T3> e = vector::StandardBasis(0, aPrime.size());
  std::vector<T3> eNorm = vector::Multiply(e, norm);

  T sign = aPrime[0] <= T{} ? T{-1} : T{1};

  return vector::Add(eNorm, vector::Multiply(sign, aPrime));
}

template<typename T>
auto HouseholderMatrix(const std::vector<T>& aPrime) {
  using T3 = std::common_type_t<T, double>;

  int size = aPrime.size();

  Matrix<T3> I = Matrix<T>::identity(size);

  Matrix<T3> w = Matrix<T3>(aPrime.size(), 1, Omega(aPrime));
  Matrix<T3> wT = w.transpose();

  T3 wNorm = static_cast<T3>(vector::Norm(w.data()));
  T3 wNorm2 = wNorm * wNorm;

  Matrix<T3> result = I - 2.0 * ((1.0 / wNorm2) * (w * wT));

  return result;
}

template<typename T>
auto BlockMatrix(const Matrix<T>& mat, const int& amount) {
  if (!mat.isSquare())
    throw std::invalid_argument("Cannot compute the block matrix of a non-square matrix");

  Matrix<T> block(mat.rows() + amount, mat.cols() + amount);

  for (int i = 0; i < amount; i++) block(i, i) = T{1};

  for (int i = 0; i < mat.rows(); i++) {
    for (int j = 0; j < mat.cols(); j++) {
      block(i + amount, j + amount) = mat(i, j);
    }
  }

  return block;
}

template<typename T>
auto UpperHessenbergMatrix(const Matrix<T>& mat) {

}

}
}

#endif