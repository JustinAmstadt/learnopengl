/*
make the grid move, but feel like you are moving over the grid
3D quadratic function with falling cubes

*/

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
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;


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

	srand((unsigned)time(NULL));

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
	scene->addObjectVec(ObjectData::graphLines);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glEnable(GL_DEPTH_TEST);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		scene->renderScene();
		ObjectData::updateData();

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
	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		scene->camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		scene->camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		scene->camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		scene->camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	scene->camera.ProcessMouseMovement(xoffset, yoffset);
}