#ifndef FLATPLANE_H
#define FLATPLANE_H

#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Square.h"
#include "Scene.h"

class FlatPlane {
public:
	int size;
	float scale = 12.0;
	float offset;
	float height;
	std::vector<glm::vec3> vertices;
	std::vector<GLuint> indices;
	std::shared_ptr<GeometricObject> plane;
	std::shared_ptr<SceneObject> list;

	FlatPlane(std::shared_ptr<Shader> shaderProgram, int size, float height) {
		this->size = size;
		this->height = height;
		makeVertices(shaderProgram);
	}

	void makeVertices(std::shared_ptr<Shader> shaderProgram) {
		std::vector<glm::vec2> texCoords;
		std::vector<glm::vec3> normals;
		Square square;
		list = std::make_shared<SceneObject>();
		glm::mat4 model(1.0f);
		glm::mat4 scaleMat(1.0f);
		model = glm::mat4(1.0f);
		scaleMat = glm::scale(scaleMat, glm::vec3(scale));

		offset = scale * (float)-size / (float)2.0;

		for (int i = 0; i < size; ++i) {
			model = glm::translate(model, glm::vec3(i * scale + offset, 0, offset));
			for (int j = 0; j < size; ++j) {
				model = glm::translate(model, glm::vec3(0, 0, scale));
				for (const glm::vec3& vert : square.vertices) {
					vertices.push_back(model * scaleMat * glm::vec4(vert.x, 0.0f, vert.y, 1.0f));
					normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
				}
				texCoords.insert(texCoords.end(), square.texCoords.begin(), square.texCoords.end());
			}
			model = glm::mat4(1.0f);
		}

		plane = std::make_shared<GeometricObject>(vertices);

		/*for (const auto& v : vertices) {
			std::cout << v.x << ", " << v.y << ", " << v.z << std::endl;
		}*/

		plane->setTextures(texCoords, "CartoonWave.png");
		plane->setColor(glm::vec4(1.0f));
		plane->setNormals(normals);
		makeIndices();

		*list = { plane, Scene::createVAO(plane->vertexData, plane->indices), glm::mat4(1.0f), shaderProgram, GL_PATCHES };
	}

	

	void makeIndices() {
		Square square;
		for (int i = 0; i < size * size; ++i) {
			for (const GLuint& ind : square.indices)
				indices.push_back(ind + 4 * i);
		}

		plane->indices = indices;
	}
};

#endif