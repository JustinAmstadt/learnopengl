cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)

project(hellotriangle)

# Find the required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(assimp REQUIRED)

# Include directories
include_directories(include)

# Glob all source files
file(GLOB SOURCES "src/*.cpp")

# Add executable with all sources
add_executable(hellotriangle
  ${SOURCES}
)

# Add the glad library
add_library(glad STATIC glad.c)

# Set compile options
target_compile_options(hellotriangle PRIVATE -Wall -Wextra -ggdb)

# Link libraries
target_link_libraries(hellotriangle PRIVATE ${OPENGL_LIBRARIES} glfw glad assimp::assimp)

# Include Assimp directories (though not strictly necessary since find_package already does it)
target_include_directories(hellotriangle PRIVATE ${ASSIMP_INCLUDE_DIRS})
