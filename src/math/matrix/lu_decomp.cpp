#include "lu_decomp.hpp"

namespace math {

// modified from https://en.wikipedia.org/wiki/LU_decomposition
PLU DoolittleLU(const Matrix& mat) {
  if (!mat.isSquare())
    throw std::invalid_argument("Cannot compute the LU decomposition of a non-square matrix");

  int rc = mat.rows(); // rows = colums for square matrices
  int swaps = 0;
  Matrix pivot = Matrix::identity(rc);

  Matrix result(mat.rows(), mat.cols());

  for (int i = 0; i < mat.size(); i++) {
    result(i) = (double)mat(i);
  }

  for (int i = 0; i < rc; i++) {
    int pivotIdx = i;
    double max = 0.0f;

    for (int k = i; k < rc; k++) {
      if (std::abs(result(k, i)) > max) {
        max = std::abs(result(k, i));
        pivotIdx = k;
      }
    }

    if (max < 1e-16) // account for floating point error
      throw std::invalid_argument("Matrix is singular");

    if (pivotIdx != i) {
      result.swapRows(i, pivotIdx);
      pivot.swapRows(i, pivotIdx);
      swaps++;
    }

    for (int j = i + 1; j < rc; j++) {
      result(j, i) /= result(i, i);

      for (int k = i + 1; k < rc; k++)
        result(j, k) -= result(j, i) * result(i, k);
    }
  }

  Matrix lower(rc, rc);
  Matrix upper(rc, rc);

  for (int r = 0; r < rc; r++) {
    for (int c = 0; c < rc; c++) {
      if (r > c) {
        lower(r, c) = result(r, c);
        upper(r, c) = 0.0;
      } else {
        lower(r, c) = (r == c) ? 1.0 : 0.0;
        upper(r, c) = result(r, c);
      }
    }
  }

  return { pivot, lower, upper, swaps };
}

} // namespace math