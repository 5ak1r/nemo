#include "src/draw/draw.hpp"
#include "src/draw/rasterizer.hpp"
#include "src/math/double3.hpp"
#include "src/math/hessenberg.hpp"
#include "src/math/lu_decomp.hpp"
#include "src/math/matrix.hpp"
#include "src/math/matrix_helpers.hpp"
#include "src/math/qr_algorithm.hpp"
#include "src/math/vector.hpp"
#include "src/model/mesh.hpp"
#include "src/model/obj.hpp"
#include <type_traits>

using namespace math;
using namespace math::matrix;

int main() {
  const int width = 2560;
	const int height = 1600;

	model::Mesh mesh = model::OBJ::Read("resources/cube.obj");

	std::vector<std::vector<double3>> image(height, std::vector<double3>(width));

	double2 pixels = {width, height};

	for (int i = 0; i < mesh.triangles.size(); i += 3) {
	  double2 a = WorldToScreen(mesh.vertices[mesh.triangles[i]].position, pixels);
		double2 b = WorldToScreen(mesh.vertices[mesh.triangles[i + 1]].position, pixels);
		double2 c = WorldToScreen(mesh.vertices[mesh.triangles[i + 2]].position, pixels);

		draw::rasterizer::RasterizeTriangle(a, b, c, image, width, height);
	}

  draw::BMP::Write(image, "test");
}