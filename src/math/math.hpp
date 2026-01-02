#ifndef MATH_H
#define MATH_H

#include "float2.hpp"

namespace math {
namespace vector {
inline float Dot(const float2& a, const float2& b) {
  return a.x * b.x + a.y * b.y;
}

inline float2 Perpendicular(const float2& a) {
  return { a.y, -a.x };
}
}

namespace triangle {
// check if a point is on the right side (inside the triangle) of a vector a -> b
// dot product gives forwards/backwards, so we rotate one of the points 90 degrees clockwise to obtain left/right
inline bool RightSide(const float2& a, const float2& b, const float2& p) {
  float2 ap = p - a;
  float2 abPerp = vector::Perpendicular(b - a);

  return vector::Dot(ap, abPerp) >= 0;
}

// if a point is on the right side of a -> b, b -> c and c -> a then it is within all three of them (in the triangle)
inline bool InTriangle(const float2& a, const float2& b, const float2& c, const float2& p) {
  bool ab = RightSide(a, b, p);
  bool bc = RightSide(b, c, p);
  bool ca = RightSide(c, a, p);

  return ab == bc && bc == ca;
}

}
}

#endif