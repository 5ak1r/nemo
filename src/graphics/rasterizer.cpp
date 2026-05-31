#include "rasterizer.hpp"
#include "lighting.hpp"
#include "shader.hpp"

namespace graphics {
namespace rasterizer {

template<typename T>
T InterpolatePerspective(
  const T& a,
  const T& b,
  const T& c,
  const double3& depths,
  const double3& weights
) {
  static_assert(std::is_same_v<T, double2> || std::is_same_v<T, double3>, "must be of type double2 or double3");

  T result;
  result += a / depths.x * weights.x;
  result += b / depths.y * weights.y;
  result += c / depths.z * weights.z;
  result *= depths;

  return result;
}

void RasterizeTriangle(
  const double3& a,
  const double3& b,
  const double3& c,
  const model::Vertex& va,
  const model::Vertex& vb,
  const model::Vertex& vc,
  const Material& material,
  const Scene& scene,
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
        double depth = 1.0 / Dot(1.0 / depths, weights);

        if (depth > image.getDepth(x, y)) continue;

        double3 normal;
        if (va.normal.getLength() < 1e-6 || vb.normal.getLength() < 1e-6 || vc.normal.getLength() < 1e-6) {
          normal = Cross(vb.position - va.position, vc.position - va.position);
        } else {
          normal = InterpolatePerspective(
            va.normal,
            vb.normal,
            vc.normal,
            depths,
            weights
          );
        }

        double3 worldPos = InterpolatePerspective(
          va.position,
          vb.position,
          vc.position,
          depths,
          weights
        );

        double2 texCoord = InterpolatePerspective(
          va.texture,
          vb.texture,
          vc.texture,
          depths,
          weights
        );

        Surface surface;
        surface.normal = normal.getNormalized();
        surface.worldPos = worldPos;
        surface.texCoord = texCoord;
        surface.albedo = material.texture.Sample(texCoord) * material.albedo;

        math::double3 tempPixelColor = PixelShader(surface, scene);
        Color pixelColor = {
          static_cast<uint8_t>(tempPixelColor.x * 255),
          static_cast<uint8_t>(tempPixelColor.y * 255),
          static_cast<uint8_t>(tempPixelColor.z * 255)
        }; // convert to uint8_t at the end

        image.setColor(x, y, pixelColor);
        image.setDepth(x, y, depth);
      }
    }
  }
}

} // namespace rasterizer
} // namespace graphics