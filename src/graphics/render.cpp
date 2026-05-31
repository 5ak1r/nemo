#include "render.hpp"

namespace graphics {
namespace render {

GLuint screenVAO, screenVBO, screenShader, screenTexture;

void Mesh(RenderTarget& target, const model::Mesh& mesh, const math::Transform& transform, const Camera& camera) {
  int width = target.getWidth();
  int height = target.getHeight();

  for (int i = 0; i < mesh.triangles.size(); i += 3) {
    const model::Vertex& va = mesh.vertices[mesh.triangles[i]];
    const model::Vertex& vb = mesh.vertices[mesh.triangles[i + 1]];
    const model::Vertex& vc = mesh.vertices[mesh.triangles[i + 2]];

 	  math::double3 a = VertexToScreen(va.position, transform, camera, width, height);
 		math::double3 b = VertexToScreen(vb.position, transform, camera, width, height);
  	math::double3 c = VertexToScreen(vc.position, transform, camera, width, height);

    if (a.z <= 0 || b.z <= 0 || c.z <= 0) continue;

		rasterizer::RasterizeTriangle(a, b, c, va, vb, vc, mesh.material, target);
 	}
}

void MainLoop(const window::Window& window, scene::Scene& scene) {
  SetupScreen(window.getWidth(), window.getHeight());
  GLFWwindow* windowPtr = window.getWindow();
  RenderTarget target(window.getWidth(), window.getHeight());

  //glfwSetInputMode(windowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetInputMode(windowPtr, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

  float lastTime = glfwGetTime();
  int frameCount = 0;

  float lastFrame = 0.0f;
  while (!glfwWindowShouldClose(windowPtr)) {
    float currentTime = glfwGetTime();
    frameCount++;

    if (currentTime - lastTime >= 1.0f) {
      //std::cout << "FPS: " << frameCount << std::endl;
      frameCount = 0;
      lastTime = currentTime;
    }

    float deltaTime = currentTime - lastFrame;
    lastFrame = currentTime;

    glfwPollEvents();
    io::input::Update(window);
    io::input::ProcessInput(window, scene, deltaTime);

    target.clear();
    for (auto& object : scene.components) {
      Mesh(target, object.first, object.second, scene.camera);
    }

    glClear(GL_COLOR_BUFFER_BIT);
    DrawScreen(target);
    glfwSwapBuffers(windowPtr);
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