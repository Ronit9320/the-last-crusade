#ifndef SHADERS_H
#define SHADERS_H
#include <GL/glew.h>
#include <iostream>

namespace shaderUtils {
unsigned int generateShaders(const char *vertexShaderSource,
                             const char *fragmentShaderSource);

void attributeHandler(float *vertices, size_t vertex_count);
} // namespace shaderUtils
#endif // !SHADERS_H
