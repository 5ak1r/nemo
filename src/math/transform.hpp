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
  Transform() : mPitch(0.0), mYaw(0.0), mPosition(double3(0.0)) {} // default
  Transform(const double2& yp) : mPitch(yp.x), mYaw(yp.y), mPosition(double3(0.0)) {} // JUST rotation
  Transform(const double2& yp, const double3& pos) : mPitch(yp.x), mYaw(yp.y), mPosition(pos) {} // rotation AND translation
  Transform(const double3& pos) : mPitch(0.0), mYaw(0.0), mPosition(pos) {} // JUST translation

  double getPitch() const;
  double getYaw() const;
  double3 getPosition() const;

  void setRotation(double pitch, double yaw);
  void setPitch(double pitch);
  void setYaw(double yaw);
  void setPosition(double3 pos);
  void setXPosition(double x);
  void setYPosition(double y);
  void setZPosition(double z);

  void addPitch(double amount);
  void addYaw(double amount);
  void addPosition(double3 amount);
  void addXPosition(double amount);
  void addYPosition(double amount);
  void addZPosition(double amount);

  double3 ToWorldPoint(const double3& p) const;
  double3 ToLocalPoint(const double3& p) const;
  Matrix GetBasisMatrix() const;
  Matrix GetInverseBasisMatrix() const;

  static double3 TransformVector(const Matrix& m, const double3& v);

private:
  double mYaw;
  double mPitch;

  double3 mPosition;
};

double3 VertexToScreen(const double3& vertex, const Transform& transform, const graphics::Camera& camera, int width, int height);

} // namespace math


#endif // TRANSFORM_H