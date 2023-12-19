#ifndef SANDBOXSCENE_H
#define SANDBOXSCENE_H


#include <glm/glm.hpp>
#include "Light.h"
#include "DirectionalLight.h"
#include "CircularParabola.h"
#include "PositionalLight.h"
#include "GridFloor.h"
#include "Dragonfly.h"
#include "Square.h"
#include "Arrow.h"

#include <numbers>
#include <math.h>

class SandboxScene : public Scene {
private:
	// std::unique_ptr<CircularParabola> cp;
	std::unique_ptr<GridFloor> gridFloor;
	std::vector<std::shared_ptr<SceneObject>> lights;
	std::vector<std::shared_ptr<SceneObject>> cubes;
	glm::vec3 lightPos = glm::vec3(0.0f, 1.0f, 0.0f);

public:
	SandboxScene(const int screenWidth, const int screenHeight, std::shared_ptr<Shader> shaderProgram, std::shared_ptr<Shader> lampShader) : Scene(screenWidth, screenHeight)
	{
		// cp = std::make_unique<CircularParabola>(lampShader);
		gridFloor = std::make_unique<GridFloor>(lampShader, 80);

		this->light = std::make_shared<DirectionalLight>();
		this->light->setLightColor(glm::vec3(1.0f));

		// this->addObjectVec(gridFloor->getFloorLines());
		//this->addObjectVec(cp->getFallingCubes());
		//this->addObjectVec(cp->getGraphLines());
		createGeometry(shaderProgram, lampShader);

		this->addTexture("container.jpg");
		this->addTexture("container2.png");
		this->addTexture("container2_specular.png");
		this->addTexture("lighting_maps_specular_color.png");
		this->addTexture("matrix.jpg");
		this->addTexture("colorful.jpg");
	}

	virtual void update(Camera camera) override {
		// this->light->setLightPosDir(lightPos);
		this->renderScene(camera);
		updateGeometry(camera);
<<<<<<< HEAD
=======
    this->df->update(getDeltaT());

    // Formula to get scalar of a vector with from the x and y components
    float liftScalar = std::sqrt(df->getForces().Flift[0] * df->getForces().Flift[0] + df->getForces().Flift[1] * df->getForces().Flift[1]);
    float liftTheta = 90.0f;

    // Formula to get angle of a vector with from the x and y components. If x is zero, the angle is already set to 90 degrees
    if(df->getForces().Flift[0] != 0){
      liftTheta = glm::degrees(std::atan(df->getForces().Flift[1] / df->getForces().Flift[0]));
    }

    // Correct the angle if below zero
    if(liftTheta < 0){
      float distTo90 = 90.0f - std::abs(liftTheta);
      liftTheta = 90 + distTo90;
    }

    std::cout << "lift theta: " << liftTheta << ", lift scalar " << liftScalar << std::endl;

    // Update the arrow position, scale, and rotation
    this->liftArrow->update(df->getAttrib().pos, glm::vec3(liftScalar, liftScalar / 2.0f, 1.0f), liftTheta);

    // Formula to get scalar of a vector with from the x and y components
    float gravityScalar = std::sqrt(df->getForces().Fg[1] * df->getForces().Fg[1]);
    // Update the arrow position, scale, and rotation
    this->gravityArrow->update(df->getAttrib().pos, glm::vec3(gravityScalar, gravityScalar / 2.0f, 1.0f), 270.0f);

    // Formula to get scalar of a vector with from the x and y components
    float dragScalar = std::sqrt(df->getForces().Fdrag[0] * df->getForces().Fdrag[0] + df->getForces().Fdrag[1] * df->getForces().Fdrag[1]);
    float dragTheta = -90.0f;

    // Formula to get angle of a vector with from the x and y components. If x is zero, the angle is already set to 90 degrees
    if(df->getForces().Fdrag[0] != 0){
      dragTheta = glm::degrees(std::atan(df->getForces().Fdrag[1] / df->getForces().Fdrag[0]));
    }

    // Correct the angle if below zero
    if(df->getForces().Fdrag.x < 0){
      dragTheta += 180.0;
    }

    std::cout << "drag theta: " << dragTheta << ", drag scalar: " << dragScalar << std::endl;

    // Update the arrow position, scale, and rotation
    this->dragArrow->update(df->getAttrib().pos, glm::vec3(dragScalar, dragScalar / 2.0f, 1.0f), dragTheta);

    std::cout << "\n\n";
>>>>>>> 0d723aba1af2c973d31adef636a00a16e2a3d6ee
	}

	void createGeometry(std::shared_ptr<Shader> shaderProgram, std::shared_ptr<Shader> lampShader)
	{
		//cube
		Material material{ glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, .031f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f };
		// std::shared_ptr<GeometricObject> cube = std::make_shared<Cube>("container2.png", material);
		std::shared_ptr<GeometricObject> cube = std::make_shared<Cube>();
		glm::mat4 model;
		std::shared_ptr<SceneObject> list = std::make_shared<SceneObject>();
		std::shared_ptr<Square> square = std::make_shared<Square>("container2.png");

		for (float i = 0; i < 2; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, i * 6));
			model = glm::scale(model, glm::vec3(3.0f));
			std::shared_ptr<SceneObject> list = std::make_shared<SceneObject>();
			*list = { cube, model, shaderProgram, GL_TRIANGLES};
			cubes.push_back(list);
		}
		// this->addObjectVec(cubes);

		list.reset(new SceneObject());
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(100.0f));
		*list = { square, model, shaderProgram, GL_TRIANGLES};
		this->addObject(list);

		// Smaller cube
		list.reset(new SceneObject());
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		*list = { cube, model, lampShader, GL_TRIANGLES};
		//this->addObject(list);

		// Light cube
		model = glm::mat4(1.0f);
		list.reset(new SceneObject());
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.5f));
		*list = { cube, model, lampShader, GL_TRIANGLES };
		lights.push_back(list);
		// this->addObjectVec(lights);
	}

	void updateGeometry(Camera camera)
	{
		// cp->update();
		gridFloor->updateFloor(camera);

		for (auto obj : cubes) {
			//obj->model = glm::rotate(obj->model, glm::radians(2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		}

		lights[0]->model = glm::rotate(lights[0]->model, glm::radians(1.0f), glm::vec3(0.0f, 1.0f,0.0f));
		lights[0]->model = glm::translate(lights[0]->model, glm::vec3(0.10f, 0.0f, 0.0f));
		lightPos = lights[0]->model * glm::vec4(1.0f);
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
		static_cast<void>(shaderID);
	}
};
#endif
