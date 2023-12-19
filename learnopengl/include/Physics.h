#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

struct PhysAttributes {
  glm::vec3 velocity;
  glm::vec3 accel;
  glm::vec3 pos;

  float weight;
  float mass;
  float density;

  float area;
  float Cd;
  float rho;
};

struct Forces {
  glm::vec3 Fg;
  glm::vec3 Fdrag;
  glm::vec3 Flift;
};

class PhysicsObject{

public:

  constexpr static float GRAVITY_ACCEL_S = 5.81f;
  constexpr static float GRAVITY_ACCEL_MS = 0.00981f;
  constexpr static float FLOOR_HEIGHT = 0.0f;

  const Forces& getForces(){
    return force;
  }

  const PhysAttributes& getAttrib(){
    return attrib;
  }

protected:

    PhysAttributes attrib;
    Forces force;

    PhysicsObject() {}

<<<<<<< HEAD
    virtual void calcAccel() {
=======
    virtual void calcAccel(float deltaT) {
      // Update forces
>>>>>>> 0d723aba1af2c973d31adef636a00a16e2a3d6ee
      calcGravity();
      calcLift();
      calcDrag();

      // Update acceleration
      attrib.accel = (force.Flift + force.Fdrag - force.Fg) / attrib.mass;
      std::cout << "accel: x: " << attrib.accel[0] << ", y: " << attrib.accel[1] << ", z: " << attrib.accel[2] << std::endl;
      std::cout << "lift: x: " << force.Flift[0] << ", y: " << force.Flift[1] << ", z: " << force.Flift[2] << std::endl;
      std::cout << "drag: x: " << force.Fdrag[0] << ", y: " << force.Fdrag[1] << ", z: " << force.Fdrag[2] << std::endl;
      std::cout << "gravity: x: " << force.Fg[0] << ", y: " << force.Fg[1] << ", z: " << force.Fg[2] << std::endl;
    }

    virtual void calcGravity() {
      force.Fg = glm::vec3(0.0f, (attrib.mass * GRAVITY_ACCEL_S), 0.0f);
    }

    virtual void calcDrag() {
      force.Fdrag = glm::vec3(0.0f);
      calcDragY();
      calcDragX();
    }

    virtual void calcDragX() {
      float drag = attrib.Cd * attrib.rho * attrib.velocity[0] * attrib.velocity[0] * attrib.area * .5;
      if (attrib.velocity[0] > 0){
        drag = -drag;
      }

      // Give drag vector an x value
      force.Fdrag += glm::vec3(drag, 0.0f, 0.0f);
    }

    // Calculates drag in y direction
    virtual void calcDragY() {
      float drag = attrib.Cd * attrib.rho * attrib.velocity[1] * attrib.velocity[1] * attrib.area * .5;
      
      // If the velocity in the y direction is position, change the drag scalar to negative
      if (attrib.velocity[1] > 0){
        drag = -drag;
      }

      // Give drag vector a y value
      force.Fdrag += glm::vec3(0.0f, drag, 0.0f);
    }

    // Look at dragonfly.h to find implementation
    virtual void calcLift(){}

    virtual void calcVelocity(float deltaT) {
      // Get change in velocity with accel * change in time then add to previous velocity
      attrib.velocity += deltaT * attrib.accel;

      // Velocity side to side is cancelled if the dragonfly is on the ground
      if(attrib.pos.y == 0){
        attrib.velocity.x = 0;
      }
      std::cout << "velocity: x: " << attrib.velocity[0] << ", y: " << attrib.velocity[1] << ", z: " << attrib.velocity[2] << std::endl;
    }

    // Returns change in position
    virtual glm::vec3 calcPos(float deltaT) {
      // Get change in position with velocity * change in time then add to previous position
      glm::vec3 deltaP = deltaT * attrib.velocity;
      attrib.pos += deltaP;

      // Set the y position, y velocity, and y change in position to zero if the dragonfly goes below zero
      if (attrib.pos[1] < 0.0f) {
        attrib.pos[1] = 0.0f;
        attrib.velocity[1] = 0.0f;
        deltaP[1] = 0.0f;
      }

      std::cout << "position: x: " << attrib.pos[0] << ", y: " << attrib.pos[1] << ", z: " << attrib.pos[2] << std::endl;
      std::cout << "change in position: x: " << deltaP[0] << ", y: " << deltaP[1] << ", z: " << attrib.pos[2] << std::endl;
      
      return deltaP;
    }

    // Returns change in position to that can be used for graphical translation
    glm::vec3 physUpdate(float deltaT) {
      calcAccel();
      calcVelocity(deltaT);
      return calcPos(deltaT);
    }

    // return total surface area of body and wings. Not used
    virtual float getSurfaceArea() = 0;
    
    // Returns the surface area that faces -y when not rotated. Not used
    virtual float getBottomSurfaceArea() = 0;

    // returns body mass. Not used
    virtual float getBodyMass() = 0;

};
