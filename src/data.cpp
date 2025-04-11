#include <cstdint>
#include <vector>

std::vector<float> getVertices() {

  std::vector<float> vertices = {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                                 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f};

  return vertices;
}

std::vector<uint8_t> getIndices() {
  std::vector<uint8_t> indices = {0, 1, 2, 1, 2, 3};
  return indices;
}
