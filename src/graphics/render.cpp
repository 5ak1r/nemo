#include "render.hpp"

namespace graphics {
namespace render {

GLuint screenVAO, screenVBO, screenShader, screenTexture;

void RenderMesh(RenderTarget& target, const model::Mesh& mesh, const math::Transform& transform, double fov) {
  int width = target.getWidth();
  int height = target.getHeight();

  for (int i = 0; i < mesh.triangles.size(); i += 3) {
 	  math::double3 a = VertexToScreen(mesh.vertices[mesh.triangles[i]].position, transform, width, height, fov);
 		math::double3 b = VertexToScreen(mesh.vertices[mesh.triangles[i + 1]].position, transform, width, height, fov);
 		math::double3 c = VertexToScreen(mesh.vertices[mesh.triangles[i + 2]].position, transform, width, height, fov);

 		int triIndex = i / 3;
 		double r = std::fmod(triIndex * 0.6180339887, 1.0); // 1 / φ
    double g = std::fmod(triIndex * 0.3819660113, 1.0); // 1 − 1/φ
    double d = std::fmod(triIndex * 0.7071067811, 1.0); // 1 / √2

    Color color = {(uint8_t)(r * 255), (uint8_t)(g * 255), (uint8_t)(d * 255)}; // temporary until we add shaders/textures

		rasterizer::RasterizeTriangle(a, b, c, target, color);
 	}
}

void RenderMainLoop(const window::Window& window, scene::Scene& scene) {
  SetupScreen(window.getWidth(), window.getHeight());
  GLFWwindow* windowPtr = window.getWindow();
  RenderTarget target(window.getWidth(), window.getHeight());

  float lastFrame = 0.0f;
  while (!glfwWindowShouldClose(windowPtr)) {
    float currentFrame = glfwGetTime();
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glfwPollEvents();
    ProcessInput(window, scene, deltaTime);

    target.clear();
    for (auto& object : scene.components) {
      RenderMesh(target, object.first, object.second, scene.fov);
    }

    glClear(GL_COLOR_BUFFER_BIT);
    DrawScreen(target);
    glfwSwapBuffers(windowPtr);
  }
}

void ProcessInput(const window::Window& window, scene::Scene& scene, float deltaTime) {
  GLFWwindow* windowPtr = window.getWindow();

  if (glfwGetKey(windowPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(windowPtr, true);
  else if (glfwGetKey(windowPtr, GLFW_KEY_A) == GLFW_PRESS) {
    float rotationSpeed = math::constants::PI / 18;

    for (auto& component : scene.components) {
      component.second.addYaw(rotationSpeed * deltaTime);
    }
  }
}

void SetupScreen(int width, int height) {
  float vertices[] = {
    // pos        // uv
    -1.0f,  1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, 1.0f, 0.0f,

    -1.0f,  1.0f, 0.0f, 1.0f,
     1.0f, -1.0f, 1.0f, 0.0f,
     1.0f,  1.0f, 1.0f, 1.0f
  };

  glGenVertexArrays(1, &screenVAO);
  glGenBuffers(1, &screenVBO);
  glBindVertexArray(screenVAO);
  glBindBuffer(GL_ARRAY_BUFFER, screenVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glGenTextures(1, &screenTexture);
  glBindTexture(GL_TEXTURE_2D, screenTexture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  std::string vertStr = io::file::ReadToString(vertShader);
  const char* vertChar = vertStr.c_str();

  std::string fragStr = io::file::ReadToString(fragShader);
  const char* fragChar = fragStr.c_str();

  GLuint vert = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert, 1, &vertChar, nullptr);
  glCompileShader(vert);

  GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag, 1, &fragChar, nullptr);
  glCompileShader(frag);

  screenShader = glCreateProgram();
  glAttachShader(screenShader, vert);
  glAttachShader(screenShader, frag);
  glLinkProgram(screenShader);

  glDeleteShader(vert);
  glDeleteShader(frag);
}

void DrawScreen(const RenderTarget& target) {
  glBindTexture(GL_TEXTURE_2D, screenTexture);
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, target.getWidth(), target.getHeight(), GL_RGB, GL_UNSIGNED_BYTE, target.getColorBuffer().data());

  glUseProgram(screenShader);
  glBindVertexArray(screenVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
}

} // namespace render
} // namespace graphics