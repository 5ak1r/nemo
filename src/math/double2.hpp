#ifndef DOUBLE2_H
#define DOUBLE2_H

namespace math {

struct double2 {
  double x, y;

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

}

#endif