#ifndef DOUBLE3_H
#define DOUBLE3_H

namespace math {

union double3 {
  struct { double x, y, z; };
  struct { double r, g, b; };

  double3(double a, double b, double c) : x(a), y(b), z(c) {}

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

}

#endif