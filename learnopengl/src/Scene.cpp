#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <GLFW/glfw3.h>

#include "Scene.h"
#include "GeometricObject.h"

#include <iostream>

std::unordered_map<std::string, GLuint> Scene::textureMap;

GLuint Scene::createVAO(std::vector<Vertex> data, std::vector<GLuint> indices)
{
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//bind the vertex array. this can store multiple vertex buffer objects
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), &data[0].position, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); //position
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(data[0].position)); //color
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(data[0].position) + sizeof(data[0].color))); //texture
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(data[0].position) + sizeof(data[0].color) + sizeof(data[0].texture))); //normal

  // for lines only!! checks 
  if(data[0].distFromStart > -1){
    std::cout << data[0].distFromStart;
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(data[0].position) + sizeof(data[0].color) + sizeof(data[0].texture) + sizeof(data[0].normal))); //distFromStart
  }

	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbinds the vertex buffer
	glBindVertexArray(0); //unbinds the vertex array

	return VAO;
}

void Scene::renderScene(Camera camera)
{
	for (auto i = 0u; i < objectVec.size(); i++) {
		for (auto j = 0u; j < objectVec[i].size(); j++) {
      
			std::shared_ptr<Shader> shader = objectVec[i][j]->shader;
			GLuint shaderID = shader->ID;

			// Empty function by default in the parent class
			additionalUniformCalls(shaderID);

			//lamp shader only
			glUniform3fv(glGetUniformLocation(shaderID, "lightColor"), 1, glm::value_ptr(light->getLightColor()));

			glUniform1i(glGetUniformLocation(shaderID, "material.diffuse"), 0);
			glUniform1i(glGetUniformLocation(shaderID, "material.specular"), 1);
			glUniform1i(glGetUniformLocation(shaderID, "emissionMap"), 2);

			glUniform3fv(glGetUniformLocation(shaderID, "viewPos"), 1, glm::value_ptr(camera.Position));

			glUniform1f(glGetUniformLocation(shaderID, "light.constant"), light->getAttenConst());
			glUniform1f(glGetUniformLocation(shaderID, "light.linear"), light->getAttenLin());
			glUniform1f(glGetUniformLocation(shaderID, "light.quadratic"), light->getAttenQuad());

			glUniform4fv(glGetUniformLocation(shaderID, "light.position"), 1, glm::value_ptr(light->getLightPosDir()));
			glUniform3fv(glGetUniformLocation(shaderID, "light.ambient"), 1, glm::value_ptr(light->getAmbientColor()));
			glUniform3fv(glGetUniformLocation(shaderID, "light.diffuse"), 1, glm::value_ptr(light->getDiffuseColor()));
			glUniform3fv(glGetUniformLocation(shaderID, "light.specular"), 1, glm::value_ptr(light->getSpecular()));
			glUniform1f(glGetUniformLocation(shaderID, "material.shininess"), objectVec[i][j]->object->material.shininess);

			glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, glm::value_ptr(objectVec[i][j]->model));
			glUniformMatrix4fv(glGetUniformLocation(shaderID, "view"), 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));
			glUniformMatrix4fv(glGetUniformLocation(shaderID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

			objectVec[i][j]->object->getMesh().Draw(shader, objectVec[i][j]->DRAW_ENUM);

			/*
			if (objectVec[i][j]->object->indices.size() == 0) {
				glDrawArrays(objectVec[i][j]->DRAW_ENUM, 0, objectVec[i][j]->object->vertexData.size());
			}
			else {
				// glPatchParameteri(GL_PATCH_VERTICES, 4);
				glDrawElements(objectVec[i][j]->DRAW_ENUM, objectVec[i][j]->object->indices.size(), GL_UNSIGNED_INT, 0);
			}*/
		}
	}
}

GLuint Scene::addTexture(std::string fileName) {
	return -1;

	/*
	int end = fileName.find(".");
	std::string fileExtension = fileName.substr(end);

	GLuint texture;
	glGenTextures(1, &texture);
	textureMap[fileName] = texture; //add texture to the hashmap
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;

	#ifdef __linux__
		fileName = "resources/" + fileName;
	#elif _WIN32
		fileName = "resources\\" + fileName;
	#elif __APPLE__
		fileName = "resources/" + fileName;
	#else
		std::cerr << "Could not determine which OS you are running. Textures will not load!" << std::endl;
	#endif

	unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		if(fileExtension == ".jpg")
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else if(fileExtension == ".png")
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	return texture;
*/
}

void Scene::addCubeMap(std::vector<std::string> faces)
{
	/*
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	cubeMap = textureID;
*/
}
