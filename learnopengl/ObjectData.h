#ifndef OBJECT_DATA_H
#define OBJECT_DATA_H

#include<vector>
#include "Shader.h"
#include "Scene.h"
#include "GeometricObject.h"

class ObjectData {
private:
	ObjectData() {};
public:
	static void createData(Shader* shaderProgram);
	static void updateData(const Camera& camera);
	static void createSphere(int radius, int sectorCount, int stackCount, std::vector<glm::vec3>& vertices, std::vector<GLuint>& indices);
	static void createFloor(Shader* shaderProgram, float size);
	static void createLineFunc(Shader* shaderProgram);
	static void setFloorDistance(float distance) {
		floorDistance = distance;
	}
	static void updateFloor(const Camera& camera);
	static std::vector<glm::vec3> vertices;
	static std::vector<glm::vec3> cubeVertices;
	static std::vector<glm::vec3> colors;
	static std::vector<GLuint> indices;
	static std::vector<glm::vec2> texCoords;
	static std::vector<glm::vec3> linepts;
	static GeometricObject* square;
	static GeometricObject* cube;
	static GeometricObject* circle;
	static std::vector<SceneObject*> basicGeometryVec;
	static std::vector<SceneObject*> floorLines;
	static std::vector<SceneObject*> graphLines;
	static float floorDistance;
};
#endif