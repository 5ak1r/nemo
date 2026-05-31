#ifndef SHADER_H
#define SHADER_H

#include "lighting.hpp"
#include "scene.hpp"
#include "surface.hpp"

#include "../math/double3.hpp"

namespace graphics {

math::double3 PixelShader(const Surface& surface, const Scene& scene);

math::double3 ApplyDirectionalLight(const Surface& surface, const DirectionalLight& light);
math::double3 ApplyPointLight(const Surface& surface, const PointLight& light);

} // namespace graphics

#endif // SHADER_H