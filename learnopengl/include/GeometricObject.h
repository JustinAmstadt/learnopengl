#ifndef GEOMETRIC_OBJECT_H
#define GEOMETRIC_OBJECT_H

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glad/glad.h> 
#include <string>
#include "Tragectory.h"
#include "Mesh.h"

struct Material {
	glm::vec3 ambient = glm::vec3(1.0f, 0.5f, 0.31f);
	glm::vec3 diffuse = glm::vec3(1.0f, 0.5f, .031f);
	glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f);
	float shininess = 32.0f;
};

class GeometricObject {
private:
	std::string textureFileName;
	std::vector<Vertex> vertexData;
	std::vector<GLuint> indices;
protected:
	Mesh mesh;
	std::string objName = "";
public:
	std::unique_ptr<Tragectory> tragectory = std::make_unique<Tragectory>();
	GLuint texture = -1;
	Material material;
	bool meshCreated;

	GeometricObject(std::string name);
	GeometricObject(std::string name, std::vector<glm::vec3> vertices);
	GeometricObject(std::string name, std::vector<glm::vec3> vertices, std::vector<GLuint> indices);
	GeometricObject(std::string name, Mesh mesh);

	// Keep this legacy code for the dragonfly scene
	GeometricObject(std::string name, std::vector<glm::vec3> vertices, float vecInLineDist);

	~GeometricObject() { tragectory.reset(); }

	void setColor(glm::vec4 color);
	bool setNormals(std::vector<glm::vec3>& normal);
	void setColorVec(std::vector<glm::vec4>& colorVec, glm::vec4 defaultColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	bool setTextures(std::vector<glm::vec2>& texCoords, std::string fileName);
	bool setMaterials(Material m);
	void createMesh();

	Mesh& getMesh();
};
#endif
