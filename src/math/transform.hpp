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
  Transform() : pitch(0.0), yaw(0.0), position({0.0, 0.0, 0.0}) {} // default
  Transform(double p, double y) : pitch(p), yaw(y), position({0.0, 0.0, 0.0}) {} // JUST rotation
  Transform(double p, double y, double3 pos) : pitch(p), yaw(y), position(pos) {} // rotation AND translation
  Transform(double3 pos) : pitch(0.0), yaw(0.0), position(pos) {} // JUST translation

  double Pitch() const;
  double Yaw() const;
  double3 Position() const;

  void setPitch(double p);
  void setYaw(double y);
  void setPosition(double3 pos);

  double3 ToWorldPoint(const double3& p) const;
  Matrix GetBasisMatrix() const;

  static double3 TransformVector(const Matrix& m, const double3& v);

private:
  double pitch;
  double yaw;

  double3 position;
};

double2 WorldToScreen(const double3& point, const Transform& transform, const double2& pixels, const double& fov);

} // namespace math


#endif // TRANSFORM_H