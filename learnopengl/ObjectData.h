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
	static float lineFuncFormula(float val);
	static float lineFuncTanLine(float x, float ROC, int vertInt, int numPoints);
	static void setFloorDistance(float distance) {
		floorDistance = distance;
	}
	static void createFallingCubes(Shader* shaderProgram, std::vector<glm::vec3> verts, float numLines, int numPoints);
	static void updateFallingCubes();
	static void updateFloor(const Camera& camera);
	static std::vector<glm::vec3> colors;
	static std::vector<glm::vec3> linepts;
	static GeometricObject* circle;
	static std::vector<SceneObject*> basicGeometryVec;
	static std::vector<SceneObject*> floorLines;
	static std::vector<SceneObject*> graphLines;
	static std::vector<SceneObject*> fallingCubes;
	static float floorDistance;
};
#endif