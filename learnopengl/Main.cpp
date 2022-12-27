#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/spline.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <vector>

#include "Shader.h"
#include "Scene.h"
#include "GeometricObject.h"
#include "ObjectData.h"

#define POSITION_ATTRIB 0;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void loop();
void processInput(GLFWwindow* window);
void createSphere(int radius, int sectorCount, int stackCount, std::vector<glm::vec3>& vertices, std::vector<GLuint>& indices);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
GLFWwindow* window;
std::string vertexShaderSource;
std::string fragShaderSource;
Shader* shaderProgram;
std::unique_ptr<Scene> scene(new Scene);


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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	shaderProgram = new Shader("vert.vert", "frag.frag");

	loop();

	glfwTerminate();
	return 0;
}

void loop() {
	ObjectData::createData(shaderProgram);
	//scene->addObjectVec(ObjectData::basicGeometryVec);
	scene->addObjectVec(ObjectData::floorLines);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glEnable(GL_DEPTH_TEST);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		scene->renderScene();
		ObjectData::updateData();
		scene->camera.update();

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
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	
	const float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		scene->camera.cameraPos += cameraSpeed * scene->camera.cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		scene->camera.cameraPos -= cameraSpeed * scene->camera.cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		scene->camera.cameraPos -= glm::normalize(glm::cross(scene->camera.cameraFront, scene->camera.cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		scene->camera.cameraPos += glm::normalize(glm::cross(scene->camera.cameraFront, scene->camera.cameraUp)) * cameraSpeed;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	//scene->camera.mouseUpdate(xpos, ypos);
}