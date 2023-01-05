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

#include "GeometricObject.h"
#include "Shader.h"
#include "Scene.h"
#include "CircularParabola.h"
#include "ObjectData.h"
#include "GridFloor.h"
#include "PositionalLight.h"
#include "DirectionalLight.h"

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
std::unique_ptr<Scene> scene = std::make_unique<Scene>();
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;
std::unique_ptr<CircularParabola> cp;
std::unique_ptr<GridFloor> gridFloor;
std::vector<std::shared_ptr<SceneObject>> lights;
std::vector<std::shared_ptr<SceneObject>> cubes;
glm::vec3 lightPos = glm::vec3(0.0f, 20.0f, 3.0f);


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
	
	shaderProgram = std::make_shared<Shader>("vert.vert", "frag.frag");
	lampShader = std::make_shared<Shader>("lamp.vert", "lamp.frag");

	loop();

	glfwTerminate();
	return 0;
}

void loop() {
	cp = std::make_unique<CircularParabola>(shaderProgram);
	gridFloor = std::make_unique<GridFloor>(shaderProgram, 80);

	scene->light = std::make_shared<PositionalLight>();

	//scene->addObjectVec(gridFloor->getFloorLines());
	//scene->addObjectVec(cp->getFallingCubes());
	//scene->addObjectVec(cp->getGraphLines());
	createGeometry();

	scene->addTexture("container.jpg");
	scene->addTexture("container2.png");
	scene->addTexture("container2_specular.png");
	scene->addTexture("lighting_maps_specular_color.png");
	scene->addTexture("matrix.jpg");
	scene->addTexture("colorful.jpg");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, scene->textureMap["container2.png"]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, scene->textureMap["container2_specular.png"]);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, scene->textureMap["matrix.jpg"]);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		scene->light->setLightPosDir(lightPos);
		//scene->light->setLightColor(glm::vec3(1.0f, 0.0f, 1.0f));

		scene->renderScene();
		updateGeometry();

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

void createGeometry()
{
	//cube
	Material material{ glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, .031f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f };
	std::shared_ptr<GeometricObject> cube = std::make_shared<Cube>("container2.png", material);
	glm::mat4 model;
	std::shared_ptr<SceneObject> list = std::make_shared<SceneObject>();

	for (float i = 0; i < 3; i++) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, i * 6));
		model = glm::scale(model, glm::vec3(3.0f));
		std::shared_ptr<SceneObject> list = std::make_shared<SceneObject>();
		*list = { cube, Scene::createVAO(cube->vertexData), model, shaderProgram, GL_TRIANGLES };
		cubes.push_back(list);
		scene->addObjectVec(cubes);
	}
	


	//light
	model = glm::mat4(1.0f);
	list.reset(new SceneObject());
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.5f));
	*list = { cube, Scene::createVAO(cube->vertexData), model, lampShader, GL_TRIANGLES };
	lights.push_back(list);
	scene->addObjectVec(lights);
}

void updateGeometry()
{
	cp->update();
	gridFloor->updateFloor(scene->camera);

	for (auto obj : cubes) {
		//obj->model = glm::rotate(obj->model, glm::radians(2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::mat4 inverseModel(1.0f);
	//lights[0]->model = glm::rotate(lights[0]->model, glm::radians(1.0f), glm::vec3(0.0f, 1.0f,0.0f));
	//inverseModel = glm::inverse(lights[0]->model);
	//lights[0]->model = glm::translate(lights[0]->model, glm::vec3(0.10f, 0.0f, 0.0f));
	//lights[0]->model = inverseModel * lights[0]->model;
	//lightPos = lights[0]->model * glm::vec4(1.0f);
	//std::cout << lightPos.x << ", " << lightPos.y << ", " << lightPos.z << std::endl;
}
