#ifndef OBJECT_DATA_H
#define OBJECT_DATA_H

#include <memory>
#include<vector>
#include "Shader.h"
#include "Scene.h"
#include "GeometricObject.h"

class ObjectData {
private:
	ObjectData() {};
public:
	static void createData(std::shared_ptr<Shader> shaderProgram);
	static void updateData();
	static void createSphere(int radius, int sectorCount, int stackCount, std::vector<glm::vec3>& vertices, std::vector<GLuint>& indices);
	static std::vector<glm::vec3> colors;
	static std::vector<glm::vec3> linepts;
	static std::shared_ptr<GeometricObject> circle;
	static std::vector<std::shared_ptr<SceneObject>> basicGeometryVec;
};
#endif
