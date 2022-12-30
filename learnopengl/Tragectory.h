#ifndef TRAGECTORY_H
#define TRAGECTOR_H

#include <iostream>
#include <queue>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Target {
	float initialDistance = 0;
	float traveledDistance = 0;
	glm::vec3 direction = glm::vec3(0.0f);
};

class Tragectory {
public:
	std::queue<Target> targetQueue;
	float speed = 0.03f;

	void addTarget(glm::vec3 t, glm::vec3 currentPos) {
		Target newTarget;
		glm::vec3 displacement = t - currentPos;
		newTarget.initialDistance = glm::length(displacement);
		newTarget.direction = glm::normalize(displacement);
		targetQueue.push(newTarget);
	}

	void addTargetVec(std::vector<glm::vec3> targets, glm::vec3 currentPos) {
		for (const glm::vec3& t : targets) {
			Target newTarget;
			glm::vec3 displacement = t - currentPos;
			newTarget.initialDistance = glm::length(displacement);
			newTarget.direction = glm::normalize(displacement);
			targetQueue.push(newTarget);
		}
	}

	glm::mat4 update() {
		glm::mat4 model(1.0f);
		if (targetQueue.size() > 0) {
			glm::vec3 direction = glm::vec3(speed) * targetQueue.front().direction;
			model = glm::translate(model, direction);
			targetQueue.front().traveledDistance += glm::length(direction);
			if (targetQueue.front().traveledDistance > targetQueue.front().initialDistance) {
				targetQueue.pop();
			}
		}
		return model;
	}

	void clear() {
		while (!targetQueue.empty())
			targetQueue.pop();
	}
};

#endif