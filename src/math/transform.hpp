#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <cmath>
#include <iostream>
#include "double2.hpp"
#include "double3.hpp"
#include "matrix.hpp"

namespace math {

class Transform {
public:
  Transform() : pitch(0.0), yaw(0.0) {}
  Transform(double p, double y) : pitch(p), yaw(y) {}

  double Pitch() const;
  double Yaw() const;
  void setPitch(double p);
  void setYaw(double y);

  double3 ToWorldPoint(const double3& p) const;
  Matrix GetBasisMatrix() const;

  static double3 TransformVector(const Matrix& m, const double3& v);

private:
  double pitch;
  double yaw;
};

double2 WorldToScreen(const double3& point, const Transform& transform, const double2& pixels);

} // namespace math


#endif // TRANSFORM_H