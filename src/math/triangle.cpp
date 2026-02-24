#include "triangle.hpp"
#include "vector.hpp"

namespace math {
namespace triangle {

double SignedTriangleArea(const double2& a, const double2& b, const double2& c) {
  double2 ac = c - a;
  double2 abPerp = vector::Perpendicular(b - a);

  return vector::Dot(ac, abPerp) / 2;
}

bool InTriangle(const double2& a, const double2& b, const double2& c, const double2& p, double3& weights) {
  double ab = SignedTriangleArea(a, b, p);
  double bc = SignedTriangleArea(b, c, p);
  double ca = SignedTriangleArea(c, a, p);
  bool inTriangle = ab >= 0 && bc >= 0 && ca >= 0;

  //barycentric coordinates
  double totalArea = ab + bc + ca;
  double invAreaSum = 1.0 / totalArea;

  double weightA = bc * invAreaSum;
  double weightB = ca * invAreaSum;
  double weightC = ab * invAreaSum;

  weights = {weightA, weightB, weightC};

  return inTriangle && totalArea > 0.0;
}

} // namespace triangle
} // namespace math