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
public:
	std::vector<std::vector<std::shared_ptr<SceneObject>>> objectVec;

	Camera camera;
	glm::mat4 projection;

	Scene();
	~Scene();

	static GLuint createVAO(std::vector<Vertex> data, std::vector<GLuint> indices = std::vector<GLuint>());

	void renderScene();
	void addObjectVec(std::vector<std::shared_ptr<SceneObject>> vector);
};
#endif
