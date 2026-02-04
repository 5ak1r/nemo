#include "qr_algorithm.hpp"

namespace math {
namespace qr {

double WilkinsonShift(const Matrix& mat) {
  int n = mat.rows();

  double p = mat(n - 2, n - 2);
  double q = mat(n - 2, n - 1);
  double r = mat(n - 1, n - 2);
  double s = mat(n - 1, n - 1);

  double delta = (p - s) / 2.0;
  double sign = delta >= 0 ? 1.0 : -1.0;

  double denominator = delta + sign * std::sqrt(delta * delta + q * r);

  if (std::abs(denominator) < std::numeric_limits<double>::epsilon()) return s;

  return s - (q * r) / denominator;
}

// https://en.wikipedia.org/wiki/Givens_rotation
std::pair<double, double> GivensRotation(const double& x, const double& y) {
  if (y == 0)
    return { 1.0, 0.0 };

  double r = std::hypot(x, y); // use hypot in case of over/underflow

  double c = x / r;
  double s = -y / r;

  return { c, s };
}

Matrix QRStep(const Matrix& mat) {
}

std::vector<std::complex<double>> QRAlgorithm(const Matrix& mat) {

}

} // namespace qr
} // namespace math
