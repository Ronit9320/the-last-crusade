#include "../src/file_io/shader_utils.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <string>

const size_t buffer_width = 720;
const size_t buffer_height = 480;

struct Buffer {
  size_t width, height;
  uint32_t *data;
};

void error_callback(int error, const char *description);
uint32_t rgb_to_uint32(uint8_t r, uint8_t g, uint8_t b);
void buffer_clear(Buffer *buffer, uint32_t color);
void setup_texture(GLuint *texture);
void setup_quad(GLuint *vao, GLuint *vbo);

int main() {
  glfwSetErrorCallback(error_callback);
  GLFWwindow *window;

  if (!glfwInit()) {
    return -1;
  }

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  window = glfwCreateWindow(buffer_width, buffer_height, "Space Invaders", NULL,
                            NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }
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

  GLuint texture;
  setup_texture(&texture);

  GLuint vao, vbo;
  setup_quad(&vao, &vbo);

  std::string shaderDir = "shaders/";
  std::string vertexShaderPath = shaderDir + "basic.vert";
  std::string fragmentShaderPath = shaderDir + "basic.frag";

  GLuint shaderProgram =
      ShaderUtils::createShaderProgram(vertexShaderPath, fragmentShaderPath);
  if (shaderProgram == 0) {
    std::cerr << "Failed to create shader program" << std::endl;
    glfwTerminate();
    return -1;
  }

  uint32_t clear_color = rgb_to_uint32(0, 128, 0);
  Buffer buffer;
  buffer.width = buffer_width;
  buffer.height = buffer_height;
  buffer.data = new uint32_t[buffer.width * buffer.height];
  buffer_clear(&buffer, clear_color);

  glClearColor(0.0, 0.0, 0.0, 1.0);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, buffer.width, buffer.height,
                    GL_RGBA, GL_UNSIGNED_BYTE, buffer.data);

    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6); // 6 vertices for 2 triangles

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  delete[] buffer.data;
  glDeleteProgram(shaderProgram);
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  glDeleteTextures(1, &texture);
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}

void setup_texture(GLuint *texture) {
  glGenTextures(1, texture);
  glBindTexture(GL_TEXTURE_2D, *texture);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, buffer_width, buffer_height, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void setup_quad(GLuint *vao, GLuint *vbo) {
  float vertices[] = {-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,  -1.0f, 1.0f, 0.0f,
                      1.0f,  1.0f,  1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
                      1.0f,  1.0f,  1.0f, 1.0f, -1.0f, 1.0f,  0.0f, 1.0f};

  glGenVertexArrays(1, vao);
  glGenBuffers(1, vbo);

  glBindVertexArray(*vao);

  glBindBuffer(GL_ARRAY_BUFFER, *vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                        (void *)(2 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

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
