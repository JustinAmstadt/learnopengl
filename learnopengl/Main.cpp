#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/spline.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Shader.h"

#define POSITION_ATTRIB 0;

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texture;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void loop();
void processInput(GLFWwindow* window);
std::vector<Vertex> vec3ToVertex(std::vector<glm::vec3> positionVec, glm::vec3 defaultColor);
std::vector<Vertex> vec3ToVertex(std::vector<glm::vec3> positionVec, std::vector<glm::vec3> colorVec);
std::vector<Vertex> vec3ToVertex(std::vector<glm::vec3> positionVec, std::vector<glm::vec2> texCoords, std::string fileName);
std::vector<Vertex> vec3ToVertex(std::vector<glm::vec3> positionVec, std::vector<glm::vec3> colorVec, std::vector<glm::vec2> texCoords, std::string fileName);
GLuint createVAO(std::vector<Vertex> data);
GLuint createVAO(std::vector<Vertex> data, std::vector<GLuint> indices);
glm::mat4 multiplyMatrix(glm::mat4 matrix);

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
GLFWwindow* window;
std::string vertexShaderSource;
std::string fragShaderSource;
Shader* shaderProgram;
GLuint texture;

std::vector<glm::vec3> vertices {
	glm::vec3(0.5f,  0.5f, 0.0f),  // top right
	glm::vec3(0.5f, -0.5f, 0.0f),  // bottom right
	glm::vec3(-0.5f, -0.5f, 0.0f),  // bottom left
	glm::vec3(-0.5f,  0.5f, 0.0f),   // top left
	
	//glm::vec3(0.0f, 1.0f, 0.0f),	// center
	//glm::vec3(-1.0f, -1.0f, 0.0f),	// bottom right
	//glm::vec3(1.0f, -1.0f, 0.0f),	// bottom left
};

std::vector<glm::vec3> colors{
	glm::vec3(0.0f, 0.0f, 1.0f),
	glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.5f, 0.5f, 0.5f),
	glm::vec3(0.0f, 0.0f, 1.0f),
	glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.5f, 0.5f, 0.5f),
};

std::vector<GLuint> indices {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};

std::vector<glm::vec2> texCoords{
	glm::vec2(1.0f, 1.0f),  // lower-left corner  
	glm::vec2(1.0f, 0.0f),  // lower-right corner
	glm::vec2(0.0f, 0.0f),   // top-center corner
	glm::vec2(0.0f, 1.0f),
};

std::vector<glm::vec3> linepts;

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //specifies the function to use when window gets resized

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	shaderProgram = new Shader("vert.vert", "frag.frag");

	// Define four control points
	glm::vec3 p0(-1.0f, -1.0f, 0.0f);
	glm::vec3 p1(0.0f, 1.0f, 0.0f);
	glm::vec3 p2(1.0f, -1.0f, 0.0f);
	glm::vec3 p3(2.0f, 1.0f, 0.0f);

	// Evaluate the curve at t = 0.5
	float t = -1;
	int i = 0;
	for (i; i < 20; i++) {
		glm::vec3 p = glm::catmullRom(p0, p1, p2, p3, t);
		linepts.push_back(p);
		//std::cout << "Point on curve at t = " << t << ": " << glm::to_string(p) << std::endl;
		t += .1f;
	}

	linepts.clear();

	for (double i = -5; i < 5; i = i + .1) {
		if(sin(i) != 0)
			linepts.push_back(glm::vec3(cos(i), sin(i), 0.0f));
	}

	loop();

	glfwTerminate();
	return 0;
}

std::vector<Vertex> vec3ToVertex(std::vector<glm::vec3> positionVec, glm::vec3 defaultColor = glm::vec3(1.0f, 0.0f, 0.0f)) {
	std::vector<glm::vec3> colorVec;
	for (int i = 0; i < positionVec.size(); i++) {
		colorVec.push_back(defaultColor);
	}

	std::vector<Vertex> newVec = vec3ToVertex(positionVec, colorVec);

	return newVec;
}

std::vector<Vertex> vec3ToVertex(std::vector<glm::vec3> positionVec, std::vector<glm::vec3> colorVec) {
	if (positionVec.size() != colorVec.size()) {
		std::cerr << "ERROR: Position Vector has size " << positionVec.size() << " while Color Vector has size " << colorVec.size() << std::endl;

		if (positionVec.size() > colorVec.size()) {
			while (positionVec.size() != colorVec.size()) {
				colorVec.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			}
		}
		else {
			while (positionVec.size() != colorVec.size()) {
				colorVec.pop_back();
			}
		}
		std::cerr << "ERROR CORRECTED: Position Vector now has size " << positionVec.size() << " and Color Vector now has size " << colorVec.size() << std::endl;
	}

	
	
	std::vector<Vertex> newVec;
	for (int i = 0; i < positionVec.size(); i++) {
		Vertex v;
		v.position = positionVec[i];
		v.color = colorVec[i];
		newVec.push_back(v);
	}

	newVec[0].texture = glm::vec2(-1.0f, -1.0f);

	return newVec;
}

std::vector<Vertex> vec3ToVertex(std::vector<glm::vec3> positionVec, std::vector<glm::vec3> colorVec, std::vector<glm::vec2> texCoords, std::string fileName) {
	std::vector<Vertex> newVec = vec3ToVertex(positionVec, colorVec);

	if (positionVec.size() != texCoords.size()) {
		std::cerr << "ERROR: PostionVec size of " << positionVec.size() << " does not match texCoords size of " << texCoords.size() << std::endl;
		std::cerr << "Position vector size and texCoords vector size do not match. Not adding texture to Vertex vector" << std::endl;
		return newVec;
	}

	for (int i = 0; i < positionVec.size(); i++) {
		newVec[i].texture = texCoords[i];
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

	return newVec;
}

std::vector<Vertex> vec3ToVertex(std::vector<glm::vec3> positionVec, std::vector<glm::vec2> texCoords, std::string fileName) {
	std::vector<glm::vec3> colorVec;
	std::vector<Vertex> newVec = vec3ToVertex(positionVec, colorVec, texCoords, fileName);

	return newVec;
}

GLuint createVAO(std::vector<Vertex> data) {
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//bind the vertex array. this can store multiple vertex buffer objects
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), &data[0].position, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(data[0].position));

	if (data[0].texture != glm::vec2(-1.0f, -1.0f)) {
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vertex) - sizeof(data[0].texture)));
	}

	//glBindBuffer(GL_ARRAY_BUFFER, 0); //unbinds the vertex buffer
	glBindVertexArray(0); //unbinds the vertex array

	return VAO;
}

GLuint createVAO(std::vector<Vertex> data, std::vector<GLuint> indices) {
	GLuint VAO = createVAO(data);
	GLuint EBO;
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);

	return VAO;
}

void loop() {
	GLuint VAOTriangle = createVAO(vec3ToVertex(vertices, colors), indices);
	GLuint VAOCircleCenter = createVAO(vec3ToVertex(linepts, glm::vec3(1.0f, 1.0f, 0.0f)));
	GLuint VAOCircle1 = createVAO(vec3ToVertex(linepts, glm::vec3(0.0f, 1.0f, 0.0f)));
	GLuint VAOCircle2 = createVAO(vec3ToVertex(linepts, glm::vec3(0.0f, 1.0f, 1.0f)));

	while (!glfwWindowShouldClose(window))
	{

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glUseProgram(shaderProgram->ID);

		glm::mat4 model(1.0f);
		model = glm::rotate(model, 4.0f * (float)sin(glfwGetTime()), glm::vec3(0.0, 0.0, 1.0));
		model = glm::translate(model, glm::vec3(0.8f, 0.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

		glBindVertexArray(VAOCircle1);
		glDrawArrays(GL_TRIANGLE_FAN, 0, linepts.size());

		model = glm::mat4(1.0);
		//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
		//model = glm::translate(model, glm::vec3(0.8f, 0.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

		glBindVertexArray(VAOCircleCenter);
		glDrawArrays(GL_TRIANGLE_FAN, 0, linepts.size());

		model = glm::mat4(1.0);
		model = glm::rotate(model, (float)glfwGetTime() * 1.7f, glm::vec3(0.0, 0.0, 1.0));
		model = glm::translate(model, glm::vec3(0.4f, 0.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

		glBindVertexArray(VAOCircle2);
		glDrawArrays(GL_TRIANGLE_FAN, 0, linepts.size());

		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAOTriangle);
		//glDrawArrays(GL_LINE_LOOP, 0, vertices.size());
		//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

glm::mat4 multiplyMatrix(glm::mat4 matrix) {
	matrix = glm::rotate(matrix, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
	matrix = glm::translate(matrix, glm::vec3(0.8f, 0.0f, 0.0));
	matrix = glm::scale(matrix, glm::vec3(0.1, 0.1, 0.1));

	return matrix;
}