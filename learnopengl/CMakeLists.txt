cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)

project(MazeBotOpenGL)

# Set the path to the OpenGL libraries
find_package(OpenGL REQUIRED)

# Set the path to the GLFW library
find_package(glfw3 REQUIRED)

find_package(Boost REQUIRED)

include_directories(include)

add_executable(MazeBotOpenGL 
  Main.cpp 
  Scene.cpp 
  Shader.cpp 
  ObjectData.cpp 
  GeometricObject.cpp 
  CircularParabola.cpp
  Pipe.cpp
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
)

add_library(glad STATIC glad.c)

target_compile_options(MazeBotOpenGL PRIVATE -Wall -Wextra -g)

target_link_libraries(MazeBotOpenGL ${Boost_LIBRARIES})
target_link_libraries(MazeBotOpenGL PRIVATE ${OPENGL_LIBRARIES} glfw glad)
