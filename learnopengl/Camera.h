#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	glm::mat4 view;

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	//mouse movement
	bool firstMouse = false;
	float lastX;
	float lastY;
	float pitch;
	float yaw;

	Camera() {
		view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
	}

	void update();
	void mouseUpdate(double xpos, double ypos);
};

#endif
