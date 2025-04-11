#ifndef GLUTILS_H
#define GLUTILS_H
#include <GL/glew.h>
#include <iostream>

namespace GLUtils {
unsigned int generateShaders(const char *vertexShaderSource,
                             const char *fragmentShaderSource);

void attributeHandler(float *vertices, size_t vertex_count);
unsigned int loadTextures(unsigned int texture);
} // namespace GLUtils
#endif // !SHADERS_H
