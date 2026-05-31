#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <algorithm>
#include <vector>

#include "render_target.hpp"
#include "material.hpp"
#include "../math/double2.hpp"
#include "../math/double3.hpp"
#include "../math/triangle.hpp"
#include "../model/mesh.hpp"

using namespace math;

namespace graphics {
namespace rasterizer {

void RasterizeTriangle(
  const double3& a,
  const double3& b,
  const double3& c,
  const model::Vertex& vA,
  const model::Vertex& vB,
  const model::Vertex& vC,
  const Material& material,
  render::RenderTarget& image
);

} // namespace rasterizer
} // namespace graphics


#endif // RASTERIZER_H