#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <algorithm>
#include <vector>

#include "render_target.hpp"
#include "texture.hpp"
#include "../math/double2.hpp"
#include "../math/double3.hpp"
#include "../math/triangle.hpp"

using namespace math;

namespace graphics {
namespace rasterizer {

void RasterizeTriangle(
  const double3& a,
  const double3& b,
  const double3& c,
  const double2& uvA,
  const double2& uvB,
  const double2& uvC,
  const Texture& texture,
  render::RenderTarget& image
);

} // namespace rasterizer
} // namespace graphics


#endif // RASTERIZER_H