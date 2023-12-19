#ifndef SKYBOX_H
#define SKYBOX_H

#include "Shader.h"
#include "GeometricObject.h"
#include "Scene.h"
#include "Cube.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>


class Skybox {
public:
	std::shared_ptr<SceneObject> list;

	Skybox(std::shared_ptr<Shader> shaderProgram) {
		std::shared_ptr<GeometricObject> cube = std::make_shared<Cube>(glm::vec4(0.4f, 0.4f, 0.4f, 1.0f));
		list = std::make_shared<SceneObject>();

		glm::mat4 scale(1.0f);
		scale = glm::scale(scale, glm::vec3(200.0f));

		// *list = { cube, scale, shaderProgram, GL_TRIANGLES };
	}
};

#endif