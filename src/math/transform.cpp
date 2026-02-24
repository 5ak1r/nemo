#include "transform.hpp"

namespace math {

double Transform::Pitch() const {
  return mPitch;
}

double Transform::Yaw() const {
  return mYaw;
}

double3 Transform::Position() const {
  return mPosition;
}

void Transform::setRotation(double y, double p) {
  mYaw = y;
  mPitch = p;
}

void Transform::setPosition(double3 pos) {
  mPosition = pos;
}

double3 Transform::ToWorldPoint(const double3& p) const {
  Matrix h = GetBasisMatrix();

  return TransformVector(h, p) + mPosition;
}

Matrix Transform::GetBasisMatrix() const {
  Matrix bYaw(3, 3, {std::cos(mYaw), 0.0, std::sin(mYaw), 0.0, 1.0, 0.0, -std::sin(mYaw), 0.0, std::cos(mYaw)});
  Matrix bPitch(3, 3, {1, 0, 0, 0, std::cos(mPitch), -std::sin(mPitch), 0, std::sin(mPitch), std::cos(mPitch)});

  return bPitch * bYaw;
}

double3 Transform::TransformVector(const Matrix& m, const double3& v) {
  Matrix vTemp(v);
  Matrix result = m * vTemp;

  return {result(0), result(1), result(2)};
}

double3 VertexToScreen(const double3& vertex, const Transform& transform, const double2& pixels, double fov) {
  double3 vertexWorld = transform.ToWorldPoint(vertex);

  double screenHeight = std::tan(fov / 2) * 2;
  double pixelsPerWorldUnit = pixels.y / screenHeight / vertexWorld.z;

  double2 pixelOffset = pixelsPerWorldUnit * double2(vertexWorld.x, vertexWorld.y);
  double2 vertexScreen = pixels / 2 + pixelOffset;

  return {vertexScreen.x, vertexScreen.y, vertexWorld.z};
}

} // namespace math