#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <string>

namespace graphics {
namespace window {

void InitGLFW();
void InitGLAD();

class Window {
public:
  Window(int width, int height, const std::string& name);
  ~Window();

  int getWidth() const;
  int getHeight() const;

  GLFWwindow* getWindow() const;

  void MakeCurrent() const;

private:
  const int mWidth;
  const int mHeight;

  GLFWwindow* mWindow;
};

} // namespace window
} // namespace graphics

#endif // WINDOW_H