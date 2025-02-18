#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

const size_t buffer_width = 640;
const size_t buffer_height = 480;

struct Buffer {
  size_t width, height;
  uint32_t *data;
};

void error_callback(int error, const char *description);
uint32_t rgb_to_uint32(uint8_t r, uint8_t g, uint8_t b);
void buffer_clear(Buffer *buffer, uint32_t color);

int main() {

  std::ifstream inFile("../shaders/basic.frag");
  if (!inFile) {
    std::cerr << "Couldn't open file" << std::endl;
    return -1;
  } else {
    std::cout << "File opened successfully" << std::endl;
  }

  glfwSetErrorCallback(error_callback);
  GLFWwindow *window;

  if (!glfwInit()) {
    return -1;
  };

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  window = glfwCreateWindow(640, 480, "Space Invaders", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  };
  glfwMakeContextCurrent(window);

  GLenum err = glewInit();
  if (err != GLEW_OK) {
    fprintf(stderr, "Error initializing GLEW.\n");
    glfwTerminate();
    return -1;
  }

  int glVersion[2] = {-1, 1};
  glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
  glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);

  printf("Using OpenGL: %d.%d\n", glVersion[0], glVersion[1]);

  uint32_t clear_color = rgb_to_uint32(0, 128, 0);
  Buffer buffer;
  buffer.width = buffer_width;
  buffer.height = buffer_height;
  buffer.data = new uint32_t[buffer.width * buffer.height];
  buffer_clear(&buffer, clear_color);

  glClearColor(1.0, 0.0, 0.0, 1.0);
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
};

void error_callback(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

uint32_t rgb_to_uint32(uint8_t r, uint8_t g, uint8_t b) {
  return (r << 24) | (g << 16) | (b << 8) | 255;
}

void buffer_clear(Buffer *buffer, uint32_t color) {
  for (size_t i = 0; i < buffer->width * buffer->height; ++i) {
    buffer->data[i] = color;
  }
}
