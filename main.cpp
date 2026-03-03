#include "src/graphics/rasterizer.hpp"
#include "src/graphics/render.hpp"
#include "src/graphics/window.hpp"
#include "src/io/bmp.hpp"
#include "src/math/constants.hpp"
#include "src/math/matrix.hpp"
#include "src/math/matrix_helpers.hpp"
#include "src/model/obj.hpp"

using namespace math;
using namespace math::matrix;

int main() {
  const int width = 2560;
	const int height = 1600;

	const model::Mesh mesh = model::obj::Read("resources/suzanne.obj");
	const model::Mesh mesh2 = model::obj::Read("resources/plane.obj");

	graphics::window::InitGLFW();

	graphics::window::Window window(800, 600, "test");
	window.MakeCurrent();

	graphics::window::InitGLAD();
	glViewport(0, 0, window.getWidth(), window.getHeight());

	graphics::render::RenderTarget image(width, height);

	Transform transform({PI, 0}, {0.0, 0.0, 10.0});
	Transform transform2({PI, 0}, {1.0, 0.2, 3.0});

	const double fov = PI / 3;

	for (int j = 0; j < 10; j++) {
    graphics::render::Render(image, mesh, transform, fov);
    graphics::render::Render(image, mesh2, transform2, fov);

    transform.addYaw(PI / 18);
    transform2.addYaw(PI / 18);

    io::bmp::Write(image, "test_" + std::to_string(j));

    // reset the image
    image.resetBuffers();
	}
}