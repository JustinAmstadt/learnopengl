#include "GeometricObject.h"
#include <iostream>

GeometricObject::GeometricObject(std::vector<glm::vec3> vertices, glm::vec4 defaultColor) 
	: GeometricObject(vertices, std::vector<glm::vec4>(), std::vector<glm::vec3>(), Material(), defaultColor) {}

GeometricObject::GeometricObject(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normal, glm::vec4 defaultColor)
	: GeometricObject(vertices, std::vector<glm::vec4>(), normal, material, defaultColor){}

GeometricObject::GeometricObject(std::vector<glm::vec3> vertices, std::vector<glm::vec4> colorVec, std::vector<glm::vec3> normal, Material material, glm::vec4 defaultColor)
	: GeometricObject(vertices, colorVec, normal, material, std::vector<glm::vec2>{}, std::string(), defaultColor) {}

GeometricObject::GeometricObject(std::vector<glm::vec3> vertices, std::vector<glm::vec2> texCoords, std::string fileName) : GeometricObject(vertices, std::vector<glm::vec3>(), Material(), texCoords, fileName){}

GeometricObject::GeometricObject(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normal, Material material, std::vector<glm::vec2> texCoords, std::string fileName)
{
	bool textureFlag = loadTextures(texCoords, fileName, vertices.size());
	bool normalFlag = loadNormals(normal, vertices.size());
	loadMaterials(material);

	for (int i = 0; i < vertices.size(); i++) {
		Vertex v;
		v.position = vertices[i];
		if (normalFlag)
			v.normal = normal[i];
		if(textureFlag)
			v.texture = texCoords[i];
		vertexData.push_back(v);
	}
}

GeometricObject::GeometricObject(std::vector<glm::vec3> vertices, std::vector<glm::vec4> colorVec, std::vector<glm::vec3> normal, Material material, std::vector<glm::vec2> texCoords, std::string fileName, glm::vec4 defaultColor)
{
	loadColors(colorVec, defaultColor, vertices.size());
	bool textureFlag = loadTextures(texCoords, fileName, vertices.size());
	bool normalFlag = loadNormals(normal, vertices.size());
	bool materialFlag = loadMaterials(material);

	for (int i = 0; i < vertices.size(); i++) {
		Vertex v;
		v.position = vertices[i];
		v.color = colorVec[i];
		if (normalFlag)
			v.normal = normal[i];
		if (textureFlag)
			vertexData[i].texture = texCoords[i];
		vertexData.push_back(v);
	}
}

void GeometricObject::changeColor(glm::vec4 color)
{
	for (Vertex& v : vertexData) {
		v.color = color;
	}
}

bool GeometricObject::loadNormals(std::vector<glm::vec3>& normal, std::size_t vertSize)
{
	if (normal.size() == 0) {
		std::cout << "Normal size is zero\n";
		return false;
	}
	else if (normal.size() != vertSize) {
		std::cerr << "ERROR: Normal vector has size " << normal.size() << " while Vertices vector has size  " << vertSize << std::endl;
		return false;
	}
	else {
		return true;
	}
}

void GeometricObject::loadColors(std::vector<glm::vec4>& colorVec, glm::vec4 defaultColor, std::size_t vertSize)
{
	if (colorVec.size() == 0 && defaultColor == glm::vec4(-1.0f)) {
		for (int i = 0; i < vertSize; i++) {
			colorVec.push_back(glm::vec4(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), 1.0f));
		}
	}
	else if (colorVec.size() == 0) {
		for (int i = 0; i < vertSize; i++) {
			colorVec.push_back(defaultColor);
		}
	}

	if (vertSize != colorVec.size()) {
		std::cerr << "ERROR: Position Vector has size " << vertSize << " while Color Vector has size " << colorVec.size() << std::endl;

		if (vertSize > colorVec.size()) {
			while (vertSize != colorVec.size()) {
				colorVec.push_back(defaultColor);
			}
		}
		else {
			while (vertSize != colorVec.size()) {
				colorVec.pop_back();
			}
		}
		std::cerr << "ERROR CORRECTED: Position Vector now has size " << vertSize << " and Color Vector now has size " << colorVec.size() << std::endl;
	}
}

bool GeometricObject::loadTextures(std::vector<glm::vec2>& texCoords, std::string fileName, std::size_t vertSize)
{
	if (texCoords.size() == 0) {
		return false;
	}
	else if (vertSize != texCoords.size()) {
		std::cerr << "ERROR: PostionVec size of " << vertSize << " does not match texCoords size of " << texCoords.size() << std::endl;
		std::cerr << "Position vector size and texCoords vector size do not match. Not adding texture to Vertex vector" << std::endl;
		return false;
	}
	else if (fileName.size() == 0) {
		std::cerr << "ERROR: texture file name is empty" << std::endl;
		fileName = "container.jpg";
	}

	return true;
}

bool GeometricObject::loadMaterials(Material m)
{
	material = m;
	return true;
}
