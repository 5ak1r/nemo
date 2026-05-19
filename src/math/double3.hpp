#ifndef DOUBLE3_H
#define DOUBLE3_H

#include <cmath>
#include <ostream>
#include <vector>

namespace math {

struct double3 {
  double x, y, z;

  double3() : x(0.0), y(0.0), z(0.0) {}
  double3(double a) : x(a), y(a), z(a) {}
  double3(double a, double b, double c) : x(a), y(b), z(c) {}
  double3(std::vector<double> vec) {
    if (vec.size() != 3)
      throw std::invalid_argument("vector must be length 3");

    x = vec[0];
    y = vec[1];
    z = vec[2];
  }

  double getLength() const {
    return std::sqrt(x * x + y * y + z * z);
  }

  double3 getNormalized() const {
    double length = getLength();

    if (length == 0.0) return {0.0, 0.0, 0.0};

    return {x / length, y / length, z / length};
  }
};

inline double3 operator-(const double3& a, const double3& b) {
  return double3(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline double3 operator-(const double3& a) {
  return double3(-a.x, -a.y, -a.z);
}

inline double3 operator+(const double3& a, const double3& b) {
  return double3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline double3 operator*(const double3& a, const double3& b) {
  return double3(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline double3 operator/(const double3& a, const double3& b) {
  return double3(a.x / b.x, a.y / b.y, a.z / b.z);
}

inline double3 operator*(const double& scalar, const double3& a) {
  return double3(scalar * a.x, scalar * a.y, scalar * a.z);
}

inline double3 operator/(const double3& a, const double& scalar) {
  return double3(a.x / scalar, a.y / scalar, a.z / scalar);
}

inline std::ostream& operator<<(std::ostream& os, const double3& a) {
  os << "{ " << a.x << ", " << a.y << ", " << a.z << " }";

  return os;
}

} // namespace math

#endif // DOUBLE3_H