#ifndef SQUARE_H
#define SQUARE_H
#include "GeometricObject.h"

class Square : public GeometricObject {
private:
	std::vector<glm::vec2> texCoords = {
	glm::vec2(1.0f, 1.0f),  // lower-left corner  
	glm::vec2(1.0f, 0.0f),  // lower-right corner
	glm::vec2(0.0f, 0.0f),   // top-center corner
	glm::vec2(0.0f, 1.0f),
	};
public:
	Square(glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
};

#endif