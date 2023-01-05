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
#include "Light.h"

struct SceneObject {
	std::shared_ptr<GeometricObject> object;
	GLuint VAO = -1;
	glm::mat4 model = glm::mat4(1.0f);
	std::shared_ptr<Shader> program = nullptr;
	GLenum DRAW_ENUM = GL_LINES;
};

class Scene {
private:
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	std::vector<std::vector<std::shared_ptr<SceneObject>>> objectVec;
	glm::mat4 projection;
public:
	std::shared_ptr<Light> light;
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


	void addTexture(std::string fileName);
};
#endif
