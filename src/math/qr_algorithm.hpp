#ifndef QR_ALGORITHM_H
#define QR_ALGORITHM_H

#include <iostream>
#include <cmath>
#include <complex>
#include <limits>
#include <utility>
#include <vector>

#include "hessenberg.hpp"
#include "matrix.hpp"
#include "matrix_helpers.hpp"
#include "vector.hpp"

namespace math {
namespace qr {

double WilkinsonShift(const Matrix& mat);
std::pair<double, double> GivensRotation(const double& x, const double& y);
std::pair<Matrix, Matrix> QRDecomposition(const Matrix& mat);
Matrix QRAlgorithm(const Matrix& mat);

} // namespace QR
} // namespace math

#endif