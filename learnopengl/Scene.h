#ifndef SCENE_H
#define SCENE_H

#include <glm/glm.hpp>
#include <glad/glad.h> 
#include <vector>
#include <iostream>
#include <unordered_map>

#include "GeometricObject.h"
#include "Camera.h"
#include "Shader.h"

struct SceneObject {
	std::shared_ptr<GeometricObject> object;
	GLuint VAO;
	glm::mat4 model;
	std::shared_ptr<Shader> program;
	GLenum DRAW_ENUM;
};

class Scene {
private:
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	glm::vec3 lightPos = glm::vec3(0.0f);
	glm::vec3 lightColor = glm::vec3(1.0f);
	std::vector<std::vector<std::shared_ptr<SceneObject>>> objectVec;
	glm::mat4 projection;
public:
	Camera camera;

	Scene() {
		projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
		camera = Camera();
	}
	~Scene() {
		objectVec.clear();
	}

	static GLuint createVAO(std::vector<Vertex> data, std::vector<GLuint> indices = std::vector<GLuint>());

	void renderScene();
	void addObjectVec(std::vector<std::shared_ptr<SceneObject>> vector) {
		objectVec.push_back(vector);
	}
	void addObject(std::shared_ptr<SceneObject> object) {
		objectVec.push_back(std::vector<std::shared_ptr<SceneObject>>{ object });
	}
	void setLight(glm::vec3 lightPos, glm::vec4 lightColor) {
		this->lightPos = lightPos;
		this->lightColor = lightColor;
	}
};
#endif
