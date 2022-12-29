#include "GeometricObject.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

GeometricObject::GeometricObject(std::vector<glm::vec3> vertices, glm::vec3 defaultColor) : GeometricObject(vertices, std::vector<glm::vec3>(), defaultColor){}

GeometricObject::GeometricObject(std::vector<glm::vec3> vertices, std::vector<glm::vec3> colorVec, glm::vec3 defaultColor)
{
	if (colorVec.size() == 0) {
		for (int i = 0; i < vertices.size(); i++) {
			colorVec.push_back(glm::vec3(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)));
			//colorVec.push_back(defaultColor);
		}
	}

	if (vertices.size() != colorVec.size()) {
		std::cerr << "ERROR: Position Vector has size " << vertices.size() << " while Color Vector has size " << colorVec.size() << std::endl;

		if (vertices.size() > colorVec.size()) {
			while (vertices.size() != colorVec.size()) {
				colorVec.push_back(defaultColor);
			}
		}
		else {
			while (vertices.size() != colorVec.size()) {
				colorVec.pop_back();
			}
		}
		std::cerr << "ERROR CORRECTED: Position Vector now has size " << vertices.size() << " and Color Vector now has size " << colorVec.size() << std::endl;
	}

	for (int i = 0; i < vertices.size(); i++) {
		Vertex v;
		v.position = vertices[i];
		v.color = colorVec[i];
		vertexData.push_back(v);
	}
}

GeometricObject::GeometricObject(std::vector<glm::vec3> vertices, std::vector<glm::vec2> texCoords, std::string fileName) : GeometricObject(vertices, std::vector<glm::vec3>(), texCoords, fileName){}

GeometricObject::GeometricObject(std::vector<glm::vec3> vertices, std::vector<glm::vec3> colorVec, std::vector<glm::vec2> texCoords, std::string fileName) : GeometricObject(vertices, colorVec)
{
	if (vertices.size() != texCoords.size()) {
		std::cerr << "ERROR: PostionVec size of " << vertices.size() << " does not match texCoords size of " << texCoords.size() << std::endl;
		std::cerr << "Position vector size and texCoords vector size do not match. Not adding texture to Vertex vector" << std::endl;
		return;
	}

	for (int i = 0; i < vertices.size(); i++) {
		vertexData[i].texture = texCoords[i];
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	fileName = "resources\\" + fileName;
	unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void GeometricObject::changeColor(glm::vec3 color)
{
	for (Vertex& v : vertexData) {
		v.color = color;
	}
}
