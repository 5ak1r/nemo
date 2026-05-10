#include "src/graphics/render.hpp"
#include "src/graphics/scene.hpp"
#include "src/graphics/window.hpp"
#include "src/math/constants.hpp"
#include "src/model/obj.hpp"

int main() {
  const int width = 1920;
	const int height = 1080;

	const model::Mesh mesh = model::obj::Read("resources/suzanne.obj");
	const model::Mesh mesh2 = model::obj::Read("resources/plane.obj");
	const model::Mesh mesh3 = model::obj::Read("resources/cow.obj");

	graphics::window::InitGLFW();

	graphics::window::Window window(width, height, "test");
	window.MakeCurrent();

	graphics::window::InitGLAD();
	glViewport(0, 0, window.getWidth(), window.getHeight());

	math::Transform transform({math::constants::PI, 0}, {0.0, 0.0, 10.0});
	math::Transform transform2({math::constants::PI, 0}, {1.0, 0.2, 3.0});
	math::Transform transform3({math::constants::PI, 0}, {-2.0, 0.2, 2.0});

	graphics::scene::Scene scene;
	scene.camera = graphics::Camera(math::constants::PI / 3);
	scene.components.push_back({mesh, transform});
	scene.components.push_back({mesh2, transform2});
	scene.components.push_back({mesh3, transform3});

	graphics::render::MainLoop(window, scene);
}