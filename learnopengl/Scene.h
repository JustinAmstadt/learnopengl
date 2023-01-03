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

struct Light {
	glm::vec3 lightPos = glm::vec3(0.0f);
	glm::vec3 lightColor = glm::vec3(1.0f);

	glm::vec3 ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	glm::vec3 diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
};

class Scene {
private:
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	Light light { glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f) };
	std::vector<std::vector<std::shared_ptr<SceneObject>>> objectVec;
	glm::mat4 projection;
public:
	Camera camera;
	std::unordered_map<std::string, GLuint> textureMap;

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
	void setLight(glm::vec3 lightPos, glm::vec3 lightColor) {
		light.lightPos = lightPos;
		light.lightColor = lightColor;

		light.diffuseColor = light.lightColor * light.diffuse;
		light.ambientColor = light.diffuseColor * light.ambient;
	}

	void addTexture(std::string fileName);
};
#endif
