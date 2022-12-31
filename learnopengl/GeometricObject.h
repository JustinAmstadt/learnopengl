#ifndef GEOMETRIC_OBJECT_H
#define GEOMETRIC_OBJECT_H

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h> 
#include <string>
#include "Tragectory.h"

struct Vertex {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 texture;
};

class GeometricObject {
public:
	std::vector<GLuint> indices;
	std::vector<Vertex> vertexData;
	GLuint texture = -1;
	Tragectory* tragectory = new Tragectory();

	GeometricObject(std::vector<glm::vec3> vertices, glm::vec4 defaultColor = glm::vec4(-1.0f));
	GeometricObject(std::vector<glm::vec3> vertices, std::vector<glm::vec4> colorVec, glm::vec4 defaultColor = glm::vec4(-1.0f));
	GeometricObject(std::vector<glm::vec3> vertices, std::vector<glm::vec2> texCoords, std::string fileName);
	GeometricObject(std::vector<glm::vec3> vertices, std::vector<glm::vec4> colorVec, std::vector<glm::vec2> texCoords, std::string fileName);

	~GeometricObject() { delete this->tragectory; }

	void changeColor(glm::vec4 color);
};
#endif
