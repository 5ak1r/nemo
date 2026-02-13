#ifndef DOUBLE2_H
#define DOUBLE2_H

namespace math {

struct double2 {
  double x, y;

  double2() : x(0.0), y(0.0) {}
  double2(double a, double b): x(a), y(b) {}
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

} // namespace math

#endif // DOUBLE2_H