#ifndef ARROW_H
#define ARROW_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "Scene.h"
#include "GeometricObject.h"
#include "Shader.h"

class Arrow{
  public:
    Arrow(std::shared_ptr<Shader> shaderProgram, float length){
      makeLine(shaderProgram);
    }
  private:
  std::shared_ptr<SceneObject> objPtr;
	std::vector<glm::vec3> verts;
  float length = 1;

  void makeLine(std::shared_ptr<Shader> shaderProgram){
    verts.push_back(glm::vec3(0.0f));
    verts.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

    std::shared_ptr<GeometricObject> line = std::make_shared<GeometricObject>(verts);
    line->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    objPtr = std::make_shared<SceneObject>();
    *objPtr = { line, Scene::createVAO(line->vertexData), glm::mat4(1.0f), shaderProgram, GL_LINES };


  }

};

#endif
