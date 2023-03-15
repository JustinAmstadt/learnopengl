#ifndef DRAGONFLY_H
#define DRAGONFLY_H

#include <array>

#include "Shader.h"
#include "Cube.h"
#include "Scene.h"
#include "DebugShape.h"

class Dragonfly {
  public:
    Dragonfly(std::shared_ptr<Shader> shaderProgram){
      this->shaderProgram = shaderProgram;
      drawRectangleWings(shaderProgram);
    }

    ~Dragonfly(){
      body.reset();
    }

    std::vector<std::shared_ptr<SceneObject>> getWings(){
      return wingptr;
    }

  private:
    float wingDistance = .1;
    int wingDetail = 4;
    float defaultWingLength = 4.9;
    glm::vec3 bodySize = glm::vec3(2, 2, 5);
    float wingEndRadius = 0.5;
    float startingYHeight = 5;

    std::shared_ptr<GeometricObject> body = std::make_shared<Cube>();
    std::vector<glm::vec3> wingPts;

    std::vector<std::shared_ptr<SceneObject>> wingptr;

    std::shared_ptr<Shader> shaderProgram;

    void drawRectangleWings(std::shared_ptr<Shader> shaderProgram){
      wingPts.clear(); // Accounting for if the other draw wing method was called
      for (float i = 0; i <= wingDetail; i += wingDistance){
        // front wing
        wingPts.push_back(glm::vec3(i, startingYHeight, 0));
        wingPts.push_back(glm::vec3(i, startingYHeight, 3));
      }

      makeWingPtr(wingPts);
    }

    void drawDragonflyWings(std::shared_ptr<Shader> shaderProgram){
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
      
      makeWingPtr(wingPts);
    }

    void makeWingPtr(std::vector<glm::vec3> wingPts){
      std::shared_ptr<GeometricObject> line = std::make_shared<GeometricObject>(wingPts);
      line->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
      std::shared_ptr<SceneObject> list = std::make_shared<SceneObject>();
      GLuint VAO = Scene::createVAO(line->vertexData);
      *list = { line, VAO, glm::mat4(1.0f), shaderProgram, GL_TRIANGLE_STRIP };
      wingptr.push_back(list);

      glm::mat4 model(1.0f);
      model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.3f));

      list = std::make_shared<SceneObject>();
      *list = { line, VAO, model, shaderProgram, GL_TRIANGLE_STRIP };
      wingptr.push_back(list);

      model = glm::translate(model, glm::vec3(0.5f, 0.0f, -3.3f));
      model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // rotate is messing with height
      list = std::make_shared<SceneObject>();
      *list = { line, VAO, model, shaderProgram, GL_TRIANGLE_STRIP };
      wingptr.push_back(list);
    }

    void drawBody(){

    }

    void flap(){

    }

    void move(glm::vec3 direction){

    }

};

#endif
