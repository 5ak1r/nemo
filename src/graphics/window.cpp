#include "window.hpp"

namespace graphics {
namespace window {

void InitGLFW() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void InitGLAD() {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    throw std::invalid_argument("failed to initialise GLAD");
}

Window::Window(int width, int height, const std::string& name) : mWidth(width), mHeight(height) {
  mWindow = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

  if (!mWindow)
    throw std::runtime_error("failed to create GLFW window");
}

Window::~Window() {
  if (mWindow)
    glfwDestroyWindow(mWindow);
}

int Window::getHeight() const {
  return mHeight;
}

int Window::getWidth() const {
  return mWidth;
}

GLFWwindow* Window::getWindow() const {
  return mWindow;
}

void Window::MakeCurrent() const {
  if (!mWindow)
    throw std::runtime_error("cannot make null window current");

  glfwMakeContextCurrent(mWindow);
}

} // namespace window
} // namespace graphics