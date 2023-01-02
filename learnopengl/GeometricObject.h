#ifndef GEOMETRIC_OBJECT_H
#define GEOMETRIC_OBJECT_H

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h> 
#include <string>
#include "Tragectory.h"

struct Material {
	glm::vec3 ambient = glm::vec3(1.0f, 0.5f, 0.31f);
	glm::vec3 diffuse = glm::vec3(1.0f, 0.5f, .031f);
	glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f);
	float shininess = 32.0f;
};

struct Vertex {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 texture;
	glm::vec3 normal;
};

class GeometricObject {
public:
	std::vector<GLuint> indices;
	std::vector<Vertex> vertexData;
	Tragectory* tragectory = new Tragectory();
	GLuint texture = -1;
	Material material = { glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, .031f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f };

	GeometricObject(std::vector<glm::vec3> vertices, glm::vec4 defaultColor = glm::vec4(-1.0f));
	GeometricObject(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normal, glm::vec4 defaultColor = glm::vec4(-1.0f));
	GeometricObject(std::vector<glm::vec3> vertices, std::vector<glm::vec4> colorVec, std::vector<glm::vec3> normal, Material material, glm::vec4 defaultColor = glm::vec4(-1.0f));
	GeometricObject(std::vector<glm::vec3> vertices, std::vector<glm::vec2> texCoords, std::string fileName);
	GeometricObject(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normal, Material material, std::vector<glm::vec2> texCoords, std::string fileName);
	GeometricObject(std::vector<glm::vec3> vertices, std::vector<glm::vec4> colorVec = std::vector<glm::vec4>{}, std::vector<glm::vec3> normal = std::vector<glm::vec3>{}, Material material = Material(), std::vector<glm::vec2> texCoords = std::vector<glm::vec2>{}, std::string fileName = std::string(), glm::vec4 defaultColor = glm::vec4(-1.0f));

	~GeometricObject() { delete this->tragectory; }

	void changeColor(glm::vec4 color);
	bool loadNormals(std::vector<glm::vec3>& normal, std::size_t vertSize);
	void loadColors(std::vector<glm::vec4>& colorVec, glm::vec4 defaultColor, std::size_t vertSize);
	bool loadTextures(std::vector<glm::vec2>& texCoords, std::string fileName, std::size_t vertSize);
	bool loadMaterials(Material m);
};
#endif
