#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <algorithm>
#include <vector>

#include "render_target.hpp"
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
  render::RenderTarget& image,
  const render::Color& color);

} // namespace rasterizer
} // namespace graphics


#endif // RASTERIZER_H