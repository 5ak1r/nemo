#include "input.hpp"
#include <GLFW/glfw3.h>

namespace io {
namespace input {

namespace {
  static math::double2 currentPos(0.0);
  static math::double2 prevPos(0.0);
  static math::double2 mouseDelta(0.0);

  static bool first = true;
}

void Update(const graphics::window::Window& window) {
  double x, y;
  glfwGetCursorPos(window.getWindow(), &x, &y);

  currentPos.x = x;
  currentPos.y = y;

  if (first) {
    prevPos = currentPos;
    first = false;
  }

  mouseDelta = currentPos - prevPos;
  prevPos = currentPos;
}

math::double2 GetMouseDelta() { return mouseDelta; }

void ProcessInput(const graphics::window::Window& window, graphics::scene::Scene& scene, float deltaTime) {
  GLFWwindow* windowPtr = window.getWindow();

  for (auto& component : scene.components) {
    component.second.addPitch(-deltaTime);
    component.second.addYaw(deltaTime);
  }

  if (glfwGetKey(windowPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(windowPtr, true);

  // camera controls
  float cameraSens = scene.camera.getSens();
  math::Transform& cameraTransform = scene.camera.getTransform();

  math::double2 mouseDelta = GetMouseDelta() / window.getWidth() * cameraSens;

  float cameraSpeed = scene.camera.getSpeed();

  if (glfwGetKey(windowPtr, GLFW_KEY_W) == GLFW_PRESS)
    cameraTransform.addPosition({0, 0, cameraSpeed * deltaTime});
  if (glfwGetKey(windowPtr, GLFW_KEY_S) == GLFW_PRESS)
    cameraTransform.addPosition({0, 0, -cameraSpeed * deltaTime});
  if (glfwGetKey(windowPtr, GLFW_KEY_A) == GLFW_PRESS)
    cameraTransform.addPosition({-cameraSpeed * deltaTime, 0, 0});
  if (glfwGetKey(windowPtr, GLFW_KEY_D) == GLFW_PRESS)
    cameraTransform.addPosition({cameraSpeed * deltaTime, 0, 0});
}

} // namespace input
} // namespace io