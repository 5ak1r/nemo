#include "src/draw/draw.hpp"
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
  const int width = 64;
	const int height = 64;

	model::Mesh mesh = model::OBJ::Read("resources/cube.obj");

	//std::vector<math::double3> imgRow(width, math::double3(0,0,0));
	//std::vector<std::vector<math::double3>> image(height, imgRow);
	std::vector<std::vector<double3>> image(width);

	//for (int i = 0; i < mesh.vertices.size(); i += 3) {
		//double2 a = mesh.vertices[mesh.triangles[i]];
		//double2 b = mesh.vertices[mesh.triangles[i + 1]];
		//double2 c = mesh.vertices[mesh.triangles[i + 2]];

		double2 a = double2(2, 34);
		double2 b = double2(22, 3);
		double2 c = double2(63, 0);

		for (double y = 0; y < height; y++) {
		  for (double x = 0; x < width; x++) {
				if (triangle::InTriangle(a, b, c, { x, y }))
					image[x].push_back(double3(0.0, 0.0, 1.0));
				else image[x].push_back(double3(0.0, 0.0, 0.0));
			}
		}
	//}

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

  Matrix mat5 = Matrix(4, 4, { 544, 2, 3, 4, 3, 222, 223, 444, 23, 2, 3, 4, 123123, 123, 4, 7 });

  Matrix hess = hessenberg::UpperHessenbergMatrix(mat1);

  Matrix mat6 = Matrix(5, 5, { 3, -7, 12, 4, 9, -5, 8, 1, -6, 10, 14, 2, -9, 7, -3, 6, 11, -4, 0, 5, -8,  9, 13, -2, 1 });

  std::cout << qr::QRDecomposition(mat1) << std::endl;
}