#ifndef FLOAT_H
#define FLOAT_H

namespace math {
  union float3 {
    struct { float x, y, z; };
    struct { float r, g, b; };
  };
}

#endif