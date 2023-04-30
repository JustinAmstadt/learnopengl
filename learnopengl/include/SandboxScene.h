#ifndef SANDBOXSCENE_H
#define SANDBOXSCENE_H


#include <glm/glm.hpp>
#include "Light.h"
#include "CircularParabola.h"
#include "PositionalLight.h"
#include "GridFloor.h"
#include "Dragonfly.h"

#include <numbers>
#include <math.h>

class SandboxScene : public Scene {
private:
	std::unique_ptr<CircularParabola> cp;
	std::unique_ptr<GridFloor> gridFloor;
	std::vector<std::shared_ptr<SceneObject>> lights;
	std::vector<std::shared_ptr<SceneObject>> cubes;
	glm::vec3 lightPos = glm::vec3(0.0f, 2.0f, -3.0f);

  std::unique_ptr<Dragonfly> df;
public:
	SandboxScene(std::shared_ptr<Shader> shaderProgram, std::shared_ptr<Shader> lampShader, std::shared_ptr<Shader> dragonflyShader) {
		cp = std::make_unique<CircularParabola>(lampShader);
		gridFloor = std::make_unique<GridFloor>(lampShader, 80);
    df = std::make_unique<Dragonfly>(dragonflyShader, lampShader, 60.0f, 30.0f, 60.0f, 30.0f);

		this->light = std::make_shared<PositionalLight>();

    this->addObjectVec(df->getWings());
    this->addObject(df->getBody());
		this->addObjectVec(gridFloor->getFloorLines());
		//this->addObjectVec(cp->getFallingCubes());
		//this->addObjectVec(cp->getGraphLines());
		// createGeometry(shaderProgram, lampShader);

		this->addTexture("container.jpg");
		this->addTexture("container2.png");
		this->addTexture("container2_specular.png");
		this->addTexture("lighting_maps_specular_color.png");
		this->addTexture("matrix.jpg");
		this->addTexture("colorful.jpg");
	}

	virtual void update(Camera camera) override {
		this->light->setLightPosDir(lightPos);
		this->light->setLightColor(glm::vec3(1.0f, 0.0f, 1.0f));
		this->renderScene(camera);
		updateGeometry(camera);
    this->df->update(getDeltaT());
	}

	void createGeometry(std::shared_ptr<Shader> shaderProgram, std::shared_ptr<Shader> lampShader)
	{
		//cube
		Material material{ glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, .031f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f };
		std::shared_ptr<GeometricObject> cube = std::make_shared<Cube>("container2.png", material);
		glm::mat4 model;
		std::shared_ptr<SceneObject> list = std::make_shared<SceneObject>();
		GLuint cubeVAO = Scene::createVAO(cube->vertexData);

		for (float i = 0; i < 0; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 5.0f, i * 6));
			model = glm::scale(model, glm::vec3(3.0f));
			std::shared_ptr<SceneObject> list = std::make_shared<SceneObject>();
			*list = { cube, cubeVAO, model, shaderProgram, GL_TRIANGLES };
			cubes.push_back(list);
		}
		this->addObjectVec(cubes);

		//sphere
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		*list = { cube, cubeVAO, model, shaderProgram, GL_TRIANGLES };
		this->addObject(list);


		//light
		model = glm::mat4(1.0f);
		list.reset(new SceneObject());
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.5f));
		*list = { cube, Scene::createVAO(cube->vertexData), model, lampShader, GL_TRIANGLES };
		lights.push_back(list);
		this->addObjectVec(lights);
	}

	void updateGeometry(Camera camera)
	{
		cp->update();
		gridFloor->updateFloor(camera);

		for (auto obj : cubes) {
			//obj->model = glm::rotate(obj->model, glm::radians(2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		}

		/*lights[0]->model = glm::rotate(lights[0]->model, glm::radians(1.0f), glm::vec3(0.0f, 1.0f,0.0f));
		lights[0]->model = glm::translate(lights[0]->model, glm::vec3(0.10f, 0.0f, 0.0f));
		lightPos = lights[0]->model * glm::vec4(1.0f);*/
		//std::cout << lightPos.x << ", " << lightPos.y << ", " << lightPos.z << std::endl;
	}

	void makeCurrent() override {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->textureMap["container2.png"]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, this->textureMap["container2_specular.png"]);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, this->textureMap["matrix.jpg"]);
	}

  void additionalUniformCalls(GLuint shaderID) override {
    float speed = 10.0f;
    double currentTime = glfwGetTime();

    // By offsetting the sine wave appropriately, we can get the function to have a set high and low
    glUniform1f(glGetUniformLocation(shaderID, "leftWingAngle"), df->getLeftUniform());
    glUniform1f(glGetUniformLocation(shaderID, "rightWingAngle"), df->getRightUniform());

  }
};
#endif
