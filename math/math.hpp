#ifndef MATH_H
#define MATH_H

#include "float2.hpp"

namespace math {
  inline float dot(const float2& a, const float2& b) {
    return a.x * b.x + a.y * b.y;
  }

  inline float2 perpendicular(const float2& a) {
    return {a.y, -a.x};
  }

  // check if a point is on the right side (inside the triangle) of a vector a -> b
  // dot product gives forwards/backwards, so we rotate one of the points 90 degrees clockwise to obtain left/right
  inline bool rightSide(const float2& a, const float2& b, const float2& p) {
    float2 ap = p - a;
    float2 abPerp = perpendicular(b - a);

    return dot(ap, abPerp) >= 0;
  }

  // if a point is on the right side of a -> b, b -> c and c -> a then it is within all three of them (in the triangle)
  inline bool inTriangle(const float2& a, const float2& b, const float2& c, const float2& p) {
    bool ab = rightSide(a, b, p);
    bool bc = rightSide(b, c, p);
    bool ca = rightSide(c, a, p);

    return ab == bc && bc == ca;
  }
}

#endif