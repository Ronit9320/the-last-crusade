#include "../include/window.h"
#include <iostream>

int main() {
  std::cout << "starting window creation" << std::endl;
  int width = 800;
  int height = 600;
  createWindow(width, height);
  return 0;
}
