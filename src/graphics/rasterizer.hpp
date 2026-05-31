#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <algorithm>
#include <vector>

#include "lighting.hpp"
#include "material.hpp"
#include "render_target.hpp"
#include "scene.hpp"
#include "surface.hpp"

#include "../math/double2.hpp"
#include "../math/double3.hpp"
#include "../math/triangle.hpp"

#include "../model/mesh.hpp"

using namespace math;

namespace graphics {
namespace rasterizer {

template<typename T>
T InterpolatePerspective(
  const T& a,
  const T& b,
  const T& c,
  const double3& depths,
  const double3& weights
);

void RasterizeTriangle(
  const double3& a,
  const double3& b,
  const double3& c,
  const model::Vertex& vA,
  const model::Vertex& vB,
  const model::Vertex& vC,
  const Material& material,
  const Scene& scene,
  render::RenderTarget& image
);

} // namespace rasterizer
} // namespace graphics


#endif // RASTERIZER_H