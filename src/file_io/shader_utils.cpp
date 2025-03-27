#include "shader_utils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace ShaderUtils {

std::string loadShaderFromFile(const std::string &filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    std::cerr << "Failed to open shader file: " << filepath << std::endl;
    return "";
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

GLuint compileShader(GLenum shaderType, const std::string &source) {
  GLuint shader = glCreateShader(shaderType);
  const char *sourcePtr = source.c_str();
  glShaderSource(shader, 1, &sourcePtr, nullptr);
  glCompileShader(shader);

  if (!checkShaderErrors(shader, GL_COMPILE_STATUS)) {
    std::cerr << "Shader compilation failed!" << std::endl;
    printShaderLog(shader);
    glDeleteShader(shader);
    return 0;
  }

  return shader;
}

GLuint createShaderProgram(const std::string &vertexShaderPath,
                           const std::string &fragmentShaderPath) {
  std::string vertexSource = loadShaderFromFile(vertexShaderPath);
  std::string fragmentSource = loadShaderFromFile(fragmentShaderPath);

  if (vertexSource.empty() || fragmentSource.empty()) {
    std::cerr << "Failed to load shader sources" << std::endl;
    return 0;
  }

  GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
  GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

  if (vertexShader == 0 || fragmentShader == 0) {
    if (vertexShader != 0)
      glDeleteShader(vertexShader);
    if (fragmentShader != 0)
      glDeleteShader(fragmentShader);
    return 0;
  }

  GLuint program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  if (!checkShaderErrors(program, GL_LINK_STATUS)) {
    std::cerr << "Shader program linking failed!" << std::endl;
    printProgramLog(program);
    glDeleteProgram(program);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return 0;
  }

  glDetachShader(program, vertexShader);
  glDetachShader(program, fragmentShader);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return program;
}

bool checkShaderErrors(GLuint object, GLenum statusType) {
  GLint success = 0;
  if (statusType == GL_COMPILE_STATUS) {
    glGetShaderiv(object, statusType, &success);
  } else if (statusType == GL_LINK_STATUS) {
    glGetProgramiv(object, statusType, &success);
  }
  return success != GL_FALSE;
}

void printShaderLog(GLuint shaderObj) {
  GLint logLength = 0;
  glGetShaderiv(shaderObj, GL_INFO_LOG_LENGTH, &logLength);

  if (logLength > 0) {
    std::vector<char> log(logLength);
    glGetShaderInfoLog(shaderObj, logLength, &logLength, log.data());
    std::cerr << "Shader log: " << log.data() << std::endl;
  }
}

void printProgramLog(GLuint program) {
  GLint logLength = 0;
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

  if (logLength > 0) {
    std::vector<char> log(logLength);
    glGetProgramInfoLog(program, logLength, &logLength, log.data());
    std::cerr << "Program log: " << log.data() << std::endl;
  }
}

} // namespace ShaderUtils
