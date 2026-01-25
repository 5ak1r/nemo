#include "hessenberg.hpp"
#include "matrix_helpers.hpp"

namespace math {
namespace hessenberg {

std::vector<double> Omega(const std::vector<double>& aPrime) {
  double norm = vector::Norm(aPrime);
  std::vector<double> e = vector::StandardBasis(0, aPrime.size());
  std::vector<double> eNorm = vector::Multiply(e, norm);

  double sign = aPrime[0] <= 0.0 ? -1.0 : 1.0;

  return vector::Add(eNorm, vector::Multiply(sign, aPrime));
}

Matrix HouseholderMatrix(const Matrix& mat) {
  Matrix noRow = matrix::RemoveMatrixRow(mat, 0);
  const std::vector<double>& aPrime = noRow.getCol(0);

  int size = aPrime.size();
  Matrix I = Matrix::identity(size);

  Matrix w = Matrix(size, 1, Omega(aPrime));
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

Matrix UpperHessenbergMatrix(const Matrix& mat) {

}

} // namespace hessenberg
} // namespace math
