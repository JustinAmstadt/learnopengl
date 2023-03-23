#include <glm/gtc/matrix_transform.hpp>

struct PhysAttributes {
  glm::vec3 velocity;
  glm::vec3 accel;
  glm::vec3 pos;
  float weight;
  float mass;

  const float GRAVITY_ACCEL = 9.81f;

};
