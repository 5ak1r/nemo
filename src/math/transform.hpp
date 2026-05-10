#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <cmath>
#include <iostream>

#include "double2.hpp"
#include "double3.hpp"
#include "matrix/matrix.hpp"

// avoid recursive
namespace graphics {
class Camera;
} // namespace graphics

namespace math {

class Transform {
public:
  Transform() : mPitch(0.0), mYaw(0.0), mPosition({0.0, 0.0, 0.0}) {} // default
  Transform(const double2& yp) : mPitch(yp.x), mYaw(yp.y), mPosition({0.0, 0.0, 0.0}) {} // JUST rotation
  Transform(const double2& yp, const double3& pos) : mPitch(yp.x), mYaw(yp.y), mPosition(pos) {} // rotation AND translation
  Transform(const double3& pos) : mPitch(0.0), mYaw(0.0), mPosition(pos) {} // JUST translation

  double Pitch() const;
  double Yaw() const;
  double3 Position() const;

  void setRotation(double y, double p);
  void setPosition(double3 pos);

  void addYaw(double amount);
  void addPitch(double amount);
  void addPosition(double3 amount);

  double3 ToWorldPoint(const double3& p) const;
  double3 ToLocalPoint(const double3& p) const;
  Matrix GetBasisMatrix() const;

  static double3 TransformVector(const Matrix& m, const double3& v);

private:
  double mYaw;
  double mPitch;

  double3 mPosition;
};

double3 VertexToScreen(const double3& vertex, const Transform& transform, const graphics::Camera& camera, int width, int height);

} // namespace math


#endif // TRANSFORM_H