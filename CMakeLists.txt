cmake_minimum_required(VERSION 3.10)
project(space)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

set(SOURCES src/main.cpp src/GLUtils/window.cpp)

set(HEADERS src/GLUtils/window.h)

add_executable(space ${SOURCES} ${HEADERS})

target_include_directories(space PRIVATE ${OPENGL_INCLUDE_DIR} ${CMAKE_SRC_DIR}/src)

target_link_libraries(space GLEW::GLEW glfw OpenGL::GL)


