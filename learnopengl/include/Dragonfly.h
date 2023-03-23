#ifndef DRAGONFLY_H
#define DRAGONFLY_H

#include <array>
#include <algorithm>

#include "Shader.h"
#include "Cube.h"
#include "Scene.h"
#include "DebugShape.h"
#include "Physics.h"

#include <GLFW/glfw3.h>


class DragonflyPhysics{

  public:

    const int CFP_CUBED_MASS = 1600; // mass of a thin piece of carbon fiber plate per cubic meter in grams
    PhysAttributes attrib;

    float wingArea;
    // body surfaces
    
    DragonflyPhysics(float cubeDimH, float cubeDimW, float cubeDimL, float wingL, float wingW){
      attrib.mass = getSurfaceArea(cubeDimH, cubeDimW, cubeDimL, wingL, wingW);

    }

    // return total weight in grams per cubic meter
    float getSurfaceArea(float cubeDimH, float cubeDimW, float cubeDimL, float wingL, float wingW){
      float bodySurfaceArea = 2 * cubeDimH * cubeDimW + 2 * cubeDimH * cubeDimL + 2 * cubeDimW * cubeDimL;
      float wingSurfaceArea = 2 * wingL * wingW;
      return bodySurfaceArea + wingSurfaceArea;
    }


  private:


};

class Dragonfly {
  public:
    Dragonfly(std::shared_ptr<Shader> wingShader, std::shared_ptr<Shader> bodyShader, float tl, float bl, float tr, float br){
      drawRectangleWings(wingShader);
      drawBody(bodyShader);
      setLeftWingAngle(tl, bl);
      setRightWingAngle(tr, br);
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

    void update(){
      float currentTime = glfwGetTime();
      leftUniform = glm::radians((leftTopAngle / 2.0f + leftBottomAngle / 2.0f)
        * sin(wingSpeed * currentTime) + (leftTopAngle / 2.0f - leftBottomAngle / 2.0f));
      rightUniform = glm::radians((rightTopAngle / 2.0f + rightBottomAngle / 2.0f)
        * sin(wingSpeed * currentTime) + (rightTopAngle / 2.0f - rightBottomAngle / 2.0f));
    }

    void setLeftWingAngle(float top, float bottom){
      if(top < 90.1f && top > 0 && bottom < 90.1f && bottom > 0){
        leftTopAngle = top;
        leftBottomAngle = bottom;
      }
    }

    void setRightWingAngle(float top, float bottom){
      if(top < 90.1f && top > 0 && bottom < 90.1f && bottom > 0){
        rightTopAngle = top;
        rightBottomAngle = bottom;
      }
    }
    
    float getRightUniform(){
      return rightUniform;
    }

    float getLeftUniform(){
      return leftUniform;
    }

    float getRightTopAngle(){
      return rightTopAngle;
    }

    float getLeftTopAngle(){
      return leftTopAngle;
    }

    float getRightBottomAngle(){
      return rightBottomAngle;
    }

    float getLeftBottomAngle(){
      return leftBottomAngle;
    }

  private:
    float wingDistance = 0.1;
    int wingLength = 2;
    float wingWidth = wingLength / 2.0f;
    float wingGap = wingWidth / 20.0f;
    float defaultWingLength = 4.9;
    float wingEndRadius = 0.5;
    float startingYHeight = 5;
    float bodyWidth = wingLength / 2.0f;
    float bodyLength = wingWidth * 2.0 + wingGap;
    float bodyHeight = bodyWidth * 1.2f;
    float wingXOffset = (bodyWidth / 2.0f) * (9.0f / 10.0f);

    float leftTopAngle = 0;
    float leftBottomAngle = 0;
    float rightTopAngle = 0;
    float rightBottomAngle = 0;

    float wingSpeed = 10.0f;
    float leftUniform;
    float rightUniform;


    std::vector<glm::vec3> wingPts;

    std::vector<std::shared_ptr<SceneObject>> wingptr;
    std::shared_ptr<SceneObject> bodyPtr;

    void drawRectangleWings(std::shared_ptr<Shader> wingShader){
      wingPts.clear(); // Accounting for if the other draw wing method was called
      for (float i = 0; i <= wingLength; i += wingDistance){
        wingPts.push_back(glm::vec3(i, 0.0f, 0));
        wingPts.push_back(glm::vec3(i, 0.0f, wingWidth));
      }

      makeWingPtr(wingPts, wingShader);
    }

    void drawDragonflyWings(std::shared_ptr<Shader> wingShader){
      wingPts.clear(); // Accounting for if the other draw wing method was called
      // long part
      for (float i = 0; i <= defaultWingLength; i += wingLength / defaultWingLength){
        wingPts.push_back(glm::vec3(i, startingYHeight, (float)sqrt( 0.102 * i)));
        wingPts.push_back(glm::vec3(i, startingYHeight, -(float)sqrt( 0.102 * i)));
      }

      float wingEndOutput = 1;
      for (float i = 0; wingEndOutput > 0; i += wingLength / wingEndRadius){
        wingEndOutput = (float)sqrt(0.5 - std::pow(i - defaultWingLength, 2));
        wingPts.push_back(glm::vec3(i, startingYHeight, wingEndOutput));
        wingPts.push_back(glm::vec3(i, startingYHeight, -wingEndOutput));
      }
      
      makeWingPtr(wingPts, wingShader);
    }

    void makeWingPtr(std::vector<glm::vec3> wingPts, std::shared_ptr<Shader> wingShader);

    void drawBody(std::shared_ptr<Shader> bodyShader){
      std::shared_ptr<GeometricObject> body = std::make_shared<Cube>(glm::vec4(0.346f, 0.533f, 1.0f, 1.0f));
      glm::mat4 model(1.0f);
      std::shared_ptr<SceneObject> list = std::make_shared<SceneObject>();

      model = glm::translate(model, glm::vec3(0.0f, 0.0f, wingWidth + wingGap / 2.0f));
      model = glm::scale(model, glm::vec3(bodyWidth, bodyHeight, bodyLength));
      *list = { body, Scene::createVAO(body->vertexData), model, bodyShader, GL_TRIANGLES };
      bodyPtr = list;

    }

};


#endif
