#include "src/graphics/rasterizer.hpp"
#include "src/graphics/render_target.hpp"
#include "src/io/bmp.hpp"
#include "src/math/constants.hpp"
#include "src/math/double3.hpp"
#include "src/math/hessenberg.hpp"
#include "src/math/lu_decomp.hpp"
#include "src/math/matrix.hpp"
#include "src/math/matrix_helpers.hpp"
#include "src/math/qr_algorithm.hpp"
#include "src/math/transform.hpp"
#include "src/math/vector.hpp"
#include "src/model/mesh.hpp"
#include "src/model/obj.hpp"
#include <string>

using namespace math;
using namespace math::matrix;

int main() {
  const int width = 2560;
	const int height = 1600;

	model::Mesh mesh = model::OBJ::Read("resources/suzanne.obj");

	graphics::render::RenderTarget image(width, height);

	double2 pixels = {width, height};

	for (int j = 0; j < 2; j++) {
	  Transform transform(PI, 0, {0.0, 0.0, 6.0});
    double fov = PI / 3;

  	for (int i = 0; i < mesh.triangles.size(); i += 3) {
  	  double3 a = VertexToScreen(mesh.vertices[mesh.triangles[i]].position, transform, pixels, fov);
  		double3 b = VertexToScreen(mesh.vertices[mesh.triangles[i + 1]].position, transform, pixels, fov);
  		double3 c = VertexToScreen(mesh.vertices[mesh.triangles[i + 2]].position, transform, pixels, fov);

  		int triIndex = i / 3;
  		double r = std::fmod(triIndex * 0.6180339887, 1.0); // 1 / φ
      double g = std::fmod(triIndex * 0.3819660113, 1.0); // 1 − 1/φ
      double d = std::fmod(triIndex * 0.7071067811, 1.0); // 1 / √2

      double3 color = {r, g, d};

  		graphics::rasterizer::RasterizeTriangle(a, b, c, image, width, height, color);
  	}

    io::bmp::Write(image, "test_" + std::to_string(j));

    // reset the image
    image.resetBuffers();
	}
}