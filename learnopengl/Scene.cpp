#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Scene.h"
#include "GeometricObject.h"

Scene::Scene()
{
	projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
	camera = Camera();
}

Scene::~Scene()
{
	objectVec.clear();
}

GLuint Scene::createVAO(std::vector<Vertex> data, std::vector<GLuint> indices)
{
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//bind the vertex array. this can store multiple vertex buffer objects
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), &data[0].position, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); //position
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(data[0].position)); //color
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vertex) - sizeof(data[0].texture))); //texture

	GLuint EBO;
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbinds the vertex buffer
	glBindVertexArray(0); //unbinds the vertex array

	return VAO;
}

void Scene::renderScene()
{
	glUseProgram(objectVec[0][0]->program->ID);

	for (int i = 0; i < objectVec.size(); i++) {
		for (int j = 0; j < objectVec[i].size(); j++) {
			glBindVertexArray(objectVec[i][j]->VAO);
			glUniformMatrix4fv(glGetUniformLocation(objectVec[i][j]->program->ID, "model"), 1, GL_FALSE, glm::value_ptr(objectVec[i][j]->model));
			glUniformMatrix4fv(glGetUniformLocation(objectVec[i][j]->program->ID, "view"), 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));
			glUniformMatrix4fv(glGetUniformLocation(objectVec[i][j]->program->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

			if (objectVec[i][j]->object->indices.size() == 0) {
				glDrawArrays(objectVec[i][j]->DRAW_ENUM, 0, objectVec[i][j]->object->vertexData.size());
			}
			else {
				glDrawElements(objectVec[i][j]->DRAW_ENUM, objectVec[i][j]->object->indices.size(), GL_UNSIGNED_INT, 0);
			}
		}
	}
}

void Scene::addObjectVec(std::vector<std::shared_ptr<SceneObject>> vector)
{
	objectVec.push_back(vector);
}