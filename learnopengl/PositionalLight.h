#ifndef POSITIONALLIGHT_H
#define POSITIONALLIGHT_H

class PositionalLight : public Light {
public:
	PositionalLight(glm::vec3 position = glm::vec3(0.0f)) : Light() {
		this->lightPosDir = glm::vec4(position, 1.0f);

		setAttenConst(1.0f);
		setAttenLin(0.09f);
		setAttenQuad(0.032f);
	}

	virtual void setLightPosDir(glm::vec3 position) {
		this->lightPosDir = glm::vec4(position, 1.0f);
	}
};

#endif
