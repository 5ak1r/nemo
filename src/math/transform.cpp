#include "transform.hpp"

namespace math {

double Transform::Yaw() const {
  return yaw;
}

void Transform::setYaw(double y) {
  yaw = y;
}

double3 Transform::ToWorldPoint(const double3& p) const {
  hats h = GetBasisVectors();

  return TransformVector(h, p);
}

hats Transform::GetBasisVectors() const {
  hats h;
  h.ihat = {std::cos(yaw), 0.0, std::sin(yaw)};
  h.jhat = {0.0, 1.0, 0.0};
  h.khat = {-std::sin(yaw), 0.0, std::cos(yaw)};

  return h;
}

double3 Transform::TransformVector(hats h, double3 v) {
  return v.x * h.ihat + v.y * h.jhat + v.z * h.khat;
}

double2 WorldToScreen(const double3& point, const Transform& transform, const double2& pixels) {
  double3 pointWorld = transform.ToWorldPoint(point);

  double screenHeight = 5.0;
  double pixelsPerWorldUnit = pixels.y / screenHeight;

  double2 pixelOffset = pixelsPerWorldUnit * double2(pointWorld.x, pointWorld.y);

  return pixels / 2.0 + pixelOffset;
}

} // namespace math