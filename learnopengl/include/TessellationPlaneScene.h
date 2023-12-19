#ifndef TESSELLATIONPLANESCENE_H
#define TESSELLATIONPLANESCENE_H

#include "Scene.h"
#include "Shader.h"
#include "FlatPlane.h"

class TessellationPlaneScene : public Scene {
private:
	std::unique_ptr<FlatPlane> fp;

public:
	TessellationPlaneScene(const float screenWidth, const float screenHeight, std::shared_ptr<Shader> lampShader) : Scene(screenWidth, screenHeight)
	{
		fp = std::make_unique<FlatPlane>(lampShader, 20, 0.0);

		this->addObject(fp->list);
		this->light = std::make_shared<DirectionalLight>();
	}

	void update(Camera camera) {
		this->renderScene(camera);
	}
};

#endif