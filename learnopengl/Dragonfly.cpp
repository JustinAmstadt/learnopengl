
#include "include/Dragonfly.h"

void Dragonfly::makeWingPtr(std::vector<glm::vec3> wingPts, std::shared_ptr<Shader> wingShader){
  std::shared_ptr<GeometricObject> rightLine = std::make_shared<GeometricObject>(wingPts, wingDistance);
  rightLine->setColor(glm::vec4(0.970f, 0.291f, 0.476f, 1.0f));
  GLuint rightVAO = Scene::createVAO(rightLine->vertexData);
  std::shared_ptr<SceneObject> list = std::make_shared<SceneObject>();

  // top right
  glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(wingXOffset, 0.0f, 0.0f));
  *list = { rightLine, rightVAO, model, wingShader, GL_TRIANGLE_STRIP };
  wingptr.push_back(list);

  // bottom right
  model = glm::translate(model, glm::vec3(0.0f, 0.0f, wingWidth + wingGap));
  list = std::make_shared<SceneObject>();
  *list = { rightLine, rightVAO, model, wingShader, GL_TRIANGLE_STRIP };
  wingptr.push_back(list);

  std::for_each(wingPts.begin(), wingPts.end(), [](glm::vec3& vec) { vec.x = -vec.x; }); // marking the left side with a negative x. will fix in shader
  std::shared_ptr<GeometricObject> leftLine = std::make_shared<GeometricObject>(wingPts, wingDistance);
  leftLine->setColor(glm::vec4(0.970f, 0.291f, 0.476f, 1.0f));
  GLuint leftVAO = Scene::createVAO(leftLine->vertexData);

  // top left
  model = glm::mat4(1.0f);
  glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(wingXOffset, 0.0f, -2.0f * wingWidth - wingGap)); // negative z here because we are are rotating 180 degress around y axis. z becomes flipped
  glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // We rotate here so that the endpoints continue to be endpoints on the other side
  model = rotate * translate;
  list = std::make_shared<SceneObject>();
  *list = { leftLine, leftVAO, model, wingShader, GL_TRIANGLE_STRIP };
  wingptr.push_back(list);
  
  // bottom left
  model = glm::translate(model, glm::vec3(0.0f, 0.0f, wingWidth + wingGap));
  list = std::make_shared<SceneObject>();
  *list = { leftLine, leftVAO, model, wingShader, GL_TRIANGLE_STRIP };
  wingptr.push_back(list);
}
