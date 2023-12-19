#ifndef ARROW_H
#define ARROW_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <vector>

#include "Scene.h"
#include "GeometricObject.h"
#include "Shader.h"

class Arrow{
public:
  // requires a shader program and how many degrees to rotate the arrow
  Arrow(std::shared_ptr<Shader> shaderProgram){
    makeArrow(shaderProgram);
  }

  std::shared_ptr<SceneObject> getObjPtr(){
    return objPtr;
  }

  void update(glm::vec3 position, glm::vec3 newScale, float rotateDegrees){
    // glm::vec3 scale, rotation, translation, skew;
    // glm::quat orientation;
    // glm::vec4 perspective;
    // glm::decompose(objPtr->model, scale, orientation, translation, skew, perspective);

    // Create a new translation matrix using the new position
    glm::mat4 newTranslation = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 newScaling = glm::scale(glm::mat4(1.0f), newScale);
    glm::mat4 newRotation = glm::rotate(glm::mat4(1.0f), glm::radians(rotateDegrees), glm::vec3(0.0f, 0.0f, 1.0f));

    // Combine the new translation with the existing rotation and scaling
    objPtr->model = newTranslation * newRotation * newScaling;
  }

  void translate(glm::vec3 direction){
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), direction);
    objPtr->model = translate * objPtr->model;
  }

  void scale(glm::vec3 size){
    glm::mat4 scale = glm::scale(scale, size);
    objPtr->model = scale * objPtr->model;
  }

  void rotate(float degrees){
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(degrees), glm::vec3(0.0f, 0.0f, 1.0f));
    objPtr->model = rotation * objPtr->model;
  }

private:
  std::shared_ptr<SceneObject> objPtr;
	std::vector<glm::vec3> verts;
  std::vector<GLuint> indicies;

  void makeArrow(std::shared_ptr<Shader> shaderProgram){
    verts.push_back(glm::vec3(0.0f));
    verts.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
    verts.push_back(glm::vec3(0.7f, 0.3f, 0.0f));
    verts.push_back(glm::vec3(0.7f, -0.3f, 0.0f));

    // body
    indicies.push_back(0);
    indicies.push_back(1);

    // top head
    indicies.push_back(1);
    indicies.push_back(2);

    // bottom head
    indicies.push_back(1);
    indicies.push_back(3);


    std::shared_ptr<GeometricObject> line = std::make_shared<GeometricObject>(verts);
    line->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    line->getMesh().indices = indicies;
    objPtr = std::make_shared<SceneObject>();
    *objPtr = { line, glm::mat4(1.0f), shaderProgram, GL_LINES };
  }
};

#endif
