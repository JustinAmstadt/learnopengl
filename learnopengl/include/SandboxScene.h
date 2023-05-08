#ifndef SANDBOXSCENE_H
#define SANDBOXSCENE_H


#include <glm/glm.hpp>
#include "Light.h"
#include "CircularParabola.h"
#include "PositionalLight.h"
#include "GridFloor.h"
#include "Dragonfly.h"
#include "Arrow.h"

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
  std::unique_ptr<Arrow> liftArrow;
  std::unique_ptr<Arrow> dragArrow;
  std::unique_ptr<Arrow> gravityArrow;

public:
	SandboxScene(std::shared_ptr<Shader> shaderProgram, std::shared_ptr<Shader> lampShader, std::shared_ptr<Shader> dragonflyShader) {
		cp = std::make_unique<CircularParabola>(lampShader);
		gridFloor = std::make_unique<GridFloor>(lampShader, 80);
    df = std::make_unique<Dragonfly>(dragonflyShader, lampShader, 60.0f, 30.0f, 60.0f, 30.0f);
    liftArrow = std::make_unique<Arrow>(lampShader);
    gravityArrow = std::make_unique<Arrow>(lampShader);
    dragArrow = std::make_unique<Arrow>(lampShader);

		this->light = std::make_shared<PositionalLight>();

    this->addObject(dragArrow->getObjPtr());
    this->addObject(liftArrow->getObjPtr());
    this->addObject(gravityArrow->getObjPtr());
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

    float liftScalar = std::sqrt(df->getForces().Flift[0] * df->getForces().Flift[0] + df->getForces().Flift[1] * df->getForces().Flift[1]);
    float liftTheta = 90.0f;

    if(df->getForces().Flift[0] != 0){
      liftTheta = glm::degrees(std::atan(df->getForces().Flift[1] / df->getForces().Flift[0]));
    }

    if(liftTheta < 0){
      float distTo90 = 90.0f - std::abs(liftTheta);
      liftTheta = 90 + distTo90;
    }

    std::cout << "lift theta: " << liftTheta << std::endl;

    this->liftArrow->update(df->getAttrib().pos, glm::vec3(liftScalar, liftScalar / 2.0f, 1.0f), liftTheta);

    float gravityScalar = std::sqrt(df->getForces().Fg[1] * df->getForces().Fg[1]);
    this->gravityArrow->update(df->getAttrib().pos, glm::vec3(gravityScalar, gravityScalar / 2.0f, 1.0f), 270.0f);

    float dragScalar = std::sqrt(df->getForces().Fdrag[0] * df->getForces().Fdrag[0] + df->getForces().Fdrag[1] * df->getForces().Fdrag[1]);
    float dragTheta = 90.0f;

    if(df->getForces().Fdrag[0] != 0){
      dragTheta = glm::degrees(std::atan(df->getForces().Fdrag[1] / df->getForces().Fdrag[0]));
    }

    if(dragTheta < 0){
      float distTo90 = 90.0f - std::abs(dragTheta);
      dragTheta = 90 + distTo90;
    }

    if(df->getForces().Fdrag.y < 0){
      dragTheta = -dragTheta;
    }
    std::cout << "drag theta: " << dragTheta << ", drag scalar: " << dragScalar << std::endl;

    this->dragArrow->update(df->getAttrib().pos, glm::vec3(dragScalar, dragScalar / 2.0f, 1.0f), dragTheta);
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

  virtual void pressUp() override {
    df->incWingSpeed();
  }
  virtual void pressDown() override {
    df->decWingSpeed();
  }

  virtual void pressR() override {
    df->goLeft();
  }
  virtual void pressF() override {
    df->goRight();
  }

};
#endif
