#ifndef CUBE_H
#define CUBE_H
#include "GeometricObject.h"

class Cube : public GeometricObject {
private:
	
public:
	Cube(glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
};


#endif