#include "CircularParabola.h"

void CircularParabola::createLineFunc(std::shared_ptr<Shader> shaderProgram)
{
	std::vector<GLuint> indices;
	std::vector<glm::vec4> graphColor;
	glm::mat4 model = glm::mat4(1.0f);

	for (float i = 0; i < 360.0f; i += 360 / numLines) {
		model = glm::rotate(model, glm::radians(360.0f / numLines), glm::vec3(0.0f, 1.0f, 0.0f));
		for (float j = 0.0; j < numPoints / 10.0; j += 0.1) {
			glm::vec4 vec = model * glm::vec4(j, lineFuncFormula(j), 0, 0); //update bottom function too
			//std::cout << counter++ << ": " << vec[0] << ", " << vec[1] << ", " << vec[2] << std::endl;
			verts.push_back(glm::vec3(vec[0], vec[1], vec[2]));
			graphColor.push_back(glm::vec4(0.0f, 0.0f, i * 2 / 100, 0.5f));
		}
	}

	//std::cout << verts.size() << std::endl;

	//all faces except the last one
	for (int i = 0; i < verts.size() - (verts.size() / numLines); i += verts.size() / numLines) {
		indices.push_back(numPoints + 1 + i);
		indices.push_back(1 + i);
		indices.push_back(i);
		for (int j = 0; j < numPoints - 2; j++) {
			indices.push_back(numPoints + 1 + j + i);
			indices.push_back(2 + j + i);
			indices.push_back(1 + j + i);

			indices.push_back(numPoints + 2 + j + i);
			indices.push_back(2 + j + i);
			indices.push_back(numPoints + 1 + j + i);
		}
	}
	//last face
	int lastFaceStart = verts.size() - (verts.size() / numLines);
	indices.push_back(1);
	indices.push_back(1 + lastFaceStart);
	indices.push_back(0);
	for (int i = 0; i < numPoints - 2; i++) {
		indices.push_back(1 + i);
		indices.push_back(lastFaceStart + 2 + i);
		indices.push_back(lastFaceStart + 1 + i);

		indices.push_back(2 + i);
		indices.push_back(lastFaceStart + 2 + i);
		indices.push_back(1 + i);
	}

	std::shared_ptr<GeometricObject> line = std::make_shared<GeometricObject>(verts);
	line->setColor(glm::vec4(0.0f, 0.0f, 0.8f, 0.8f));
	line->indices = indices;
	std::shared_ptr<SceneObject> list = std::make_shared<SceneObject>();
	*list = { line, Scene::createVAO(line->vertexData, line->indices), model, shaderProgram, GL_TRIANGLES };
	graphLines.push_back(list);
}

float CircularParabola::lineFuncFormula(float val)
{
	return 0.01f * val * val;
}

glm::mat4 CircularParabola::resetCubePosition(std::shared_ptr<GeometricObject> cube)
{
	glm::mat4 model(1.0f);
	int randomVertIndex = 0;
	int adjVertIndex;

	while (randomVertIndex % numPoints == 0) {
		randomVertIndex = rand() % verts.size();
	}

	adjVertIndex = randomVertIndex + numPoints;

	if (adjVertIndex > verts.size()) {
		adjVertIndex = randomVertIndex - (randomVertIndex / numPoints) * numPoints;
	}

	glm::vec3 center = verts[randomVertIndex] - glm::vec3(0.5f) * (verts[randomVertIndex] - verts[adjVertIndex]);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(0.0f, 5.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f));

	cube->tragectory->addTarget(center, center + glm::vec3(0.0f, 5.0f, 0.0f));
	cube->tragectory->addTarget(glm::vec3(0.0f, 1.0f, 0.0f), center);

	return model;
}

void CircularParabola::createFallingCubes(std::shared_ptr<Shader> shaderProgram)
{
	Material material{ glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, .031f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f };
	std::shared_ptr<SceneObject> list;
	glm::mat4 model(1.0f);
	std::shared_ptr<GeometricObject> cube = std::make_shared<Cube>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), material);
	GLuint VAO = Scene::createVAO(cube->vertexData);

	for (int i = 0; i < 10; i++) {
		list.reset(new SceneObject());
		cube.reset(new Cube(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), material));
		model = resetCubePosition(cube);
		*list = { cube, VAO, model, shaderProgram, GL_TRIANGLES };
		fallingCubes.push_back(list);
	}
}

void CircularParabola::updateFallingCubes()
{
	for (int i = 0; i < fallingCubes.size(); i++) {
		fallingCubes[i]->model = fallingCubes[i]->object->tragectory->update() * fallingCubes[i]->model;
		fallingCubes[i]->model = glm::rotate(fallingCubes[i]->model, glm::radians(1.0f), glm::vec3(0.4f, 0.3f, 0.6f));
		if (fallingCubes[i]->object->tragectory->targetQueue.size() == 0) {
			fallingCubes[i]->model = resetCubePosition(fallingCubes[i]->object);
		}
	}
}
