#include "../include/file_io.h"
#include "../include/shaders.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

void createWindow() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "START", NULL, NULL);
  glfwMakeContextCurrent(window);
  glewInit();
  std::string vertexShader = readFromFile("../shaders/shader.vert");
  std::string fragmentShader = readFromFile("../shaders/shader.frag");

  const GLchar *vertex = vertexShader.c_str();
  const GLchar *fragment = fragmentShader.c_str();

  generateShaders(vertex, fragment);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.0f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
}
