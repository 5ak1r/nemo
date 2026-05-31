#include "rasterizer.hpp"
#include "lighting.hpp"

namespace graphics {
namespace rasterizer {

void RasterizeTriangle(
  const double3& a,
  const double3& b,
  const double3& c,
  const model::Vertex& va,
  const model::Vertex& vb,
  const model::Vertex& vc,
  const Material& material,
  const std::vector<DirectionalLight>& directionalLights,
  const std::vector<PointLight>& pointLights,
  render::RenderTarget& image
) {
  int minX = std::floor(std::min({a.x, b.x, c.x}));
  int minY = std::floor(std::min({a.y, b.y, c.y}));
  int maxX = std::ceil(std::max({a.x, b.x, c.x}));
  int maxY = std::ceil(std::max({a.y, b.y, c.y}));

  minX = std::max(0, minX);
  minY = std::max(0, minY);
  maxX = std::min(image.getWidth() - 1, maxX);
  maxY = std::min(image.getHeight() - 1, maxY);

  for (int y = minY; y <= maxY; y++) {
    for (int x = minX; x <= maxX; x++) {
      double3 weights;

      if (triangle::InTriangle(double2(a), double2(b), double2(c), {x + 0.5, y + 0.5}, weights)) {
        double3 depths = {a.z, b.z, c.z};
        double depth = 1.0 / vector::Dot(1.0 / depths, weights);

        if (depth > image.getDepth(x, y)) continue;

        double2 texCoord;
        texCoord += va.texture / depths.x * weights.x;
        texCoord += vb.texture / depths.y * weights.y;
        texCoord += vc.texture / depths.z * weights.z;
        texCoord *= depths;

        Color texColor = material.texture.Sample(texCoord);

        double3 normal;
        normal += va.normal / depths.x * weights.x;
        normal += vb.normal / depths.y * weights.y;
        normal += vc.normal / depths.z * weights.z;
        normal *= depths;

        // apply lighting method, using all scene lights, inputs: scene, texColor, normal, output: one Color

        image.setColor(x, y, texColor); // setColor to this new Color
        image.setDepth(x, y, depth);
      }
    }
  }
}

} // namespace rasterizer
} // namespace graphics