#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include <iostream>

class DirectionalLight : public Light {
public:
	DirectionalLight(glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f)) : Light() {
		this->lightPosDir = glm::vec4(direction, 0.0f);
	}

	virtual void setLightPosDir(glm::vec3 direction) {
		for (int i = 0; i < 3; i++) {
			if (direction[i] > 1.0f || direction[i] < -1.0f) {
				std::cerr << "Set a directional light above or below 1.0f: " << direction[i] << std::endl;
				return;
			}
		}

		this->lightPosDir = glm::vec4(direction, 0.0f);
	}

	virtual void setAttenConst(float val) {
		std::cerr << "Cannot set attenuation for a directional light" << std::endl;
	}

	virtual void setAttenLin(float val) {
		std::cerr << "Cannot set attenuation for a directional light" << std::endl;
	}

	virtual void setAttenQuad(float val) {
		std::cerr << "Cannot set attenuation for a directional light" << std::endl;
	}
};

#endif