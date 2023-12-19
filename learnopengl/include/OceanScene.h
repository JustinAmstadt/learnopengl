#ifndef OCEANSCENE_H
#define OCEANSCENE_H

#include "Scene.h"

class OceanScene : public Scene {
private:
	std::unique_ptr<Rain> rain;
	std::unique_ptr<Skybox> skybox;
	std::unique_ptr<FlatPlane> fp;
public:
	OceanScene(const float screenWidth, const float screenHeight, std::shared_ptr<Shader> oceanShader, std::shared_ptr<Shader> rainShader, std::shared_ptr<Shader> skyboxShader) : Scene(screenWidth, screenHeight) 
	{
		rain = std::make_unique<Rain>(rainShader);
		skybox = std::make_unique<Skybox>(skyboxShader);
		fp = std::make_unique<FlatPlane>(oceanShader, 20, 0.0);

		this->light = std::make_shared<DirectionalLight>();
		this->addObject(skybox->list);
		this->addObjectVec(rain->rainVec);
		this->addObject(fp->list);

		this->addTexture("CartoonWave.png");
	}

	virtual void update(Camera camera) {
		this->renderScene(camera);
		rain->updateRain();
	}

	virtual void makeCurrent() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->textureMap["CartoonWave.png"]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, this->textureMap["CartoonWave.png"]);
	}

	virtual void additionalUniformCalls(GLuint shaderID) {
		glUniform1f(glGetUniformLocation(shaderID, "time"), (float)glfwGetTime());
	}
};

#endif