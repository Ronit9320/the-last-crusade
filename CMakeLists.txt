cmake_minimum_required(VERSION 3.10)
project(space)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

# Define source files
set(SOURCES src/main.cpp src/file_io/shader_utils.cpp)

# Define header files
set(HEADERS src/file_io/shader_utils.h)

# Create executable
add_executable(space ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(space PRIVATE ${OPENGL_INCLUDE_DIR}
                                         ${CMAKE_SOURCE_DIR}/src)

# Link libraries
target_link_libraries(space GLEW::GLEW glfw OpenGL::GL)

# Optional: Add a custom command to copy shaders when they change
add_custom_command(
  TARGET space
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders
          ${CMAKE_BINARY_DIR}/shaders)
