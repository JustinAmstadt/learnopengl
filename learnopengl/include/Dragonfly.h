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

struct DragonFlyDim {
  float bodyWidth;
  float bodyHeight;
  float bodyLength;
  float wallThickness;
  float wingWidth;
  float wingLength;
  float wingThickness;
};

class Dragonfly : public PhysicsObject {
  public:

    const int CFP_CUBED_MASS = 1600; // mass of a thin piece of carbon fiber plate per cubic meter in grams
    const float CFP_DENSITY = 1.5f;

    Dragonfly(std::shared_ptr<Shader> wingShader, std::shared_ptr<Shader> bodyShader, float tl, float bl, float tr, float br){

      dim.wingLength = 2;
      dim.wingWidth = dim.wingLength / 2.0f;
      dim.bodyWidth = dim.wingLength / 2.0f;
      dim.bodyLength = dim.wingWidth * 2.0 + wingGap;
      dim.bodyHeight = dim.bodyWidth * 1.2f;
      dim.wallThickness = 0.1f;
      dim.wingThickness = 0.1f;
      wingGap = dim.wingWidth / 20.0f;
      wingXOffset = (dim.bodyWidth / 2.0f) * (9.0f / 10.0f);

      attrib.accel = glm::vec3(0.0f, 0.0f, 0.0f);
      attrib.velocity = glm::vec3(0.0f);
      attrib.mass = 2;
      attrib.pos = glm::vec3(0.0f);
      attrib.density = CFP_DENSITY;
      attrib.area = 1;
      attrib.Cd = .3;
      attrib.rho = 1.225;

      drawRectangleWings(wingShader);
      drawBody(bodyShader);
      setLeftWingAngle(tl, bl);
      setRightWingAngle(tr, br);

      translate(startingOffset);
      attrib.pos = startingOffset;
    }

    ~Dragonfly(){
      wingptr.clear();
      bodyPtr.reset();
    }

    // returns two SceneObject ptrs that point to the wings
    std::vector<std::shared_ptr<SceneObject>> getWings(){
      return wingptr;
    }

    // Returns a SceneObject ptr that points to the cube that is the body
    std::shared_ptr<SceneObject> getBody(){
      return bodyPtr;
    }

    // Returns the difference in position from one render cycle to the next
    const glm::vec3& getDeltaP(){
      return deltaP;
    }

    // Translates the body and wings by a certain distance
    void translate(glm::vec3 direction){
      glm::mat4 translate = glm::translate(glm::mat4(1.0f), direction);
      for(const std::shared_ptr<SceneObject>& wing : wingptr){
        wing->model = translate * wing->model;
      }

      bodyPtr->model = translate * bodyPtr->model;
    }

    void update(float deltaT){
      float currentTime = glfwGetTime();

      // Sets the angles for the right and left wing. This is plugged into the wingAngle in dragonfly.vert 
      leftUniform = glm::radians((leftTopAngle / 2.0f + leftBottomAngle / 2.0f)
        * sin(upWingSpeed * currentTime) + (leftTopAngle / 2.0f - leftBottomAngle / 2.0f));
      rightUniform = glm::radians((rightTopAngle / 2.0f + rightBottomAngle / 2.0f)
        * sin(upWingSpeed * currentTime) + (rightTopAngle / 2.0f - rightBottomAngle / 2.0f));
      
      // std::cout << "curAngle - prevAngle: " << glm::degrees(leftUniform - prevUniform) << ", leftUniform: " << glm::degrees(leftUniform) << ", rightUniform: " << rightUniform << ", wingSpeed: " << upWingSpeed << std::endl;

      deltaP = physUpdate(deltaT);
      translate(deltaP);
    }

    // Calculates the Flift that gets transformed into acceleration in the physics calculations
    virtual void calcLift(){
      float wingDiffFactor = 0.009f;
      force.Flift = glm::vec3(0.0f);

      force.Flift += glm::vec3(0.0f, upWingSpeed / 2.0f, 0.0f);
      
      // ensures that the dragonfly isn't moving sideways on the ground
      if(attrib.pos.y > 0){
        force.Flift += glm::vec3((leftTopAngle - rightTopAngle) * wingDiffFactor * upWingSpeed, 0.0f, 0.0f);
      }
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

    void decWingSpeed(){
      upWingSpeed--;
      if(upWingSpeed < 0){
        upWingSpeed = 0;
      }
    }

    void incWingSpeed(){
      upWingSpeed++;
    }

    // Sets the wing angles to go left
    void goLeft(){
      setRightWingAngle(rightTopAngle + 1.0f, rightBottomAngle - 1.0f); // increase angle
      setLeftWingAngle(leftTopAngle - 1.0f, leftBottomAngle + 1.0f); // decrease angle
    }

    // Sets the wing angles to go right
    void goRight(){
      setLeftWingAngle(leftTopAngle + 1.0f, leftBottomAngle - 1.0f); // increase angle
      setRightWingAngle(rightTopAngle - 1.0f, rightBottomAngle + 1.0f); // decrease angle
    }

    // Increase left angle
    void inclAngle(){
      setLeftWingAngle(leftTopAngle + 1.0f, leftBottomAngle - 1.0f);
    }

    // Decrease left angle
    void declAngle(){
      setLeftWingAngle(leftTopAngle - 1.0f, leftBottomAngle + 1.0f);
    }

    // Increase right angle
    void incrAngle(){
      setRightWingAngle(rightTopAngle + 1.0f, rightBottomAngle - 1.0f);
    }

    // Decrease right angle
    void decrAngle(){
      setRightWingAngle(rightTopAngle - 1.0f, rightBottomAngle + 1.0f);
    }

    void incluAngle(){
      setLeftWingAngle(leftTopAngle + 1.0f, leftBottomAngle);
    }

    void incldAngle(){
      setLeftWingAngle(leftTopAngle, leftBottomAngle + 1.0f);
    }

    void decluAngle(){
      setLeftWingAngle(leftTopAngle - 1.0f, leftBottomAngle);
    }

    void decldAngle(){
      setLeftWingAngle(leftTopAngle, leftBottomAngle - 1.0f);
    }

    void incruAngle(){
      setRightWingAngle(rightTopAngle + 1.0f, rightBottomAngle);
    }

    void incrdAngle(){
      setRightWingAngle(rightTopAngle, rightBottomAngle + 1.0f);
    }

    void decruAngle(){
      setRightWingAngle(rightTopAngle - 1.0f, rightBottomAngle);
    }

    void decrdAngle(){
      setRightWingAngle(rightTopAngle, rightBottomAngle - 1.0f);
    }

  private:
    DragonFlyDim dim;

    float wingDistance = 0.1;
    float defaultWingLength = 4.9;
    float wingEndRadius = 0.5;
    float startingYHeight = 5;
    float wingXOffset;
    float wingGap;
    glm::vec3 startingOffset = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 deltaP;

    float leftTopAngle = 0;
    float leftBottomAngle = 0;
    float rightTopAngle = 0;
    float rightBottomAngle = 0;

    float upWingSpeed = 15.0f;
    float downWingSpeed = 8.0f;
    float leftUniform;
    float rightUniform;

    std::vector<glm::vec3> wingPts;

    std::vector<std::shared_ptr<SceneObject>> wingptr;
    std::shared_ptr<SceneObject> bodyPtr;
    
    // give angle difference in radians
    // returns the new speed. gives back same speed if no change is necessary
    float swapWingSpeed(float curSpeed, float angleDifference){
      static bool diffIsPos = 1;
      static int cooldown = 5;
      
      if(diffIsPos && angleDifference < 0 && cooldown <= 0){
        diffIsPos = 0;
        cooldown = 3;
        return downWingSpeed;
      }
      else if(!diffIsPos && angleDifference > 0 && cooldown <= 0){
        diffIsPos = 1;
        cooldown = 3;
        return upWingSpeed;
      }
      
      cooldown--;
      
      return curSpeed;
    }

    // Makes rectangular wings
    void drawRectangleWings(std::shared_ptr<Shader> wingShader){
      wingPts.clear(); // Accounting for if the other draw wing method was called
      for (float i = 0; i <= dim.wingLength; i += wingDistance){
        wingPts.push_back(glm::vec3(i, 0.0f, 0));
        wingPts.push_back(glm::vec3(i, 0.0f, dim.wingWidth));
      }

      makeWingPtr(wingPts, wingShader);
    }

    // Makes circular wings that are more shaped like a dragonfly (doesn't work)
    void drawDragonflyWings(std::shared_ptr<Shader> wingShader){
      wingPts.clear(); // Accounting for if the other draw wing method was called
      // long part
      for (float i = 0; i <= defaultWingLength; i += dim.wingLength / defaultWingLength){
        wingPts.push_back(glm::vec3(i, startingYHeight, (float)sqrt( 0.102 * i)));
        wingPts.push_back(glm::vec3(i, startingYHeight, -(float)sqrt( 0.102 * i)));
      }

      float wingEndOutput = 1;
      for (float i = 0; wingEndOutput > 0; i += dim.wingLength / wingEndRadius){
        wingEndOutput = (float)sqrt(0.5 - std::pow(i - defaultWingLength, 2));
        wingPts.push_back(glm::vec3(i, startingYHeight, wingEndOutput));
        wingPts.push_back(glm::vec3(i, startingYHeight, -wingEndOutput));
      }
      
      makeWingPtr(wingPts, wingShader);
    }

    // Creates the SceneObjects for each of the four wings
    void makeWingPtr(std::vector<glm::vec3> wingPts, std::shared_ptr<Shader> wingShader);

    // Creates the SceneObject that points to the rectangular body of the dragonfly
    void drawBody(std::shared_ptr<Shader> bodyShader){
      std::shared_ptr<GeometricObject> body = std::make_shared<Cube>(glm::vec4(0.346f, 0.533f, 1.0f, 1.0f));
      glm::mat4 model(1.0f);
      std::shared_ptr<SceneObject> list = std::make_shared<SceneObject>();

      model = glm::translate(model, glm::vec3(0.0f, 0.0f, dim.wingWidth + wingGap / 2.0f));
      model = glm::scale(model, glm::vec3(dim.bodyWidth, dim.bodyHeight, dim.bodyLength));
      *list = { body, model, bodyShader, GL_TRIANGLES };
      bodyPtr = list;
    }

    // Returns wing mass of all 4 wings
    float getWingMass(const DragonFlyDim & dim){
      float wingArea = dim.wingWidth * dim.wingLength;
      return 4 * attrib.density * wingArea * dim.wingThickness;
    }

    // return total surface area of body and wings. don't see a use though
    virtual float getSurfaceArea(){
      float bodySurfaceArea = 2 * dim.bodyHeight * dim.bodyWidth + 2 * dim.bodyHeight * dim.bodyLength + 2 * dim.bodyWidth * dim.bodyLength;
      float wingSurfaceArea = 4 * dim.wingLength * dim.wingWidth;
      return bodySurfaceArea + wingSurfaceArea;
    }
    
    // Returns the surface area that faces -y when not rotated
    virtual float getBottomSurfaceArea(){
      float bodyBottom = dim.bodyWidth * dim.bodyLength;
      float wingSurfaceArea = 4 * dim.wingLength * dim.wingWidth;
      return bodyBottom + wingSurfaceArea;
    }

    // returns body mass of drone
    virtual float getBodyMass(){
      float V1 = dim.bodyLength * dim.bodyWidth * dim.bodyHeight;
      float V2 = (dim.bodyLength - 2 * dim.wallThickness) * (dim.bodyWidth - 2 * dim.wallThickness) * (dim.bodyHeight - 2 * dim.wallThickness);
      return attrib.density * (V1 - V2);
    }

};


#endif
