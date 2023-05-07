#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

struct PhysAttributes {
  glm::vec3 velocity;
  glm::vec3 accel;
  glm::vec3 pos;
  float weight;
  float mass;
  float density;
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

protected:

    PhysAttributes attrib;
    Forces force;

    PhysicsObject() {}

    virtual void calcAccel(float deltaT) {
      calcGravity();
      calcLift(deltaT);
      calcDrag();

      // std::cout << "x: " << force.Fg[0] << ", y: " << force.Fg[1] << ", z: " << force.Fg[2] << std::endl;
      attrib.accel = (force.Flift + force.Fdrag - force.Fg) / attrib.mass;
      std::cout << "accel: x: " << attrib.accel[0] << ", y: " << attrib.accel[1] << ", z: " << attrib.accel[2] << std::endl;
      std::cout << "lift: x: " << force.Flift[0] << ", y: " << force.Flift[1] << ", z: " << force.Flift[2] << std::endl;
      std::cout << "drag: x: " << force.Fdrag[0] << ", y: " << force.Fdrag[1] << ", z: " << force.Fdrag[2] << std::endl;
      std::cout << "gravity: x: " << force.Fg[0] << ", y: " << force.Fg[1] << ", z: " << force.Fg[2] << std::endl;
    }

    virtual void calcGravity() {
      force.Fg = glm::vec3(0.0f, (attrib.mass * GRAVITY_ACCEL_S), 0.0f);
      // std::cout << "x: " << force.Fg[0] << ", y: " << force.Fg[1] << ", z: " << force.Fg[2] << std::endl;
    }

    virtual void calcDrag() {
      force.Fdrag = glm::vec3(0.0f);
      calcDragY();
      calcDragX();
    }

    virtual void calcDragX() {
      float area = 1;
      float Cd = .3;
      float rho = 1.225;
      float drag = Cd * rho * attrib.velocity[0] * attrib.velocity[0] * area * .5;
      if (attrib.velocity[0] > 0){
        drag = -drag;
      }
      std::cout << "drag: " << drag << std::endl;
      force.Fdrag += glm::vec3(drag, 0.0f, 0.0f);
    }

    virtual void calcDragY() {
      float area = 1;
      float Cd = .3;
      float rho = 1.225;
      float drag = Cd * rho * attrib.velocity[1] * attrib.velocity[1] * area * .5;
      if (attrib.velocity[1] > 0){
        drag = -drag;
      }
      force.Fdrag += glm::vec3(0.0f, drag, 0.0f);
    }

    virtual void calcLift(float deltaT){}

    virtual void calcVelocity(float deltaT) {
      attrib.velocity += deltaT * attrib.accel;
      std::cout << "velocity: x: " << attrib.velocity[0] << ", y: " << attrib.velocity[1] << ", z: " << attrib.velocity[2] << std::endl;
    }

    // Returns change in position
    virtual glm::vec3 calcPos(float deltaT) {
      glm::vec3 deltaP = deltaT * attrib.velocity;
      attrib.pos += deltaP;

      if (attrib.pos[1] < 0.0f) {
        attrib.pos[1] = 0.0f;
        attrib.velocity[1] = 0.0f;
        deltaP[1] = 0.0f;
      }

      std::cout << "x: " << attrib.pos[0] << ", y: " << attrib.pos[1] << ", z: " << attrib.pos[2] << std::endl;
      
      return deltaP;
    }

    // Returns change in position to that can be used for graphical translation
    glm::vec3 physUpdate(float deltaT) {
      calcAccel(deltaT);
      calcVelocity(deltaT);
      return calcPos(deltaT);
    }

    // return total surface area of body and wings. don't see a use though
    virtual float getSurfaceArea() = 0;
    
    // Returns the surface area that faces -y when not rotated
    virtual float getBottomSurfaceArea() = 0;

    // returns body mass
    virtual float getBodyMass() = 0;

};
