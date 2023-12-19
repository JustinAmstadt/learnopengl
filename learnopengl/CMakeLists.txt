cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)

project(learnopengl)

# Set the path to the OpenGL libraries
find_package(OpenGL REQUIRED)

# Set the path to the GLFW library
find_package(glfw3 REQUIRED)
# find_package(assimp REQUIRED)

find_package(assimp REQUIRED)

include_directories(include)
# include_directories(${ASSIMP_INCLUDE_DIRS})

file(GLOB SOURCES "src/*.cpp")

add_executable(learnopengl
<<<<<<< HEAD
  ${SOURCES}
=======
  Main.cpp 
  Scene.cpp 
  Shader.cpp 
  ObjectData.cpp 
  GeometricObject.cpp 
  CircularParabola.cpp
  Pipe.cpp
  Dragonfly.cpp
  include/Bot.h
  include/Cube.h
  include/GeometricObject.h
  include/MazeScene.h
  include/PositionalLight.h
  include/Scene.h
  include/Spotlight.h
  include/Tragectory.h
  include/Camera.h
  include/DirectionalLight.h
  include/GridFloor.h
  include/ObjectData.h
  include/Rain.h
  include/Shader.h
  include/Square.h
  include/CircularParabola.h
  include/FlatPlane.h
  include/Light.h
  include/OceanScene.h
  include/SandboxScene.h
  include/Skybox.h
  include/TessellationPlaneScene.h
  include/Dragonfly.h
  include/DebugShape.h
  include/Physics.h
  include/Arrow.h
>>>>>>> 0d723aba1af2c973d31adef636a00a16e2a3d6ee
)

add_library(glad STATIC glad.c)

target_compile_options(learnopengl PRIVATE -Wall -Wextra -ggdb)

<<<<<<< HEAD
target_link_libraries(learnopengl PRIVATE ${OPENGL_LIBRARIES} glfw glad assimp::assimp)
target_include_directories(learnopengl PRIVATE ${ASSIMP_INCLUDE_DIRS})
=======
# ${ASSIMP_LIBRARIES} in target_link_libraries
target_link_libraries(learnopengl PRIVATE ${OPENGL_LIBRARIES} glfw glad)
>>>>>>> 0d723aba1af2c973d31adef636a00a16e2a3d6ee
