#ifndef RENDER_H
#define RENDER_H

#include "rasterizer.hpp"
#include "render_target.hpp"
#include "../math/double2.hpp"
#include "../math/double3.hpp"
#include "../math/transform.hpp"
#include "../model/mesh.hpp"

namespace graphics {
namespace render {

void Render(RenderTarget& target, const model::Mesh& mesh, const math::Transform& transform, double fov);

} // namespace render
} // namespace graphics

#endif // RENDER_H