#ifndef FLOAT3_H
#define FLOAT3_H

namespace math {

union float3 {
  struct { float x, y, z; };
  struct { float r, g, b; };

  float3(float a, float b, float c) : x(a), y(b), z(c) {}

};

inline float3 operator-(const float3& a, const float3& b) {
  return float3(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline float3 operator-(const float3& a) {
  return float3(-a.x, -a.y, -a.z);
}

inline float3 operator+(const float3& a, const float3& b) {
  return float3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline float3 operator*(const float3& a, const float3& b) {
  return float3(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline float3 operator/(const float3& a, const float3& b) {
  return float3(a.x / b.x, a.y / b.y, a.z / b.z);
}

}

#endif