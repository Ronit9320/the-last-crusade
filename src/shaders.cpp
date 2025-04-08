#include "../include/file_io.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void generateShaders() {
  readFromFile("../shaders/shader.frag");
  readFromFile("../shaders/shader.vert");
}
