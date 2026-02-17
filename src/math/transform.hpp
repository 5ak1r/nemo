#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <cmath>
#include <iostream>
#include "double2.hpp"
#include "double3.hpp"

namespace math {

struct hats {
  double3 ihat;
  double3 jhat;
  double3 khat;

  hats() : ihat(double3()), jhat(double3()), khat(double3()) {}
  hats(double3 i, double3 j, double3 k) : ihat(i), jhat(j), khat(k) {}
};

class Transform {
public:
  Transform() : yaw(0.0) {}
  Transform(double y) : yaw(y) {}

  double Yaw() const;
  void setYaw(double y);

  double3 ToWorldPoint(const double3& p) const;
  hats GetBasisVectors() const;

  static double3 TransformVector(hats h, double3 v);

private:
  double yaw;
};

double2 WorldToScreen(const double3& point, const Transform& transform, const double2& pixels);

} // namespace math


#endif // TRANSFORM_H