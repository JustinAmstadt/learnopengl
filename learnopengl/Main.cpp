/*

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
#include <memory>

#include "include/FlatPlane.h"
#include "include/GeometricObject.h"
#include "include/Shader.h"
#include "include/Scene.h"
#include "include/CircularParabola.h"
#include "include/ObjectData.h"
#include "include/GridFloor.h"
#include "include/PositionalLight.h"
#include "include/Bot.h"
#include "include/DirectionalLight.h"
#include "include/Skybox.h"
#include "include/Rain.h"
#include "include/OceanScene.h"
#include "include/SandboxScene.h"
#include "include/TessellationPlaneScene.h"
#include "include/MazeScene.h"
#include "include/Dragonfly.h"

#define POSITION_ATTRIB 0;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void loop();
void processInput(GLFWwindow* window);
void createSphere(int radius, int sectorCount, int stackCount, std::vector<glm::vec3>& vertices, std::vector<GLuint>& indices);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void createGeometry();
void updateGeometry();

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
GLFWwindow* window;
std::string vertexShaderSource;
std::string fragShaderSource;
std::shared_ptr<Shader> shaderProgram;
std::shared_ptr<Shader> lampShader;
std::shared_ptr<Shader> oceanShader;
std::shared_ptr<Shader> skyboxShader;
std::shared_ptr<Shader> tessShader;
std::shared_ptr<Shader> hyperbolic;
std::shared_ptr<Shader> dragonflyShader;

std::shared_ptr<Scene> maze;

float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;

Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));


int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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
	
	shaderProgram = std::make_shared<Shader>("vert.vert", "frag.frag", nullptr, nullptr);
	lampShader = std::make_shared<Shader>("lamp.vert", "lamp.frag", nullptr, nullptr);
	oceanShader = std::make_shared<Shader>("ocean.vert", "ocean.frag", nullptr, nullptr);
	skyboxShader = std::make_shared<Shader>("skybox.vert", "skybox.frag", nullptr, nullptr);
	// tessShader = std::make_shared<Shader>("lamp.vert", "lamp.frag", "tess.tese", "tess.tesc");
	hyperbolic = std::make_shared<Shader>("hyperbolic.vert", "hyperbolic.frag", nullptr, nullptr);
  dragonflyShader = std::make_shared<Shader>("dragonfly.vert", "lamp.frag", nullptr, nullptr);

	loop();

	glfwTerminate();
	return 0;
}

void loop() {
	// std::shared_ptr<Scene> ocean = std::make_shared<OceanScene>(oceanShader, lampShader, skyboxShader);
	std::shared_ptr<Scene> sandbox = std::make_shared<SandboxScene>(shaderProgram, lampShader, dragonflyShader);
	// std::shared_ptr<Scene> tessellation = std::make_shared<TessellationPlaneScene>(tessShader);

  maze = std::make_shared<MazeScene>(lampShader);

	sandbox->makeCurrent();
  
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		sandbox->update(camera);

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
	float currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);

  std::shared_ptr<MazeScene> mazeCast = std::dynamic_pointer_cast<MazeScene>(maze);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    mazeCast->moveBotUp();
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    mazeCast->moveBotDown();
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    mazeCast->moveBotRight();
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    mazeCast->moveBotLeft();
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

	camera.ProcessMouseMovement(xoffset, yoffset);
}




