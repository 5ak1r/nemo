#ifndef LU_DECOMP_H
#define LU_DECOMP_H

#include <cmath>
#include <stdexcept>

#include "matrix.hpp"

namespace math {

struct PLU {
  Matrix pivot;
  Matrix lower;
  Matrix upper;
  int swaps;
};

// modified from https://en.wikipedia.org/wiki/LU_decomposition
PLU DoolittleLU(const Matrix& mat);

} // namespace math

#endif // LU_DECOMP_H