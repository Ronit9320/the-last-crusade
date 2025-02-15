cmake_minimum_required(VERSION 3.10)

project(space)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(space src/main.cpp)

target_include_directories(space PRIVATE ${OPENGL_INCLUDE_DIR})
target_link_libraries(space GLEW::GLEW glfw OpenGL::GL)

