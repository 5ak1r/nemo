#ifndef VECTOR_H
#define VECTOR_H

#include "float2.hpp"
#include "float3.hpp"

namespace math {
namespace vector {
inline float Dot(const float2& a, const float2& b) {
  return a.x * b.x + a.y * b.y;
}

inline float Dot(const float3& a, const float3& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float2 Perpendicular(const float2& a) {
  return { a.y, -a.x };
}

}
}

#endif