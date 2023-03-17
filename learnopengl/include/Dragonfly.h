#ifndef DRAGONFLY_H
#define DRAGONFLY_H

#include <array>

#include "Shader.h"
#include "Cube.h"
#include "Scene.h"
#include "DebugShape.h"

class Dragonfly {
  public:
    Dragonfly(std::shared_ptr<Shader> wingShader, std::shared_ptr<Shader> bodyShader){
      drawRectangleWings(wingShader);
      drawBody(bodyShader);
    }

    ~Dragonfly(){
      wingptr.clear();
      bodyPtr.reset();
    }

    std::vector<std::shared_ptr<SceneObject>> getWings(){
      return wingptr;
    }

    std::shared_ptr<SceneObject> getBody(){
      return bodyPtr;
    }

    void translate(glm::vec3 direction){
      glm::mat4 translate = glm::translate(glm::mat4(1.0f), direction);
      for(const std::shared_ptr<SceneObject> wing : wingptr){
        wing->model = translate * wing->model;
      }

      bodyPtr->model = translate * bodyPtr->model;
    }
  private:
    float wingDistance = 0.1;
    int wingDetail = 4;
    float defaultWingLength = 4.9;
    float wingEndRadius = 0.5;
    float startingYHeight = 5;

    std::vector<glm::vec3> wingPts;

    std::vector<std::shared_ptr<SceneObject>> wingptr;
    std::shared_ptr<SceneObject> bodyPtr;

    void drawRectangleWings(std::shared_ptr<Shader> wingShader){
      wingPts.clear(); // Accounting for if the other draw wing method was called
      for (float i = 0; i <= wingDetail; i += wingDistance){
        // front wing
        wingPts.push_back(glm::vec3(i, 0.0f, 0));
        wingPts.push_back(glm::vec3(i, 0.0f, 3));
      }

      makeWingPtr(wingPts, wingShader);
    }

    void drawDragonflyWings(std::shared_ptr<Shader> wingShader){
      wingPts.clear(); // Accounting for if the other draw wing method was called
      // long part
      for (float i = 0; i <= defaultWingLength; i += wingDetail / defaultWingLength){
        wingPts.push_back(glm::vec3(i, startingYHeight, (float)sqrt( 0.102 * i)));
        wingPts.push_back(glm::vec3(i, startingYHeight, -(float)sqrt( 0.102 * i)));
      }

      float wingEndOutput = 1;
      for (float i = 0; wingEndOutput > 0; i += wingDetail / wingEndRadius){
        wingEndOutput = (float)sqrt(0.5 - std::pow(i - defaultWingLength, 2));
        wingPts.push_back(glm::vec3(i, startingYHeight, wingEndOutput));
        wingPts.push_back(glm::vec3(i, startingYHeight, -wingEndOutput));
      }
      
      makeWingPtr(wingPts, wingShader);
    }

    void makeWingPtr(std::vector<glm::vec3> wingPts, std::shared_ptr<Shader> wingShader){
      std::shared_ptr<GeometricObject> line = std::make_shared<GeometricObject>(wingPts, wingDistance);
      line->setColor(glm::vec4(0.970f, 0.291f, 0.476f, 1.0f));

      // top right
      std::shared_ptr<SceneObject> list = std::make_shared<SceneObject>();
      GLuint VAO = Scene::createVAO(line->vertexData);
      *list = { line, VAO, glm::mat4(1.0f), wingShader, GL_TRIANGLE_STRIP };
      wingptr.push_back(list);

      // bottom right
      glm::mat4 model(1.0f);
      model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.3f));
      list = std::make_shared<SceneObject>();
      *list = { line, VAO, model, wingShader, GL_TRIANGLE_STRIP };
      wingptr.push_back(list);

      // top left
      model = glm::mat4(1.0f);
      glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(1.4f, 0.0f, -6.3f)); // negative z here because we are are rotating 180 degress around y axis. z becomes flipped
      glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // We rotate here so that the endpoints continue to be endpoints on the other side
      model = rotate * translate;
      list = std::make_shared<SceneObject>();
      *list = { line, VAO, model, wingShader, GL_TRIANGLE_STRIP };
      wingptr.push_back(list);
      
      // bottom left
      model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.3f));
      list = std::make_shared<SceneObject>();
      *list = { line, VAO, model, wingShader, GL_TRIANGLE_STRIP };
      wingptr.push_back(list);
    }

    void drawBody(std::shared_ptr<Shader> bodyShader){
      std::shared_ptr<GeometricObject> body = std::make_shared<Cube>(glm::vec4(0.346f, 0.533f, 1.0f, 1.0f));
      glm::mat4 model(1.0f);
      std::shared_ptr<SceneObject> list = std::make_shared<SceneObject>();

      model = glm::translate(model, glm::vec3(-0.7f, 0.0f, 3.2f)); // magic numbers!
      model = glm::scale(model, glm::vec3(1.7f, 1.0f, 6.4f));
      *list = { body, Scene::createVAO(body->vertexData), model, bodyShader, GL_TRIANGLES };
      bodyPtr = list;

    }

    void flap(){

    }

};

#endif
