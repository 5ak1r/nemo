#include "input.hpp"

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

  mouseDelta = prevPos - currentPos;
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
  cameraTransform.setRotation(
    std::clamp(cameraTransform.getPitch() - mouseDelta.y, math::conversions::ToRadians(-85), math::conversions::ToRadians(85)),
    cameraTransform.getYaw() - mouseDelta.x);

  float cameraSpeed = scene.camera.getSpeed();
  math::double3 moveDelta(0.0);

  math::Matrix cameraMatrix = cameraTransform.GetBasisMatrix();
  math::double3 cameraRight = cameraMatrix.getCol(0);
  math::double3 cameraUp = cameraMatrix.getCol(1);
  math::double3 cameraFwd = cameraMatrix.getCol(2);

  if (glfwGetKey(windowPtr, GLFW_KEY_W) == GLFW_PRESS) moveDelta = moveDelta + cameraFwd;
  if (glfwGetKey(windowPtr, GLFW_KEY_S) == GLFW_PRESS) moveDelta = moveDelta - cameraFwd;
  if (glfwGetKey(windowPtr, GLFW_KEY_A) == GLFW_PRESS) moveDelta = moveDelta - cameraRight;
  if (glfwGetKey(windowPtr, GLFW_KEY_D) == GLFW_PRESS) moveDelta = moveDelta + cameraRight;

  cameraTransform.addPosition(moveDelta.getNormalized() * cameraSpeed * deltaTime);
  cameraTransform.setYPosition(1.0);
}

} // namespace input
} // namespace io