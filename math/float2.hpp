#ifndef FLOAT2_H
#define FLOAT2_H

namespace math {
  struct float2 {
    float x, y;

    float2(float a, float b): x(a), y(b) {}
  };

  inline float2 operator-(const float2& a, const float2& b) {
    return float2(a.x - b.x, a.y - b.y);
  }

  inline float2 operator-(const float2& a) {
    return float2(-a.x, -a.y);
  }

  inline float2 operator+(const float2& a, const float2& b) {
    return float2(a.x + b.x, a.y + b.y);
  }

  inline float2 operator*(const float2& a, const float2& b) {
    return float2(a.x * b.x, a.y * b.y);
  }

  inline float2 operator/(const float2& a, const float2& b) {
    return float2(a.x / b.x, a.y / b.y);
  }
}

#endif