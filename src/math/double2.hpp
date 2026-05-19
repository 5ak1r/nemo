#ifndef DOUBLE2_H
#define DOUBLE2_H

#include <ostream>
#include <stdexcept>
#include <vector>

#include "double3.hpp"

namespace math {

struct double2 {
  double x, y;

  double2() : x(0.0), y(0.0) {}
  double2(double a) : x(a), y(a) {}
  double2(double a, double b): x(a), y(b) {}
  double2(const double3& a) : x(a.x), y(a.y) {}
  double2(std::vector<double> vec) {
    if (vec.size() != 2)
      throw std::invalid_argument("vector must be length 2");

    x = vec[0];
    y = vec[1];
  }

  double getLength() const {
    return std::sqrt(x * x + y * y);
  }

  double2 getNormalized() const {
    double length = getLength();

    if (length == 0.0) return {0.0, 0.0};

    return {x / length, y / length};
  }
};

inline double2 operator-(const double2& a, const double2& b) {
  return double2(a.x - b.x, a.y - b.y);
}

inline double2 operator-(const double2& a) {
  return double2(-a.x, -a.y);
}

inline double2 operator+(const double2& a, const double2& b) {
  return double2(a.x + b.x, a.y + b.y);
}

inline double2 operator*(const double2& a, const double2& b) {
  return double2(a.x * b.x, a.y * b.y);
}

inline double2 operator/(const double2& a, const double2& b) {
  return double2(a.x / b.x, a.y / b.y);
}

inline double2 operator*(const double& scalar, const double2& a) {
  return double2(scalar * a.x, scalar * a.y);
}

inline double2 operator/(const double2& a, const double& scalar) {
  return double2(a.x / scalar, a.y / scalar);
}

inline std::ostream& operator<<(std::ostream& os, const double2& a) {
  os << "{ " << a.x << ", " << a.y << " }";

  return os;
}

} // namespace math

#endif // DOUBLE2_H