#include "transform.hpp"

namespace math {

double Transform::Pitch() const {
  return pitch;
}

double Transform::Yaw() const {
  return yaw;
}

void Transform::setPitch(double p) {
  pitch = p;
}

void Transform::setYaw(double y) {
  yaw = y;
}

double3 Transform::ToWorldPoint(const double3& p) const {
  Matrix h = GetBasisMatrix();

  return TransformVector(h, p);
}

Matrix Transform::GetBasisMatrix() const {
  Matrix mYaw(3, 3, {std::cos(yaw), 0.0, std::sin(yaw), 0.0, 1.0, 0.0, -std::sin(yaw), 0.0, std::cos(yaw)});
  Matrix mPitch(3, 3, {1, 0, 0, 0, std::cos(pitch), -std::sin(pitch), 0, std::sin(pitch), std::cos(pitch)});

  return mPitch * mYaw;
}

double3 Transform::TransformVector(const Matrix& m, const double3& v) {
  Matrix vTemp(v);
  Matrix result = m * vTemp;

  return {result(0), result(1), result(2)};
}

double2 WorldToScreen(const double3& point, const Transform& transform, const double2& pixels) {
  double3 pointWorld = transform.ToWorldPoint(point);

  double screenHeight = 5.0;
  double pixelsPerWorldUnit = pixels.y / screenHeight;

  double2 pixelOffset = pixelsPerWorldUnit * double2(pointWorld.x, pointWorld.y);

  return pixels / 2.0 + pixelOffset;
}

} // namespace math