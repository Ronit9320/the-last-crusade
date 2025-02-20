#pragma once

#include <GL/glew.h>
#include <string>

namespace ShaderUtils {
std::string loadShaderFromFile(const std::string &filepath);

GLuint compileShader(GLenum shaderType, const std::string &source);

GLuint createShaderProgram(const std::string &vertexShaderPath,
                           const std::string &fragmentShaderPath);

bool checkShaderErrors(GLuint object, GLenum statusType);

void printShaderLog(GLuint shaderObj);

void printProgramLog(GLuint program);
} // namespace ShaderUtils
