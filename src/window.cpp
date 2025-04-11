#include "../include/GLUtils.h"
#include "../include/data.h"
#include "../include/errorHandler.h"
#include "../include/file_io.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

bool createWindow(int width, int height) {
  glfwInit();
  if (!glfwInit()) {
    std::cout << "GLFW initialization failed" << std::endl;
    return false;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
      glfwCreateWindow(width, height, "THE LAST CRUSADE", NULL, NULL);
  if (window == nullptr) {
    std::cout << "window creation failed" << std::endl;
    return false;
  }

  glfwMakeContextCurrent(window);
  glewInit();
  checkErrors();
  if (glewInit() != 0) {
    std::cout << "GLEW initialization failed" << std::endl;
    return false;
  }
  std::string vertexShader = readFromFile("../shaders/shader.vert");
  std::string fragmentShader = readFromFile("../shaders/shader.frag");

  const char *vertex = vertexShader.c_str();
  const char *fragment = fragmentShader.c_str();

  std::vector<float> vertices = getData();

  unsigned int shaderProgram = GLUtils::generateShaders(vertex, fragment);
  GLUtils::attributeHandler(vertices.data(), vertices.size());

  unsigned int texture;
  GLUtils::loadTextures(texture);
  checkErrors();

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.0f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    checkErrors();

    glBindTexture(GL_TEXTURE_2D, texture);
    checkErrors();

    glUseProgram(shaderProgram);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return true;
}
