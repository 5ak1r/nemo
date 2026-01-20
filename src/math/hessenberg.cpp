#include "hessenberg.hpp"

namespace math {
namespace hessenberg {

std::vector<double> Omega(const std::vector<double>& aPrime) {
  double norm = vector::Norm(aPrime);
  std::vector<double> e = vector::StandardBasis(0, aPrime.size());
  std::vector<double> eNorm = vector::Multiply(e, norm);

  double sign = aPrime[0] <= 0.0 ? -1.0 : 1.0;

  return vector::Add(eNorm, vector::Multiply(sign, aPrime));
}

Matrix HouseholderMatrix(const std::vector<double>& aPrime) {
  int size = aPrime.size();

  Matrix I = Matrix::identity(size);

  Matrix w = Matrix(aPrime.size(), 1, Omega(aPrime));
  Matrix wT = w.transpose();

  double wNorm = vector::Norm(w.data());
  double wNorm2 = wNorm * wNorm;

  Matrix result = I - 2.0 * ((1.0 / wNorm2) * (w * wT));

  return result;
}

Matrix BlockMatrix(const Matrix& mat, const int& amount) {
  if (!mat.isSquare())
    throw std::invalid_argument("Cannot compute the block matrix of a non-square matrix");

  Matrix block(mat.rows() + amount, mat.cols() + amount);

  for (int i = 0; i < amount; i++) block(i, i) = 1.0;

  for (int i = 0; i < mat.rows(); i++) {
    for (int j = 0; j < mat.cols(); j++) {
      block(i + amount, j + amount) = mat(i, j);
    }
  }

  return block;
}

} // namespace hessenberg
} // namespace math
