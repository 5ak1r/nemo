#include "transform.hpp"
#include "../graphics/camera.hpp"

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
  mPitch = y;
  mYaw = p;
}

void Transform::setPosition(double3 pos) {
  mPosition = pos;
}

void Transform::addPitch(double amount) {
  mPitch += amount;
}

void Transform::addYaw(double amount) {
  mYaw += amount;
}

void Transform::addPosition(double3 amount) {
  mPosition = mPosition + amount;
}

double3 Transform::ToWorldPoint(const double3& p) const {
  Matrix h = GetBasisMatrix();

  return TransformVector(h, p) + mPosition;
}

double3 Transform::ToLocalPoint(const double3& p) const {
  return p - mPosition;
}

Matrix Transform::GetBasisMatrix() const {
  Matrix bYaw(3, 3, {std::cos(mPitch), 0.0, std::sin(mPitch), 0.0, 1.0, 0.0, -std::sin(mPitch), 0.0, std::cos(mPitch)});
  Matrix bPitch(3, 3, {1, 0, 0, 0, std::cos(mYaw), -std::sin(mYaw), 0, std::sin(mYaw), std::cos(mYaw)});

  return bPitch * bYaw;
}

double3 Transform::TransformVector(const Matrix& m, const double3& v) {
  Matrix vTemp(v);
  Matrix result = m * vTemp;

  return {result(0), result(1), result(2)};
}

double3 VertexToScreen(const double3& vertex, const Transform& transform, const graphics::Camera& camera, int width, int height) {
  double3 vertexWorld = transform.ToWorldPoint(vertex);
  double3 vertexView = camera.transform.ToLocalPoint(vertexWorld);

  double screenHeight = std::tan(camera.fov / 2) * 2;
  double pixelsPerWorldUnit = height / screenHeight / vertexView.z;

  double2 pixelOffset = pixelsPerWorldUnit * double2(vertexView.x, vertexView.y);
  double2 vertexScreen = double2(width, height) / 2 + pixelOffset;

  return {vertexScreen.x, vertexScreen.y, vertexView.z};
}

} // namespace math