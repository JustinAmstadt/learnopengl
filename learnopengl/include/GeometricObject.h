#ifndef GEOMETRIC_OBJECT_H
#define GEOMETRIC_OBJECT_H

#include <vector>
#include <memory>
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
private:
	std::string textureFileName;
public:
	std::vector<GLuint> indices;
	std::vector<Vertex> vertexData;
	std::unique_ptr<Tragectory> tragectory = std::make_unique<Tragectory>();
	GLuint texture = -1;
	Material material;

	GeometricObject(std::vector<glm::vec3> vertices);
  
  GeometricObject(std::array<glm::vec3, 2> vertices);
	~GeometricObject() { tragectory.reset(); }

	void setColor(glm::vec4 color);
	bool setNormals(std::vector<glm::vec3>& normal);
	void setColorVec(std::vector<glm::vec4>& colorVec, glm::vec4 defaultColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	bool setTextures(std::vector<glm::vec2>& texCoords, std::string fileName);
	bool setMaterials(Material m);
};
#endif
