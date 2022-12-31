#ifndef CIRCULARPARABOLA_H
#define CIRCULARPARABOLA_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "GeometricObject.h"
#include "Scene.h"
#include "Cube.h"

class CircularParabola {
private:
	std::vector<std::shared_ptr<SceneObject>> fallingCubes;
	std::vector<std::shared_ptr<SceneObject>> graphLines;
	std::vector<glm::vec3> verts;
	int numPoints;
	float numLines;

	void createLineFunc(std::shared_ptr<Shader> shaderProgram);
	float lineFuncFormula(float val);
	glm::mat4 resetCubePosition(std::shared_ptr<GeometricObject> cube);
	void createFallingCubes(std::shared_ptr<Shader> shaderProgram);
	void updateFallingCubes();
public:
	CircularParabola(std::shared_ptr<Shader> shaderProgram, int numPoints = 200, float numLines = 100.0) {
		this->numLines = numLines;
		this->numPoints = numPoints;
		createLineFunc(shaderProgram);
		createFallingCubes(shaderProgram);
	}
	~CircularParabola() {
		fallingCubes.clear();
		graphLines.clear();
	}

	void update() { updateFallingCubes(); }

	const std::vector<std::shared_ptr<SceneObject>>& getFallingCubes() {
		return fallingCubes;
	}
	const std::vector<std::shared_ptr<SceneObject>>& getGraphLines() {
		return graphLines;
	}
};

#endif