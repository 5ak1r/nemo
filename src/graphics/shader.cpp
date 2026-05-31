#include "shader.hpp"

namespace graphics {

math::double3 PixelShader(const Surface& surface, const Scene& scene) {
  /*Color result = {1, 1, 1};

 for (const DirectionalLight& light : scene.directionalLights)
    result += ApplyDirectionalLight(surface, light);

  for (const PointLight& light : scene.pointLights)
    result += ApplyPointLight(surface, light);

  return surface.albedo * result;*/

  return {
    surface.normal.x * 0.5 + 0.5,
    surface.normal.y * 0.5 + 0.5,
    surface.normal.z * 0.5 + 0.5
  };
}

math::double3 ApplyDirectionalLight(const Surface& surface, const DirectionalLight& light) {
  math::double3 one = {1.0, 1.0, 1.0};

  return (surface.normal + one) * 0.5;
}

math::double3 ApplyPointLight(const Surface& surface, const PointLight& light) {
  return {0.0, 0.0, 0.0};
}

} // namespace graphics