#ifndef DRAGONFLYSCENE_H
#define DRAONGFLYSCENE_H


#include <glm/glm.hpp>
#include "Light.h"
#include "CircularParabola.h"
#include "PositionalLight.h"
#include "GridFloor.h"
#include "Dragonfly.h"
#include "Arrow.h"

#include <numbers>
#include <math.h>

class DragonflyScene : public Scene {
private:
	std::unique_ptr<GridFloor> gridFloor;
	std::unique_ptr<Dragonfly> df;
	std::unique_ptr<Arrow> liftArrow;
	std::unique_ptr<Arrow> dragArrow;
	std::unique_ptr<Arrow> gravityArrow;

public:
	DragonflyScene(const float screenWidth, const float screenHeight, std::shared_ptr<Shader> lampShader, std::shared_ptr<Shader> dragonflyShader) : Scene(screenWidth, screenHeight)
	{
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
	}

	virtual void update(Camera camera) override {
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

		if(df->getForces().Fdrag.x < 0){
		dragTheta += 180.0;
		}

		std::cout << "drag theta: " << dragTheta << ", drag scalar: " << dragScalar << std::endl;

		this->dragArrow->update(df->getAttrib().pos, glm::vec3(dragScalar, dragScalar / 2.0f, 1.0f), dragTheta);
	}

	void updateGeometry(Camera camera)
	{
		gridFloor->updateFloor(camera);
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
