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
	GLuint cubeMap = -1;
protected:
	glm::vec4 clearColor = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);
public:
	std::shared_ptr<Light> light;
	static std::unordered_map<std::string, GLuint> textureMap;

	Scene() {
		projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
	}
	~Scene() {
		objectVec.clear();
	}

	static GLuint createVAO(std::vector<Vertex> data, std::vector<GLuint> indices = std::vector<GLuint>());

	void renderScene(Camera camera);
	void addObjectVec(std::vector<std::shared_ptr<SceneObject>> vector) {
		if(vector.size() > 0)
			objectVec.push_back(vector);
	}
	void addObject(std::shared_ptr<SceneObject> object) {
		objectVec.push_back(std::vector<std::shared_ptr<SceneObject>>{ object });
	}

	void addTexture(std::string fileName);

	void addCubeMap(std::vector<std::string> faces);

	virtual void update(Camera camera) = 0;
	virtual void makeCurrent() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};


#endif
