#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "double2.hpp"
#include "vector.hpp"

namespace math {
namespace triangle {

// if a point is on the right side of a -> b, b -> c and c -> a then it is within all three of them (in the triangle)
bool InTriangle(const double2& a, const double2& b, const double2& c, const double2& p, double3& weights);

// area of triangle abc, pos if clockwise, neg is anticlockwise
double SignedTriangleArea(const double2& a, const double2& b, const double2& c);

} // namespace triangle
} // namespace math

#endif // TRIANGLE_H