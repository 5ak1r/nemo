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
std::pair<double, double> GivensRotation(double x, double y) {
  if (y == 0)
    return { 1.0, 0.0 };

  double r = std::hypot(x, y); // use hypot in case of over/underflow

  double c = x / r;
  double s = -y / r;

  return { c, s };
}

// https://www.math.ucla.edu/~yanovsky/Teaching/Math151B/handouts/GramSchmidt.pdf this one works!
std::pair<Matrix, Matrix> QRDecomposition(const Matrix& mat) {
  int n = mat.rows();

  std::vector<std::vector<double>> es;
  double dot = 0.0;

  for (int j = 0; j < n; j++) {
    std::vector<double> a = mat.getCol(j);
    std::vector<double> u = a;

    for (int i = 0; i < j; i++) {
      double dot = vector::Dot(a, es[i]);
      for (int k = 0; k < n; k++)
        u[k] -= dot * es[i][k];
    }

    double uNorm = vector::Norm(u);

    std::vector<double> e;
    for (int k = 0; k < n; k++)
      e.push_back(u[k] / uNorm);

    es.push_back(e);
  }

  Matrix Q(n, n);
  Matrix R(n, n);

  for (int j = 0; j < n; j++) {
    for (int i = 0; i < n; i++) {
      Q(i, j) = es[j][i];
    }
  }

  for (int j = 0; j < n; j++) {
    for (int i = 0; i <= j; i++) {
      R(i, j) = vector::Dot(mat.getCol(j), es[i]);
    }
  }

  return { Q, R };
}

Matrix QRAlgorithm(const Matrix& mat) {
  if (!mat.isSquare())
    throw std::invalid_argument("must be a Square Matrix");

  Matrix A = mat;

  int maxIterations = 1000;

  for (int i = 0; i < maxIterations; i++) {
    std::pair<Matrix, Matrix> QR = QRDecomposition(A);
    A = QR.second * QR.first;
  }

  return A;
}

} // namespace qr
} // namespace math
