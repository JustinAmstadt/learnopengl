#ifndef DEBUG_SHAPE_H
#define DEBUG_SHAPE_H

#include <memory>

#include "Scene.h"
#include "Cube.h"
#include "Shader.h"

class DebugShape{
  public:
    DebugShape(std::shared_ptr<Shader> shaderProgram){
      std::shared_ptr<GeometricObject> cubeGeom = std::make_shared<Cube>();
      GLuint cubeVAO = Scene::createVAO(cubeGeom->vertexData);
      *cubeptr = { cubeGeom, cubeVAO, glm::mat4(1.0f), shaderProgram, GL_TRIANGLES };
    }

    std::shared_ptr<SceneObject> getDebugPtr(){
      return cubeptr;
    }

  private:
    std::shared_ptr<SceneObject> cubeptr;
};

#endif
