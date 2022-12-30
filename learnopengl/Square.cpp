#include "Square.h"

Square::Square(glm::vec3 color)
	: GeometricObject(std::vector <glm::vec3> {
	glm::vec3(0.5f, 0.5f, 0.0f),  // top right
		glm::vec3(0.5f, -0.5f, 0.0f),  // bottom right
		glm::vec3(-0.5f, -0.5f, 0.0f),  // bottom left
		glm::vec3(-0.5f, 0.5f, 0.0f)}, color)
{
	indices = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
	};
}