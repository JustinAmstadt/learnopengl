#ifndef SQUARE_H
#define SQUARE_H
#include "GeometricObject.h"

class Square : public GeometricObject {
private:

public:
	std::vector<glm::vec2> texCoords = {
		glm::vec2(1.0f, 1.0f),  // lower-left corner  
		glm::vec2(1.0f, 0.0f),  // lower-right corner
		glm::vec2(0.0f, 0.0f),   // top-center corner
		glm::vec2(0.0f, 1.0f),
	};

	std::vector<glm::vec3> vertices{
		glm::vec3(0.5f, 0.5f, 0.0f),  // top right
		glm::vec3(0.5f, -0.5f, 0.0f),  // bottom right
		glm::vec3(-0.5f, -0.5f, 0.0f),  // bottom left
		glm::vec3(-0.5f, 0.5f, 0.0f)
	};

	//same name as parent class. be careful
	std::vector<GLfloat> indices{
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	Square() : Square("") {}

	Square(std::string fileName)
		: GeometricObject(vertices)
	{
		this->indices = indices;

		setTextures(texCoords, fileName);
		setColor(glm::vec4(1.0f));
	}
};

#endif