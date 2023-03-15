#ifndef DRAGONFLY_H
#define DRAGONFLY_H

#include <glm/glm.hpp>
#include <array>

#include "Shader.h"
#include "Cube.h"
#include "Scene.h"

class Dragonfly {
  public:
    Dragonfly(std::shared_ptr<Shader> shaderProgram){
      drawWings(shaderProgram);
    }

    ~Dragonfly(){
      body.reset();
    }

    std::shared_ptr<SceneObject> getWings(){
      return wingptr;
    }

  private:
    int wingDetail = 10;
    float defaultWingLength = 4.9;
    glm::vec3 bodySize = glm::vec3(2, 2, 5);
    float wingEndRadius = 0.5;
    float startingYHeight = 5;

    std::shared_ptr<GeometricObject> body = std::make_shared<Cube>();
    std::vector<glm::vec3> wingPts;

    std::shared_ptr<SceneObject> wingptr;

    void drawWings(std::shared_ptr<Shader> shaderProgram){
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

      std::shared_ptr<GeometricObject> line = std::make_shared<GeometricObject>(wingPts);
      line->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
      wingptr = std::make_shared<SceneObject>();
      *wingptr = { line, Scene::createVAO(line->vertexData), glm::mat4(1.0f), shaderProgram, GL_LINES};
    }

    void drawBody(){

    }

    void flap(){

    }

    void move(glm::vec3 direction){

    }

};

#endif
