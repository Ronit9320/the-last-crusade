cmake_minimum_required(VERSION 3.10)
project(space)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(SDL3 REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(space ${SOURCES})

target_include_directories(
  space PRIVATE ${OPENGL_INCLUDE_DIR} ${CMAKE_SRC_DIR}/include
                ${CMAKE_SRC_DIR}/src)

target_link_libraries(space GLEW::GLEW glfw OpenGL::GL SDL3::SDL3)
