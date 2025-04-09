#include <GL/glew.h>
#include <iostream>

int checkErrors() {
  GLenum error = glGetError();
  while (error != GL_NO_ERROR) {
    switch (error) {
    case GL_INVALID_ENUM:
      std::cout << "ERROR: Invalid enum" << std::endl;
    case GL_INVALID_VALUE:
      std::cout << "ERROR: Invalid value" << std::endl;
    default:
      std::cout << "ERROR: Unkown error" << std::endl;
      break;
    }
    error = glGetError();
  }
  return error;
}
