#include "transform.hpp"

namespace math {

double Transform::Pitch() const {
  return pitch;
}

double Transform::Yaw() const {
  return yaw;
}

double3 Transform::Position() const {
  return position;
}

void Transform::setPitch(double p) {
  pitch = p;
}

void Transform::setYaw(double y) {
  yaw = y;
}

void Transform::setPosition(double3 pos) {
  position = pos;
}

double3 Transform::ToWorldPoint(const double3& p) const {
  Matrix h = GetBasisMatrix();

  return TransformVector(h, p) + position;
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

double2 WorldToScreen(const double3& point, const Transform& transform, const double2& pixels, const double& fov) {
  double3 pointWorld = transform.ToWorldPoint(point);

  double screenHeight = std::tan(fov / 2) * 2;
  double pixelsPerWorldUnit = pixels.y / screenHeight / pointWorld.z;

  double2 pixelOffset = pixelsPerWorldUnit * double2(pointWorld.x, pointWorld.y);

  return pixels / 2.0 + pixelOffset;
}

} // namespace math