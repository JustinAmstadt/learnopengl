#ifndef CUBE_H
#define CUBE_H
#include "GeometricObject.h"

class Cube : public GeometricObject {
private:
	
public:
	Cube(glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f));
};


#endif