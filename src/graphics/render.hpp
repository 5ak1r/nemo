#ifndef RENDER_H
#define RENDER_H

#include "rasterizer.hpp"
#include "render_target.hpp"
#include "scene.hpp"
#include "window.hpp"

#include "../io/file.hpp"
#include "../io/input.hpp"

#include "../math/constants_conversions.hpp"
#include "../math/double2.hpp"
#include "../math/double3.hpp"
#include "../math/transform.hpp"

#include "../model/mesh.hpp"

namespace graphics {
namespace render {

const std::string vertShader = "src/graphics/shaders/vert.glsl";
const std::string fragShader = "src/graphics/shaders/frag.glsl";

void Mesh(RenderTarget& target, const model::Mesh& mesh, const Camera& camera, const math::Transform& transform, double fov);
void MainLoop(const window::Window& window, scene::Scene& scene);

void SetupScreen(int width, int height);
void DrawScreen(const RenderTarget& target);

} // namespace render
} // namespace graphics

#endif // RENDER_H