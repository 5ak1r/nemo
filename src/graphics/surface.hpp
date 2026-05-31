#ifndef SURFACE_H
#define SURFACE_H

#include "../math/double2.hpp"
#include "../math/double3.hpp"

namespace graphics {

struct Surface {
  math::double3 normal;
  math::double3 worldPos;
  math::double2 texCoord;

  math::double3 albedo;
};

} // namespace graphics

#endif // SURFACE_H