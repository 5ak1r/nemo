#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <cmath>
#include <iostream>
#include "double2.hpp"
#include "double3.hpp"
#include "matrix/matrix.hpp"

namespace math {

class Transform {
public:
  Transform() : mYaw(0.0), mPitch(0.0), mPosition({0.0, 0.0, 0.0}) {} // default
  Transform(const double2& yp) : mYaw(yp.x), mPitch(yp.y), mPosition({0.0, 0.0, 0.0}) {} // JUST rotation
  Transform(const double2& yp, const double3& pos) : mYaw(yp.x), mPitch(yp.y), mPosition(pos) {} // rotation AND translation
  Transform(const double3& pos) : mYaw(0.0), mPitch(0.0), mPosition(pos) {} // JUST translation

  double Yaw() const;
  double Pitch() const;
  double3 Position() const;

  void setRotation(double y, double p);
  void setPosition(double3 pos);

  void addYaw(double amount);
  void addPitch(double amount);
  void addPosition(double3 amount);

  double3 ToWorldPoint(const double3& p) const;
  Matrix GetBasisMatrix() const;

  static double3 TransformVector(const Matrix& m, const double3& v);

private:
  double mPitch;
  double mYaw;

  double3 mPosition;
};

double3 VertexToScreen(const double3& vertex, const Transform& transform, int width, int height, double fov);

} // namespace math


#endif // TRANSFORM_H