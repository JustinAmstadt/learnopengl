#ifndef FLATPLANE_H
#define FLATPLANE_H

#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Square.h"
#include "Scene.h"
#include "GeometricObject.h"

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
				for (const Vertex& vert : square.getMesh().vertices) {
					vertices.push_back(model * scaleMat * glm::vec4(vert.position.x, 0.0f, vert.position.y, 1.0f));
					normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
				}
				texCoords.insert(texCoords.end(), square.texCoords.begin(), square.texCoords.end());
			}
			model = glm::mat4(1.0f);
		}

		plane = std::make_shared<GeometricObject>("FlatPlane Line", vertices);

		/*for (const auto& v : vertices) {
			std::cout << v.x << ", " << v.y << ", " << v.z << std::endl;
		}*/

		plane->setTextures(texCoords, "CartoonWave.png");
		plane->setColor(glm::vec4(1.0f));
		plane->setNormals(normals);
		makeIndices();

		*list = { plane, glm::mat4(1.0f), shaderProgram, GL_PATCHES };
	}

	void makeIndices() {
		Square square;
		for (int i = 0; i < size * size; ++i) {
			for (const GLfloat& ind : square.getMesh().indices)
				indices.push_back(ind + 4 * i);
		}

		plane->getMesh().indices = indices;
	}
};

#endif

/*private RawModel generateTerrain(Loader loader){
		int count = VERTEX_COUNT * VERTEX_COUNT;
		float[] vertices = new float[count * 3];
		float[] normals = new float[count * 3];
		float[] textureCoords = new float[count*2];
		int[] indices = new int[6*(VERTEX_COUNT-1)*(VERTEX_COUNT-1)];
		int vertexPointer = 0;
		for(int i=0;i<VERTEX_COUNT;i++){
			for(int j=0;j<VERTEX_COUNT;j++){
				vertices[vertexPointer*3] = (float)j/((float)VERTEX_COUNT - 1) * SIZE;
				vertices[vertexPointer*3+1] = 0;
				vertices[vertexPointer*3+2] = (float)i/((float)VERTEX_COUNT - 1) * SIZE;
				normals[vertexPointer*3] = 0;
				normals[vertexPointer*3+1] = 1;
				normals[vertexPointer*3+2] = 0;
				textureCoords[vertexPointer*2] = (float)j/((float)VERTEX_COUNT - 1);
				textureCoords[vertexPointer*2+1] = (float)i/((float)VERTEX_COUNT - 1);
				vertexPointer++;
			}
		}
		int pointer = 0;
		for(int gz=0;gz<VERTEX_COUNT-1;gz++){
			for(int gx=0;gx<VERTEX_COUNT-1;gx++){
				int topLeft = (gz*VERTEX_COUNT)+gx;
				int topRight = topLeft + 1;
				int bottomLeft = ((gz+1)*VERTEX_COUNT)+gx;
				int bottomRight = bottomLeft + 1;
				indices[pointer++] = topLeft;
				indices[pointer++] = bottomLeft;
				indices[pointer++] = topRight;
				indices[pointer++] = topRight;
				indices[pointer++] = bottomLeft;
				indices[pointer++] = bottomRight;
			}
		}
		return loader.loadToVAO(vertices, textureCoords, normals, indices);
	}*/