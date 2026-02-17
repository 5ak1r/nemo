#include "src/draw/draw.hpp"
#include "src/draw/rasterizer.hpp"
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

using namespace math;
using namespace math::matrix;

int main() {
  const int width = 2560;
	const int height = 1600;

	model::Mesh mesh = model::OBJ::Read("resources/cube.obj");

	std::vector<std::vector<double3>> image(height, std::vector<double3>(width, {0.0, 0.0, 0.0}));

	double2 pixels = {width, height};

	Transform transform(0);

	for (int i = 0; i < mesh.triangles.size(); i += 3) {
	  double2 a = WorldToScreen(mesh.vertices[mesh.triangles[i]].position, transform, pixels);
		double2 b = WorldToScreen(mesh.vertices[mesh.triangles[i + 1]].position, transform, pixels);
		double2 c = WorldToScreen(mesh.vertices[mesh.triangles[i + 2]].position, transform, pixels);

		double3 color = {1.0,1.0,0.0};
		draw::rasterizer::RasterizeTriangle(a, b, c, image, width, height, color);
	}

  draw::BMP::Write(image, "test");
}