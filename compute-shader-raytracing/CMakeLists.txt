cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)

project(computeshaderraytracer)

# Set the path to the OpenGL libraries
find_package(OpenGL REQUIRED)

# Set the path to the GLFW library
find_package(glfw3 REQUIRED)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(computeshaderraytracer
  ${SOURCES}
)

add_library(glad STATIC glad.c)

target_compile_options(computeshaderraytracer PRIVATE -Wall -Wextra -ggdb)

target_link_libraries(computeshaderraytracer PRIVATE ${OPENGL_LIBRARIES} glfw glad)