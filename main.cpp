#include "src/draw/draw.hpp"
#include "src/math/hessenberg.hpp"
#include "src/math/lu_decomp.hpp"
#include "src/math/matrix.hpp"
#include "src/math/matrix_helpers.hpp"
#include "src/math/vector.hpp"
#include "src/model/mesh.hpp"
#include "src/model/obj.hpp"

using namespace math;
using namespace math::matrix;

int main() {
  const int width = 1024;
	const int height = 1024;

	model::Mesh mesh = model::OBJ::Read("resources/cube.obj");

	std::vector<math::double3> imgRow(width, math::double3(0,0,0));
	std::vector<std::vector<math::double3>> image(height, imgRow);

	for (int i = 0; i < mesh.vertices.size(); i += 3) {
		//double2 a = mesh.vertices[mesh.triangles[i]];
		//double2 b = mesh.vertices[mesh.triangles[i + 1]];
		//double2 c = mesh.vertices[mesh.triangles[i + 2]];

		for (double y = 0; y < height; y++) {
		for (double x = 0; x < width; x++) {
				//if (triangle::inTriangle(a, b, c, {x, y}))
					image[x][y] = math::double3(0.0f, 0.0f, 1.0f);
			}
		}
	}

  draw::BMP::Write(image, "test");

  std::vector<double> data1 = {
    7, 12, -3,  8,  0, 15,
    -6,  4,  9, -1, 11,  2,
    14, -8,  5,  3, -2, 10,
    1, 13, -5,  6,  9, -7,
    8,  0, 16, -4,  2, 11,
    -9,  5,  3, 12, -1,  4
  };
  Matrix mat1 = Matrix(6.0, 6.0, data1);
  Matrix mat2 = RemoveMatrixRow(RemoveMatrixCol(mat1, 0), 0);
  Matrix mat3 = RemoveMatrixRow(RemoveMatrixCol(mat2, 0), 0);
  Matrix mat4 = RemoveMatrixRow(RemoveMatrixCol(mat3, 0), 0);

  Matrix mat5 = Matrix(4, 4, {544, 2, 3, 4, 3, 222, 223, 444, 23, 2, 3, 4, 123123, 123, 4, 7});

  std::cout << mat2 << std::endl;
}