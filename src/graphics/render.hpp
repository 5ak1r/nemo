#ifndef RENDER_H
#define RENDER_H

#include "rasterizer.hpp"
#include "render_target.hpp"
#include "scene.hpp"
#include "window.hpp"
#include "../io/file.hpp"
#include "../math/constants.hpp"
#include "../math/double2.hpp"
#include "../math/double3.hpp"
#include "../math/transform.hpp"
#include "../model/mesh.hpp"

namespace graphics {
namespace render {

const std::string vertShader = "src/graphics/shaders/vert.glsl";
const std::string fragShader = "src/graphics/shaders/frag.glsl";

void RenderMesh(RenderTarget& target, const model::Mesh& mesh, const math::Transform& transform, double fov);
void RenderMainLoop(const window::Window& window, scene::Scene& scene);

void ProcessInput(const window::Window& window, scene::Scene& scene, float deltaTime);

void SetupScreen(int width, int height);
void DrawScreen(const RenderTarget& target);

} // namespace render
} // namespace graphics

#endif // RENDER_H