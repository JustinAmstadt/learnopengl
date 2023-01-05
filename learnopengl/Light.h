#ifndef LIGHT_H
#define LIGHT_H

class Light {
private:
	//attenuation
	float constant;
	float linear;
	float quadratic;
protected:
	glm::vec4 lightPosDir = glm::vec4(0.0f);
	glm::vec3 lightColor = glm::vec3(1.0f);

	glm::vec3 ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	glm::vec3 diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::vec3 ambientColor = glm::vec3(0.0f);
	glm::vec3 diffuseColor = glm::vec3(0.0f);
public:
	Light() : Light(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f)) {}
	Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 lightColor) {
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		this->lightColor = lightColor;

		diffuseColor = lightColor * this->diffuse;
		ambientColor = diffuseColor * this->ambient;

		constant = -1.0f;
		linear = -1.0f;
		quadratic = -1.0f;
	}

	//either position or direction
	virtual void setLightPosDir(glm::vec3) = 0;
	
	virtual void setAttenConst(float val) {
		constant = val;
	}

	virtual void setAttenLin(float val) {
		linear = val;
	}

	virtual void setAttenQuad(float val) {
		quadratic = val;
	}

	float getAttenConst() {
		return constant;
	}

	float getAttenLin() {
		return linear;
	}

	float getAttenQuad() {
		return quadratic;
	}

	void setLightColor(glm::vec3 color) {
		this->lightColor = color;
	}

	glm::vec3 getAmbientColor() {
		return ambientColor;
	}

	glm::vec3 getDiffuseColor() {
		return diffuseColor;
	}

	glm::vec3 getSpecular() {
		return specular;
	}

	glm::vec4 getLightPosDir() {
		return lightPosDir;
	}

	glm::vec3 getLightColor() {
		return lightColor;
	}
};

#endif