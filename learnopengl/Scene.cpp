#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <GLFW/glfw3.h>

#include "Scene.h"
#include "GeometricObject.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); //position
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(data[0].position)); //color
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(data[0].position) + sizeof(data[0].color))); //texture
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(data[0].position) + sizeof(data[0].color) + +sizeof(data[0].texture))); //normal

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
	for (int i = 0; i < objectVec.size(); i++) {
		glUseProgram(objectVec[i][0]->program->ID);
		for (int j = 0; j < objectVec[i].size(); j++) {
			glBindVertexArray(objectVec[i][j]->VAO);
			

			//std::cout << objectVec[i][j]->object->material.ambient.x << std::endl;
			//std::cout << camera.Position.x << ", " << camera.Position.y << ", " << camera.Position.z << std::endl;

			glUniform3fv(glGetUniformLocation(objectVec[i][j]->program->ID, "viewPos"), 1, glm::value_ptr(camera.Position));
			glUniform3fv(glGetUniformLocation(objectVec[i][j]->program->ID, "light.position"), 1, glm::value_ptr(lightPos));
			glUniform3fv(glGetUniformLocation(objectVec[i][j]->program->ID, "light.color"), 1, glm::value_ptr(lightColor));
			glUniform3fv(glGetUniformLocation(objectVec[i][j]->program->ID, "light.ambient"), 1, glm::value_ptr(light.ambient));
			glUniform3fv(glGetUniformLocation(objectVec[i][j]->program->ID, "light.diffuse"), 1, glm::value_ptr(light.diffuse));
			glUniform3fv(glGetUniformLocation(objectVec[i][j]->program->ID, "light.specular"), 1, glm::value_ptr(light.specular));
			glUniform3fv(glGetUniformLocation(objectVec[i][j]->program->ID, "material.ambient"), 1, glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.31f)));
			glUniform3fv(glGetUniformLocation(objectVec[i][j]->program->ID, "material.diffuse"), 1, glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.31f)));
			glUniform3fv(glGetUniformLocation(objectVec[i][j]->program->ID, "material.specular"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
			glUniform1f(glGetUniformLocation(objectVec[i][j]->program->ID, "material.shininess"), objectVec[i][j]->object->material.shininess);
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

void Scene::addTexture(std::string fileName) {
	GLuint texture;
	glGenTextures(1, &texture);
	textureMap[fileName] = texture;
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