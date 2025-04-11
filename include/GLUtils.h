#ifndef GLUTILS_H
#define GLUTILS_H
#include <GL/glew.h>
#include <iostream>

namespace GLUtils {
unsigned int generateShaders(const char *vertexShaderSource,
                             const char *fragmentShaderSource);

unsigned int genBuffers(float *vertices, unsigned int *indices, size_t vertSize,
                        size_t indSize);
unsigned int loadTextures();
} // namespace GLUtils
#endif // !SHADERS_H
