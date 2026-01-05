#include "src/draw/draw.hpp"
#include "src/math/hessenberg.hpp"
#include "src/math/lu_decomp.hpp"
#include "src/math/matrix.hpp"
#include "src/math/vector.hpp"
#include "src/model/mesh.hpp"
#include "src/model/obj.hpp"

int main() {
  const int width = 1024;
	const int height = 1024;

	model::Mesh mesh = model::OBJ::Read("resources/cube.obj");

	std::vector<math::double3> imgRow(width, math::double3(0,0,0));
	std::vector<std::vector<math::double3>> image(height, imgRow);

	for (int i = 0; i < mesh.vertices.size(); i += 3) {
		//math::double2 a = mesh.vertices[mesh.triangles[i]];
		//math::double2 b = mesh.vertices[mesh.triangles[i + 1]];
		//math::double2 c = mesh.vertices[mesh.triangles[i + 2]];

		for (double y = 0; y < height; y++) {
		for (double x = 0; x < width; x++) {
				//if (math::triangle::inTriangle(a, b, c, {x, y}))
					image[x][y] = math::double3(0.0f, 0.0f, 1.0f);
			}
		}
	}

  draw::BMP::Write(image, "test");

  std::vector<int> data1 = {
    7, 12, -3,  8,  0, 15,
    -6,  4,  9, -1, 11,  2,
    14, -8,  5,  3, -2, 10,
    1, 13, -5,  6,  9, -7,
    8,  0, 16, -4,  2, 11,
    -9,  5,  3, 12, -1,  4
  };
  math::Matrix<int> mat1 = math::Matrix<int>(6, 6, data1 );

  std::cout << mat1.cofactors() << "\n\n";
  std::cout << mat1.adjugate() << "\n\n";

  std::cout << mat1.inverse() << "\n\n";
  std::cout << mat1.inverse() * mat1 << "\n\n";

  std::cout << mat1 * mat1 << "\n\n";

  math::Matrix<int> mat2 = math::Matrix<int>(2, 3, { 1, 1, 1, 2, 2, 2 });
  math::Matrix<int> mat3 = math::Matrix<int>(2, 2, { 1, 1, 2, 2 });

  std::cout << mat2 * mat2.transpose() << std::endl;
  std::cout << mat2.transpose() << std::endl;
  std::cout << mat3 * mat2 << "\n\n";

  auto vec1 = mat3.row(0);
  auto vec2 = mat3.row(1);

  std::cout << math::vector::Add(vec1, vec2) << std::endl;
  std::cout << math::vector::Subtract(vec1, vec2) << std::endl;
  std::cout << math::vector::Multiply(vec1, vec2) << std::endl;
  std::cout << math::vector::Divide(vec1, vec2) << std::endl;

  std::cout << math::vector::Multiply(vec1, 3.0) << std::endl;
  std::cout << math::hessenberg::Omega(vec1) << std::endl;
}