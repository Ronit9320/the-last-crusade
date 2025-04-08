#include <fstream>
#include <iostream>
#include <sstream>

std::string readFromFile(const std::string &filePath) {
  std::ifstream file(filePath);
  if (!file.is_open()) {
    std::cout << "Failed to open shader file" << std::endl;
    return "";
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::cout << buffer.str() << std::endl;
  return buffer.str();
}
