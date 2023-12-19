cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)

project(learnopengl)

# Set the path to the OpenGL libraries
find_package(OpenGL REQUIRED)

# Set the path to the GLFW library
find_package(glfw3 REQUIRED)

find_package(assimp REQUIRED)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(learnopengl
  ${SOURCES}
)

add_library(glad STATIC glad.c)

target_compile_options(learnopengl PRIVATE -Wall -Wextra -ggdb)

target_link_libraries(learnopengl PRIVATE ${OPENGL_LIBRARIES} glfw glad assimp::assimp)
target_include_directories(learnopengl PRIVATE ${ASSIMP_INCLUDE_DIRS})
