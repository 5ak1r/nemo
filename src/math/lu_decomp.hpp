#ifndef LU_DECOMP_H
#define LU_DECOMP_H

#include <cmath>
#include <stdexcept>
#include <type_traits>

namespace math {

// forward declaration
template<typename T>
struct Matrix;

template<typename T>
struct PLU {
  Matrix<T> pivot;
  Matrix<std::common_type_t<T, double>> lower;
  Matrix<std::common_type_t<T, double>> upper;
  int swaps;
};

// modified from https://en.wikipedia.org/wiki/LU_decomposition
template<typename T>
PLU<T> DoolittleLU(const Matrix<T>& matrix) {
  if (!matrix.isSquare())
    throw std::invalid_argument("Cannot compute the LU decomposition of a non-square matrix");

  int rc = matrix.rows(); // rows = colums for square matrices
  int swaps = 0;
  Matrix<T> pivot = Matrix<T>::identity(rc);

  using T3 = std::common_type_t<T, double>;
  Matrix<T3> result(matrix.rows(), matrix.cols());

  for (int i = 0; i < matrix.size(); i++) {
    result(i) = (double)matrix(i);
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

  Matrix<T3> lower(rc, rc);
  Matrix<T3> upper(rc, rc);

  for (int r = 0; r < rc; r++) {
    for (int c = 0; c < rc; c++) {
      if (r > c) {
        lower(r, c) = result(r, c);
        upper(r, c) = T3{0};
      } else {
        lower(r, c) = (r == c) ? T3{1} : T3{0};
        upper(r, c) = result(r, c);
      }
    }
  }

  return { pivot, lower, upper, swaps };
}

}

#endif