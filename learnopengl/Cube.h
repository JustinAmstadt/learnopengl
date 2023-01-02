#ifndef CUBE_H
#define CUBE_H
#include "GeometricObject.h"

class Cube : public GeometricObject {
private:
	
public:
	Cube(Material material = Material{ glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, .031f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f }
		, glm::vec4 defaultColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)) : GeometricObject(
		std::vector<glm::vec3> {
		glm::vec3(-0.5f, -0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f, -0.5f),
			glm::vec3(0.5f, 0.5f, -0.5f),
			glm::vec3(0.5f, 0.5f, -0.5f),
			glm::vec3(-0.5f, 0.5f, -0.5f),
			glm::vec3(-0.5f, -0.5f, -0.5f),

			glm::vec3(-0.5f, -0.5f, 0.5f),
			glm::vec3(0.5f, -0.5f, 0.5f),
			glm::vec3(0.5f, 0.5f, 0.5f),
			glm::vec3(0.5f, 0.5f, 0.5f),
			glm::vec3(-0.5f, 0.5f, 0.5f),
			glm::vec3(-0.5f, -0.5f, 0.5f),

			glm::vec3(-0.5f, 0.5f, 0.5f),
			glm::vec3(-0.5f, 0.5f, -0.5f),
			glm::vec3(-0.5f, -0.5f, -0.5f),
			glm::vec3(-0.5f, -0.5f, -0.5f),
			glm::vec3(-0.5f, -0.5f, 0.5f),
			glm::vec3(-0.5f, 0.5f, 0.5f),

			glm::vec3(0.5f, 0.5f, 0.5f),
			glm::vec3(0.5f, 0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f, 0.5f),
			glm::vec3(0.5f, 0.5f, 0.5f),

			glm::vec3(-0.5f, -0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f, 0.5f),
			glm::vec3(0.5f, -0.5f, 0.5f),
			glm::vec3(-0.5f, -0.5f, 0.5f),
			glm::vec3(-0.5f, -0.5f, -0.5f),

			glm::vec3(-0.5f, 0.5f, -0.5f),
			glm::vec3(0.5f, 0.5f, -0.5f),
			glm::vec3(0.5f, 0.5f, 0.5f),
			glm::vec3(0.5f, 0.5f, 0.5f),
			glm::vec3(-0.5f, 0.5f, 0.5f),
			glm::vec3(-0.5f, 0.5f, -0.5f),
	},
		
		std::vector<glm::vec3>{
			glm::vec3(0.0f, 0.0f, -1.0f),
				glm::vec3(0.0f, 0.0f, -1.0f),
				glm::vec3(0.0f, 0.0f, -1.0f),
				glm::vec3(0.0f, 0.0f, -1.0f),
				glm::vec3(0.0f, 0.0f, -1.0f),
				glm::vec3(0.0f, 0.0f, -1.0f),

				glm::vec3(0.0f, 0.0f, 1.0f),
				glm::vec3(0.0f, 0.0f, 1.0f),
				glm::vec3(0.0f, 0.0f, 1.0f),
				glm::vec3(0.0f, 0.0f, 1.0f),
				glm::vec3(0.0f, 0.0f, 1.0f),
				glm::vec3(0.0f, 0.0f, 1.0f),

				glm::vec3(-1.0f, 0.0f, 0.0f),
				glm::vec3(-1.0f, 0.0f, 0.0f),
				glm::vec3(-1.0f, 0.0f, 0.0f),
				glm::vec3(-1.0f, 0.0f, 0.0f),
				glm::vec3(-1.0f, 0.0f, 0.0f),
				glm::vec3(-1.0f, 0.0f, 0.0f),

				glm::vec3(1.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 0.0f, 0.0f),

				glm::vec3(0.0f, -1.0f, 0.0f),
				glm::vec3(0.0f, -1.0f, 0.0f),
				glm::vec3(0.0f, -1.0f, 0.0f),
				glm::vec3(0.0f, -1.0f, 0.0f),
				glm::vec3(0.0f, -1.0f, 0.0f),
				glm::vec3(0.0f, -1.0f, 0.0f),

				glm::vec3(0.0f, 1.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f),
		}, defaultColor) 
	{
		this->material = material;
	}

	Cube(Material material, std::string textureFileName) : GeometricObject(
		std::vector<glm::vec3> {
		glm::vec3(-0.5f, -0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f, -0.5f),
			glm::vec3(0.5f, 0.5f, -0.5f),
			glm::vec3(0.5f, 0.5f, -0.5f),
			glm::vec3(-0.5f, 0.5f, -0.5f),
			glm::vec3(-0.5f, -0.5f, -0.5f),

			glm::vec3(-0.5f, -0.5f, 0.5f),
			glm::vec3(0.5f, -0.5f, 0.5f),
			glm::vec3(0.5f, 0.5f, 0.5f),
			glm::vec3(0.5f, 0.5f, 0.5f),
			glm::vec3(-0.5f, 0.5f, 0.5f),
			glm::vec3(-0.5f, -0.5f, 0.5f),

			glm::vec3(-0.5f, 0.5f, 0.5f),
			glm::vec3(-0.5f, 0.5f, -0.5f),
			glm::vec3(-0.5f, -0.5f, -0.5f),
			glm::vec3(-0.5f, -0.5f, -0.5f),
			glm::vec3(-0.5f, -0.5f, 0.5f),
			glm::vec3(-0.5f, 0.5f, 0.5f),

			glm::vec3(0.5f, 0.5f, 0.5f),
			glm::vec3(0.5f, 0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f, 0.5f),
			glm::vec3(0.5f, 0.5f, 0.5f),

			glm::vec3(-0.5f, -0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f, 0.5f),
			glm::vec3(0.5f, -0.5f, 0.5f),
			glm::vec3(-0.5f, -0.5f, 0.5f),
			glm::vec3(-0.5f, -0.5f, -0.5f),

			glm::vec3(-0.5f, 0.5f, -0.5f),
			glm::vec3(0.5f, 0.5f, -0.5f),
			glm::vec3(0.5f, 0.5f, 0.5f),
			glm::vec3(0.5f, 0.5f, 0.5f),
			glm::vec3(-0.5f, 0.5f, 0.5f),
			glm::vec3(-0.5f, 0.5f, -0.5f),
	},
		std::vector<glm::vec3>{
			glm::vec3(0.0f, 0.0f, -1.0f),
				glm::vec3(0.0f, 0.0f, -1.0f),
				glm::vec3(0.0f, 0.0f, -1.0f),
				glm::vec3(0.0f, 0.0f, -1.0f),
				glm::vec3(0.0f, 0.0f, -1.0f),
				glm::vec3(0.0f, 0.0f, -1.0f),

				glm::vec3(0.0f, 0.0f, 1.0f),
				glm::vec3(0.0f, 0.0f, 1.0f),
				glm::vec3(0.0f, 0.0f, 1.0f),
				glm::vec3(0.0f, 0.0f, 1.0f),
				glm::vec3(0.0f, 0.0f, 1.0f),
				glm::vec3(0.0f, 0.0f, 1.0f),

				glm::vec3(-1.0f, 0.0f, 0.0f),
				glm::vec3(-1.0f, 0.0f, 0.0f),
				glm::vec3(-1.0f, 0.0f, 0.0f),
				glm::vec3(-1.0f, 0.0f, 0.0f),
				glm::vec3(-1.0f, 0.0f, 0.0f),
				glm::vec3(-1.0f, 0.0f, 0.0f),

				glm::vec3(1.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 0.0f, 0.0f),

				glm::vec3(0.0f, -1.0f, 0.0f),
				glm::vec3(0.0f, -1.0f, 0.0f),
				glm::vec3(0.0f, -1.0f, 0.0f),
				glm::vec3(0.0f, -1.0f, 0.0f),
				glm::vec3(0.0f, -1.0f, 0.0f),
				glm::vec3(0.0f, -1.0f, 0.0f),

				glm::vec3(0.0f, 1.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f),
		}, material,
			std::vector<glm::vec2> {
				glm::vec2(0.0f, 0.0f),
				glm::vec2(1.0f, 0.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(0.0f, 1.0f),
				glm::vec2(0.0f, 0.0f),

				glm::vec2(0.0f, 0.0f),
				glm::vec2(1.0f, 0.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(0.0f, 1.0f),
				glm::vec2(0.0f, 0.0f),


				glm::vec2(1.0f, 0.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(0.0f, 1.0f),
				glm::vec2(0.0f, 1.0f),
				glm::vec2(0.0f, 0.0f),
				glm::vec2(1.0f, 0.0f),

				glm::vec2(1.0f, 0.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(0.0f, 1.0f),
				glm::vec2(0.0f, 1.0f),
				glm::vec2(0.0f, 0.0f),
				glm::vec2(1.0f, 0.0f),


				glm::vec2(0.0f, 1.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(1.0f, 0.0f),
				glm::vec2(1.0f, 0.0f),
				glm::vec2(0.0f, 0.0f),
				glm::vec2(0.0f, 1.0f),

				glm::vec2(0.0f, 1.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(1.0f, 0.0f),
				glm::vec2(1.0f, 0.0f),
				glm::vec2(0.0f, 0.0f),
				glm::vec2(0.0f, 1.0f),
			},
				textureFileName)
	{}
};


#endif