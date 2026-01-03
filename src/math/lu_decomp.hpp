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
  Matrix<std::common_type_t<T, float>> lower;
  Matrix<std::common_type_t<T, float>> upper;
};

// modified from https://en.wikipedia.org/wiki/LU_decomposition
template<typename T>
PLU<T> DoolittleLU(const Matrix<T>& matrix) {
  if (!matrix.isSquare())
    throw std::invalid_argument("Cannot compute the LU decomposition of a non-square matrix");

  int rc = matrix.rows(); // rows = colums for square matrices
  Matrix<T> pivot = Matrix<T>::identity(rc);

  using T3 = std::common_type_t<T, float>;
  Matrix<T3> result(matrix.rows(), matrix.cols());

  for (int i = 0; i < matrix.size(); i++) {
    result(i) = (float)matrix(i);
  }

  for (int i = 0; i < rc; i++) {
    int pivotIdx = i;
    float max = 0.0f;

    for (int k = i; k < rc; k++) {
      if (std::abs(result(k, i)) > max) {
        max = std::abs(result(k, i));
        pivotIdx = k;
      }
    }

    if (max < 0.000001f) // account for floating point error
      throw std::invalid_argument("Matrix is singular");

    if (pivotIdx != i) {
      result.swapRows(i, pivotIdx);
      pivot.swapRows(i, pivotIdx);
    }

    for (int j = i + 1; j < rc; j++) {
      result(j, i) /= result(i, i);

      for (int k = i + 1; k < rc; k++)
        result(j, k) -= result(j, i) * result(i, k);
    }
  }

  Matrix<T3> lower(rc, rc);
  Matrix<T3> upper(rc, rc);

  for (int c = 0; c < rc; c++) {
    for (int r = 0; r < rc; r++) {
      if (c > r) {
        lower(c, r) = result(c, r);
        upper(c, r) = T3{};
      } else {
        lower(c, r) = (c == r) ? T3{1} : T3{0};
        upper(c, r) = result(c, r);
      }
    }
  }

  return { pivot, lower, upper };
}

}

#endif