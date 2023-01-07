#ifndef RAIN_H
#define RAIN_H

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "GeometricObject.h"
#include "Scene.h"

class Rain {
private:
	glm::mat4 generateResetMatrix() {
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(
			((float)rand() / (float)RAND_MAX) * 60.0f + -30.0f, 
			((float)rand() / RAND_MAX) * 5.0 + maxHeight - 3.0f,
			((float)rand() / ((float)RAND_MAX) * 60.0f + -30.0f)));
		return model;
	}
public:
	int dropCount = 300;
	float dropLength = 0.8f;
	float fallSpeed = -1.0f;
	float maxHeight = 20.0f;
	float minHeight = -2.0f;
	std::vector <std::shared_ptr<SceneObject>> rainVec;

	Rain(std::shared_ptr<Shader> shaderProgram) {
		std::shared_ptr<GeometricObject> line = std::make_shared<GeometricObject>(
			std::vector<glm::vec3> { glm::vec3(0.0f, -dropLength / 2.0f, 0.0f), glm::vec3(0.0f, dropLength / 2.0f, 0.0f) });
		line->setColor(glm::vec4(34.0f / 255.0f, 25.0f / 255.0f, 255.0f / 255.0f, 0.0f));
		std::shared_ptr<SceneObject> list;
		GLuint VAO = Scene::createVAO(line->vertexData);

		for (int i = 0; i < dropCount; ++i) {

			list.reset(new SceneObject());
			*list = { line, VAO, generateResetMatrix(), shaderProgram, GL_LINES };
			rainVec.push_back(list);
		}
		
	}

	void updateRain() {
		for (int i = 0; i < rainVec.size(); ++i) {
			if (rainVec[i]->model[3][1] <= minHeight) { //[3][1] represents the y value for height
				rainVec[i]->model = generateResetMatrix();
			}
			else {
				rainVec[i]->model = glm::translate(rainVec[i]->model, glm::vec3(0.0f, fallSpeed, 0.0f));
			}
		}
	}

};

#endif