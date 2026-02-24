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
  Transform() : mPitch(0.0), mYaw(0.0), mPosition({0.0, 0.0, 0.0}) {} // default
  Transform(double p, double y) : mPitch(p), mYaw(y), mPosition({0.0, 0.0, 0.0}) {} // JUST rotation
  Transform(double p, double y, double3 pos) : mPitch(p), mYaw(y), mPosition(pos) {} // rotation AND translation
  Transform(double3 pos) : mPitch(0.0), mYaw(0.0), mPosition(pos) {} // JUST translation

  double Pitch() const;
  double Yaw() const;
  double3 Position() const;

  void setRotation(double y, double p);
  void setPosition(double3 pos);

  double3 ToWorldPoint(const double3& p) const;
  Matrix GetBasisMatrix() const;

  static double3 TransformVector(const Matrix& m, const double3& v);

private:
  double mPitch;
  double mYaw;

  double3 mPosition;
};

double3 VertexToScreen(const double3& vertex, const Transform& transform, const double2& pixels, double fov);

} // namespace math


#endif // TRANSFORM_H