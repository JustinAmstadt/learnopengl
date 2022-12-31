#ifndef GRIDFLOOR_H
#define GRIDFLOOR_H

#include <iostream>

#include "Camera.h"
#include "Shader.h"
#include "Scene.h"


class GridFloor {
private:
	std::vector<std::shared_ptr<SceneObject>> floorLines;
	float floorDistance = 4.0f;

	void createFloor(std::shared_ptr<Shader> shaderProgram, float size) {
		size -= (int)size % (int)floorDistance;

		std::cout << "size: " << size << std::endl;

		std::shared_ptr<SceneObject> list = std::make_shared<SceneObject>();
		glm::mat4 model = glm::mat4(1.0f);

		std::shared_ptr<GeometricObject> line = std::make_shared<GeometricObject>(std::vector<glm::vec3> { glm::vec3(0.0f, -2.0f, -size), glm::vec3(0.0f, -2.0f, size) },
			glm::vec4(0.0f, 0.8f, 0.0f, 1.0f));

		GLuint VAO = Scene::createVAO(line->vertexData);

		//vertical middle line
		*list = { line, VAO, model, shaderProgram, GL_LINES };
		floorLines.push_back(list);

		//vertical right side
		for (int i = 0; i < size / 4; i++) {
			list.reset(new SceneObject());
			model = glm::translate(model, glm::vec3(floorDistance, 0.0f, 0.0f));
			*list = { line, VAO, model, shaderProgram, GL_LINES };
			floorLines.push_back(list);
		}

		model = glm::mat4(1.0f);

		//vertical left side
		for (int i = 0; i < size / 4; i++) {
			list.reset(new SceneObject());
			model = glm::translate(model, glm::vec3(-floorDistance, 0.0f, 0.0f));
			*list = { line, VAO, model, shaderProgram, GL_LINES };
			floorLines.push_back(list);
		}

		list.reset(new SceneObject());
		model = glm::mat4(1.0f);

		//horizontal middle line
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		*list = { line, VAO, model, shaderProgram, GL_LINES };
		floorLines.push_back(list);

		for (int i = 0; i < size / floorDistance + 1; i++) {
			list.reset(new SceneObject());
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, (float)i * -floorDistance));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			*list = { line, VAO, model, shaderProgram, GL_LINES };
			floorLines.push_back(list);
		}

		for (int i = 0; i < size / floorDistance + 1; i++) {
			list.reset(new SceneObject());
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, (float)i * floorDistance));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			*list = { line, VAO, model, shaderProgram, GL_LINES };
			floorLines.push_back(list);
		}
	}
public:
	GridFloor(std::shared_ptr<Shader> shaderProgram, float size) {
		createFloor(shaderProgram, size);
	}

	~GridFloor() {
		floorLines.clear();
	}
	
	void updateFloor(const Camera& camera) {
		//std::cout << camera.Position[0] << ", " << camera.Position[1] << ", " << camera.Position[2] << std::endl;

		glm::mat4 model(1.0f);
		static float cameraOffsetX = 0.0f;
		static float cameraOffsetZ = 0.0f;

		model = glm::mat4(1.0f);

		//shifts the grid over by the distance between lines in the floor once the next line has been reached.
		//gives the illusion that you are running over the grid, but the grid is following you and you are flying
		//over the same square continuously
		if (camera.Position[0] >= cameraOffsetX + floorDistance) {
			cameraOffsetX += 4;
			model = glm::translate(model, glm::vec3(floorDistance, 0.0f, 0.0f));
			for (int i = 0; i < floorLines.size(); i++) {
				floorLines[i]->model = model * floorLines[i]->model;
			}
		}
		else if (camera.Position[0] < cameraOffsetX - floorDistance) {
			cameraOffsetX -= 4;
			model = glm::translate(model, glm::vec3(-floorDistance, 0.0f, 0.0f));
			for (int i = 0; i < floorLines.size(); i++) {
				floorLines[i]->model = model * floorLines[i]->model;
			}
		}

		if (camera.Position[2] >= cameraOffsetZ + floorDistance) {
			cameraOffsetZ += 4;
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, floorDistance));
			for (int i = 0; i < floorLines.size(); i++) {
				floorLines[i]->model = model * floorLines[i]->model;
			}
		}
		else if (camera.Position[2] < cameraOffsetZ - floorDistance) {
			cameraOffsetZ -= 4;
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, -floorDistance));
			for (int i = 0; i < floorLines.size(); i++) {
				floorLines[i]->model = model * floorLines[i]->model;
			}
		}
	}

	const std::vector<std::shared_ptr<SceneObject>>& getFloorLines() {
		return floorLines;
	}
};

#endif