#include <memory>
#include "GeometricObject.h"
#include <iostream>

GeometricObject::GeometricObject(std::vector<glm::vec3> vertices) 
{
	for (int i = 0; i < vertices.size(); i++) {
		Vertex v;
		v.position = vertices[i];
		vertexData.push_back(v);
	}
}

void GeometricObject::setColor(glm::vec4 color)
{
	for (Vertex& v : vertexData) {
		v.color = color;
	}
}

bool GeometricObject::setNormals(std::vector<glm::vec3>& normal)
{
	if (normal.size() == 0) {
		std::cout << "Normal size is zero\n";
		return false;
	}
	else if (normal.size() != vertexData.size()) {
		std::cerr << "ERROR: Normal vector has size " << normal.size() << " while Vertices vector has size  " << vertexData.size() << std::endl;
		return false;
	}
	else {
		for (int i = 0; i < vertexData.size(); i++) {
			vertexData[i].normal = normal[i];
		}
	}
}

void GeometricObject::setColorVec(std::vector<glm::vec4>& colorVec, glm::vec4 defaultColor)
{
	if (colorVec.size() == 0 && defaultColor == glm::vec4(-1.0f)) {
		for (int i = 0; i < vertexData.size(); i++) {
			colorVec.push_back(glm::vec4(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), 1.0f));
		}
	}
	else if (colorVec.size() == 0) {
		for (int i = 0; i < vertexData.size(); i++) {
			colorVec.push_back(defaultColor);
		}
	}

	if (vertexData.size() != colorVec.size()) {
		std::cerr << "ERROR: Position Vector has size " << vertexData.size() << " while Color Vector has size " << colorVec.size() << std::endl;

		if (vertexData.size() > colorVec.size()) {
			while (vertexData.size() != colorVec.size()) {
				colorVec.push_back(defaultColor);
			}
		}
		else {
			while (vertexData.size() != colorVec.size()) {
				colorVec.pop_back();
			}
		}
		std::cerr << "ERROR CORRECTED: Position Vector now has size " << vertexData.size() << " and Color Vector now has size " << colorVec.size() << std::endl;
	}

	for (int i = 0; i < vertexData.size(); i++) {
		vertexData[i].color = colorVec[i];
	}
}

bool GeometricObject::setTextures(std::vector<glm::vec2>& texCoords, std::string fileName)
{
	if (texCoords.size() == 0) {
		return false;
	}
	else if (vertexData.size() != texCoords.size()) {
		std::cerr << "ERROR: PostionVec size of " << vertexData.size() << " does not match texCoords size of " << texCoords.size() << std::endl;
		std::cerr << "Position vector size and texCoords vector size do not match. Not adding texture to Vertex vector" << std::endl;
		return false;
	}
	
	if (fileName.size() == 0) {
		std::cerr << "ERROR: texture file name is empty" << std::endl;
		textureFileName = "container.jpg";
	}
	else {
		textureFileName = fileName;
	}

	for (int i = 0; i < vertexData.size(); i++) {
		vertexData[i].texture = texCoords[i];
	}

	return true;
}

bool GeometricObject::setMaterials(Material m)
{
	material = m;
	return true;
}
