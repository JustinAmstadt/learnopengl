#ifndef GEOMETRIC_OBJECT_H
#define GEOMETRIC_OBJECT_H

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h> 
#include <string>

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texture;
};

class GeometricObject {
public:
	std::vector<GLuint> indices;
	std::vector<Vertex> vertexData;
	GLuint texture = -1;

	GeometricObject(std::vector<glm::vec3> vertices, glm::vec3 defaultColor = glm::vec3(1.0f, 0.0f, 0.0f));
	GeometricObject(std::vector<glm::vec3> vertices, std::vector<glm::vec3> colorVec, glm::vec3 defaultColor = glm::vec3(1.0f, 0.0f, 0.0f));
	GeometricObject(std::vector<glm::vec3> vertices, std::vector<glm::vec2> texCoords, std::string fileName);
	GeometricObject(std::vector<glm::vec3> vertices, std::vector<glm::vec3> colorVec, std::vector<glm::vec2> texCoords, std::string fileName);

	void changeColor(glm::vec3 color);
};
#endif
