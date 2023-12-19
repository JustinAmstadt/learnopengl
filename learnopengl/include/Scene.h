#ifndef SCENE_H
#define SCENE_H

#include <glm/glm.hpp>
#include <glad/glad.h> 
#include <vector>
#include <iostream>
#include <unordered_map>
#include <GLFW/glfw3.h>

#include "GeometricObject.h"
#include "Camera.h"
#include "Shader.h"
#include "Light.h"

struct SceneObject {
	std::shared_ptr<GeometricObject> object;
	glm::mat4 model = glm::mat4(1.0f);
	std::shared_ptr<Shader> shader = nullptr;
	GLenum DRAW_ENUM = GL_LINES;
};

class Scene {
private:
	std::vector<std::vector<std::shared_ptr<SceneObject>>> objectVec;
	glm::mat4 projection;
	GLuint cubeMap = -1;
	float prevTime = static_cast<float>(glfwGetTime());
	float curTime;
protected:
	glm::vec4 clearColor = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);
public:
	std::shared_ptr<Light> light;
	static std::unordered_map<std::string, GLuint> textureMap;

	Scene(const int screenWidth, const int screenHeight) {
		projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), (900.0f / 500.0f), 0.1f, 400.0f);
	}
	~Scene() {
		objectVec.clear();
	}

	static GLuint createVAO(std::vector<Vertex> data, std::vector<GLuint> indices);

	void renderScene(Camera camera);
	void addObjectVec(std::vector<std::shared_ptr<SceneObject>> vector) {
		if(vector.size() > 0)
			objectVec.push_back(vector);
    else {
      throw "Vector cannot be size 0";
    }
	}
	void addObject(std::shared_ptr<SceneObject> object) {
    if(object != nullptr){
      objectVec.push_back(std::vector<std::shared_ptr<SceneObject>>{ object });
    }
    else{
      throw "object cannot be nullptr";
    }
	}

  float getDeltaT() {
    curTime = static_cast<float>(glfwGetTime());
    float deltaT = curTime - prevTime;
    prevTime = curTime;
    return deltaT;
  }

	static GLuint addTexture(std::string fileName);

	void addCubeMap(std::vector<std::string> faces);

	virtual void update(Camera camera) = 0;

  // Binds textures to what the scene requires
	virtual void makeCurrent() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

  virtual void additionalUniformCalls(GLuint shaderID) {
	static_cast<void>(shaderID); // Not used in parent class
  }

  virtual void pressUp() {}
  virtual void pressDown() {}
  virtual void pressLeft() {}
  virtual void pressRight() {}
  virtual void pressR() {}
  virtual void pressF() {}
  virtual void pressT() {}
  virtual void pressG() {}
  virtual void pressY() {}
  virtual void pressH() {}
  virtual void pressU() {}
  virtual void pressJ() {}
};


#endif
