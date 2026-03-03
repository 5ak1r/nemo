#include "render.hpp"

namespace graphics {
namespace render {

void Render(RenderTarget& target, const model::Mesh& mesh, const math::Transform& transform, double fov) {
  int width = target.getWidth();
  int height = target.getHeight();

  for (int i = 0; i < mesh.triangles.size(); i += 3) {
 	  math::double3 a = VertexToScreen(mesh.vertices[mesh.triangles[i]].position, transform, width, height, fov);
 		math::double3 b = VertexToScreen(mesh.vertices[mesh.triangles[i + 1]].position, transform, width, height, fov);
 		math::double3 c = VertexToScreen(mesh.vertices[mesh.triangles[i + 2]].position, transform, width, height, fov);

 		int triIndex = i / 3;
 		double r = std::fmod(triIndex * 0.6180339887, 1.0); // 1 / φ
    double g = std::fmod(triIndex * 0.3819660113, 1.0); // 1 − 1/φ
    double d = std::fmod(triIndex * 0.7071067811, 1.0); // 1 / √2

    math::double3 color = {r, g, d};

		rasterizer::RasterizeTriangle(a, b, c, target, color);
 	}
}

} // namespace render
} // namespace graphics