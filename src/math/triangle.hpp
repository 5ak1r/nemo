#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "double2.hpp"
#include "vector.hpp"

namespace math {
namespace triangle {

// check if a point is on the right side (inside the triangle) of a vector a -> b
// dot product gives forwards/backwards, so we rotate one of the points 90 degrees clockwise to obtain left/right
inline bool RightSide(const double2& a, const double2& b, const double2& p) {
  double2 ap = p - a;
  double2 abPerp = vector::Perpendicular(b - a);

  return vector::Dot(ap, abPerp) >= 0;
}

// if a point is on the right side of a -> b, b -> c and c -> a then it is within all three of them (in the triangle)
inline bool InTriangle(const double2& a, const double2& b, const double2& c, const double2& p) {
  bool ab = RightSide(a, b, p);
  bool bc = RightSide(b, c, p);
  bool ca = RightSide(c, a, p);

  return ab == bc && bc == ca;
}

}
}

#endif