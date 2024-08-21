#ifndef SQUARE_H
#define SQUARE_H
#include "GeometricObject.h"
#include "Mesh.h"

class Square : public GeometricObject {
private:

public:
	std::vector<glm::vec2> texCoords = {
		glm::vec2(8.0f, 8.0f),  // lower-left corner  
		glm::vec2(8.0f, 0.0f),  // lower-right corner
		glm::vec2(0.0f, 0.0f),   // top-center corner
		glm::vec2(0.0f, 8.0f),
	};

	std::vector<GLuint> squareIndices{
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	Square() : GeometricObject(
		"Square",
		std::vector<glm::vec3> {
			glm::vec3(0.5f, 0.5f, 0.0f),  // top right
			glm::vec3(0.5f, -0.5f, 0.0f),  // bottom right
			glm::vec3(-0.5f, -0.5f, 0.0f),  // bottom left
			glm::vec3(-0.5f, 0.5f, 0.0f)
		}
	)
	{
		mesh.indices = squareIndices;
		setColor(glm::vec4(255.0f, 0.0f, 0.0f, 1.0f));
		createMesh();
		objName = "Square";
	}

	// fileName: Texture file name 
	Square(std::string fileName) : GeometricObject(
		"Square",
		std::vector<glm::vec3> {
			glm::vec3(0.5f, 0.5f, 0.0f),  // top right
			glm::vec3(0.5f, -0.5f, 0.0f),  // bottom right
			glm::vec3(-0.5f, -0.5f, 0.0f),  // bottom left
			glm::vec3(-0.5f, 0.5f, 0.0f)
		}
	)
	{
		mesh.indices = squareIndices;
		setTextures(texCoords, fileName);
		setColor(glm::vec4(1.0f));
		createMesh();
		objName = "Square";
	}
};
#endif