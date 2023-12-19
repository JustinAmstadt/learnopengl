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
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "FlatPlane.h"
#include "GeometricObject.h"
#include "Shader.h"
#include "Scene.h"
#include "CircularParabola.h"
#include "ObjectData.h"
#include "GridFloor.h"
#include "PositionalLight.h"
#include "Bot.h"
#include "DirectionalLight.h"
#include "Skybox.h"
#include "Rain.h"
#include "OceanScene.h"
#include "SandboxScene.h"
#include "TessellationPlaneScene.h"
#include "MazeScene.h"
#include "Dragonfly.h"
#include "DragonflyScene.h"
#include "Model.h"

#define POSITION_ATTRIB 0;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void loop();
void processInput(GLFWwindow* window);
void createSphere(int radius, int sectorCount, int stackCount, std::vector<glm::vec3>& vertices, std::vector<GLuint>& indices);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void createGeometry();
void updateGeometry();

int screenWidth;
int screenHeight;
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
std::shared_ptr<Scene> sandbox;
std::shared_ptr<Scene> dragonfly;

float lastX;
float lastY;
bool firstMouse = true;

Camera camera(glm::vec3(0.0f, 0.0f, 8.0f));

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
	screenHeight = mode->height;
	screenWidth = mode->width;
	lastX = screenWidth / 2.0f;
	lastY = screenHeight / 2.0f;

	window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", NULL, NULL);
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

	glViewport(0, 0, screenWidth, screenHeight);
	
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
	// Model backpack = Model("models/backpack/backpack.obj");

	// std::shared_ptr<Scene> ocean = std::make_shared<OceanScene>(oceanShader, lampShader, skyboxShader);
	sandbox = std::make_shared<SandboxScene>(screenWidth, screenHeight, shaderProgram, lampShader);
	// dragonfly = std::make_shared<SandboxScene>(lampShader, dragonflyShader);
	// std::shared_ptr<Scene> tessellation = std::make_shared<TessellationPlaneScene>(tessShader);

	//maze = std::make_shared<MazeScene>(lampShader);

	sandbox->makeCurrent();
  
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		sandbox->update(camera);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	static_cast<void>(window);
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
  std::shared_ptr<SandboxScene> sandboxCast = std::dynamic_pointer_cast<SandboxScene>(sandbox);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
    mazeCast->moveBotUp();
    sandboxCast->pressUp();
	dragonfly->pressUp();
  }
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
    mazeCast->moveBotDown();
    sandboxCast->pressDown();
	dragonfly->pressDown();
  }
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    mazeCast->moveBotRight();
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    mazeCast->moveBotLeft();

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
	dragonfly->pressR();
  }
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS){
	dragonfly->pressF();
  }
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS){
    sandboxCast->pressT();
  }
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS){
    sandboxCast->pressG();
  }
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
	static_cast<void>(window);

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