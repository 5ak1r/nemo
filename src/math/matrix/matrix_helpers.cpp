#include "matrix_helpers.hpp"
#include "qr_algorithm.hpp"

namespace math {
namespace matrix {

// LU Decomposition! Much faster :)
double Determinant(const Matrix& mat) {
  PLU plu = DoolittleLU(mat);
  auto& U = plu.upper;

  double res = 1.0;
  for (int i = 0; i < mat.rows(); i++) {
    res *= U(i, i);
  }

  if (plu.swaps % 2 != 0) res = -res;

  return res;
}

Matrix Transpose(const Matrix& mat) {
  std::vector<double> transposed;
  transposed.reserve(mat.size());

  if (mat.rows() == 1 || mat.cols() == 1)
    return Matrix(mat.cols(), mat.rows(), mat.data());

  for (int i = 0; i < mat.cols(); i++) {
    for (int j = 0; j < mat.rows(); j++) {
      transposed.push_back(mat(j, i));
    }
  }

  return Matrix(mat.cols(), mat.rows(), transposed);
}

Matrix Adjugate(const Matrix& mat) {
  if (!mat.isSquare())
    throw std::invalid_argument("cannot compute the cofactor of a non-square matrix");

  Matrix result(mat.rows(), mat.cols());

  for (int i = 0; i < mat.size(); i++) {
    Matrix temp(mat.rows() - 1, mat.cols() - 1);
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

    double tempDet = Determinant(temp);
    if ((iRow + iCol) % 2 != 0) tempDet = -tempDet;

    result(i) = tempDet;
  }

  return result;
}

Matrix Cofactors(const Matrix& mat) {
  if (!mat.isSquare())
    throw std::invalid_argument("cannot compute the adjugate of a non-square matrix");

  return Transpose(Adjugate(mat));
}

Matrix Inverse(const Matrix& mat) {
  if (!mat.isSquare())
    throw std::invalid_argument("cannot compute the inverse of a non-square matrix");

  double det = Determinant(mat);

  if (det == 0.0)
    throw std::invalid_argument("cannot compute the inverse of a matrix with 0 determinant");

  double det_recip = 1.0 / det;
  Matrix inverse = det_recip * Adjugate(mat);

  return inverse;
}

std::vector<std::complex<double>> Eigenvalues(const Matrix &mat) {
  if (!mat.isSquare())
    throw std::invalid_argument("cannot compute the eigenvalues of a non-square matrix");

  int n = mat.rows();

  std::vector<std::complex<double>> eigenvalues;
  eigenvalues.reserve(n);

  Matrix QR = qr::QRAlgorithm(mat);

  int i = 0;
  while(i < n) {
    if (i == n - 1 || std::abs(QR(i + 1, i)) < std::numeric_limits<double>::epsilon()) {
      eigenvalues.push_back(QR(i, i));
      i += 1;
    } else {
      // https://people.math.harvard.edu/~knill/teaching/math21b2004/exhibits/2dmatrices/index.html
      double a = QR(i, i);
      double b = QR(i, i + 1);
      double c = QR(i + 1, i);
      double d = QR(i + 1, i + 1);

      double trace = a + d;
      double det = a * d - b * c;

      std::complex<double> value = (trace * trace) / 4 - det;
      std::complex<double> sqrVal = std::sqrt(value);

      std::complex<double> eValPos = {trace / 2, sqrVal.imag()};
      std::complex<double> eValNeg = {trace / 2, -sqrVal.imag()};

      eigenvalues.push_back(eValPos);
      eigenvalues.push_back(eValNeg);

      i += 2; // skip the next diagonal as it's part of this 2x2;
    }
  }

  return eigenvalues;
}

// modified from https://www.geeksforgeeks.org/cpp/cpp-matrix-multiplication/
Matrix Multiply(const Matrix& a, const Matrix& b) {
  std::vector<double> result;
  result.reserve(a.rows() * b.cols());

  for (int i = 0; i < a.rows(); i++) {
    for (int j = 0; j < b.cols(); j++) {
      double sum = 0.0;

      for (int k = 0; k < a.cols(); k++) {
        sum += a(i, k) * b(k, j);
      }

      result.push_back(sum);
    }
  }

  return Matrix(a.rows(), b.cols(), std::move(result));
}

Matrix RemoveMatrixRow(const Matrix& mat, int idx) {
  if (idx < 0 || idx > mat.rows())
    throw std::invalid_argument("row index out of bounds");

  std::vector<double> result;
  result.reserve((mat.rows() - 1) * mat.cols());

  std::vector<double> data = mat.data();

  // insert everything up to the row, and then skip the row and insert and rest
  result.insert(result.end(), data.begin(), data.begin() + idx * mat.cols());
  result.insert(result.end(), data.begin() + (idx + 1) * mat.cols(), data.end());

  return Matrix(mat.rows() - 1, mat.cols(), result);
}

Matrix RemoveMatrixCol(const Matrix& mat, int idx) {
  if (idx < 0 || idx > mat.cols())
    throw std::invalid_argument("column index out of bounds");

  std::vector<double> result;
  result.reserve(mat.rows() * (mat.cols() - 1));

  for (int row = 0; row < mat.rows(); row++) {
    for (int col = 0; col < mat.cols(); col++) {
      if (col == idx) continue;
      result.push_back(mat(row, col));
    }
  }

  return Matrix(mat.rows(), mat.cols() - 1, result);
}

} // namespace matrix
} // namespace math