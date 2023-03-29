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

class PhysicsObject{

  public:

    constexpr static float GRAVITY_ACCEL_S = 9.81f;
    constexpr static float GRAVITY_ACCEL_MS = 0.00981f;

  protected:

    PhysAttributes attrib;

    PhysicsObject() {
    }

    virtual void calcAccel(float deltaT) {
      glm::vec3 change = glm::vec3(0.0f, deltaT * -GRAVITY_ACCEL_MS, 0.0f);
      attrib.accel + change;
    }

    virtual void calcVelocity(float deltaT) {
      attrib.velocity += deltaT * attrib.accel;
    }

    // Returns change in position
    virtual glm::vec3 calcPos(float deltaT) {
      glm::vec3 deltaP = deltaT * attrib.velocity;
      attrib.pos += deltaP;
      std::cout << deltaP[1] << std::endl;
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
