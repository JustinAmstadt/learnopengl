#include "ObjectData.h"

std::vector<glm::vec3> ObjectData::vertices;
std::vector<glm::vec3> ObjectData::colors;
std::vector<GLuint> ObjectData::indices;
std::vector<glm::vec2> ObjectData::texCoords;
std::vector<glm::vec3> ObjectData::linepts;
GeometricObject* ObjectData::square;
GeometricObject* ObjectData::circle;
std::vector<SceneObject> ObjectData::sceneObjectVec;

void ObjectData::createData(Shader* shaderProgram) {
	vertices = {
		glm::vec3(0.5f,  0.5f, 0.0f),  // top right
		glm::vec3(0.5f, -0.5f, 0.0f),  // bottom right
		glm::vec3(-0.5f, -0.5f, 0.0f),  // bottom left
		glm::vec3(-0.5f,  0.5f, 0.0f),   // top left

		//glm::vec3(0.0f, 1.0f, 0.0f),	// center
		//glm::vec3(-1.0f, -1.0f, 0.0f),	// bottom right
		//glm::vec3(1.0f, -1.0f, 0.0f),	// bottom left
	};

	colors = {
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 1.0f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 1.0f),
		glm::vec3(0.5f, 0.5f, 0.5f),
	};

	indices = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	texCoords = {
		glm::vec2(1.0f, 1.0f),  // lower-left corner  
		glm::vec2(1.0f, 0.0f),  // lower-right corner
		glm::vec2(0.0f, 0.0f),   // top-center corner
		glm::vec2(0.0f, 1.0f),
	};

	square = new GeometricObject(vertices);
	square->indices = indices;

	glm::mat4 model = glm::mat4(1.0f);

	sceneObjectVec.push_back(
		{ square, Scene::createVAO(square->vertexData, square->indices),
			model, shaderProgram, GL_TRIANGLES });


	for (double i = -5; i < 5; i = i + .1) {
		if (sin(i) != 0)
			linepts.push_back(glm::vec3(cos(i), sin(i), 0.0f));
	}

	circle = new GeometricObject(linepts, glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::scale(model, glm::vec3(0.2, 0.2, 0.2));
	sceneObjectVec.push_back({ circle, Scene::createVAO(circle->vertexData), glm::mat4(1.0f), shaderProgram, GL_TRIANGLE_FAN });
}

//taken from http://www.songho.ca/opengl/gl_sphere.html
void createSphere(int radius, int sectorCount, int stackCount, std::vector<glm::vec3>& vertices, std::vector<GLuint>& indices) {
	const float PI = 3.1415926f;

	std::vector<GLfloat> normals;
	std::vector<GLfloat> texCoords;

	float x, y, z, xy;                              // vertex position
	float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
	float s, t;                                     // vertex texCoord

	float sectorStep = 2 * PI / sectorCount;
	float stackStep = PI / stackCount;
	float sectorAngle, stackAngle;

	for (int i = 0; i <= stackCount; ++i)
	{
		stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
		xy = radius * cosf(stackAngle);             // r * cos(u)
		z = radius * sinf(stackAngle);              // r * sin(u)

		// add (sectorCount+1) vertices per stack
		// the first and last vertices have same position and normal, but different tex coords
		for (int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;           // starting from 0 to 2pi

			// vertex position (x, y, z)
			x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
			y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
			vertices.push_back(glm::vec3(x, y, x));

			// normalized vertex normal (nx, ny, nz)
			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;
			normals.push_back(nx);
			normals.push_back(ny);
			normals.push_back(nz);

			// vertex tex coord (s, t) range between [0, 1]
			s = (float)j / sectorCount;
			t = (float)i / stackCount;
			texCoords.push_back(s);
			texCoords.push_back(t);
		}
	}

	// generate CCW index list of sphere triangles
// k1--k1+1
// |  / |
// | /  |
// k2--k2+1
	std::vector<int> lineIndices;
	int k1, k2;
	for (int i = 0; i < stackCount; ++i)
	{
		k1 = i * (sectorCount + 1);     // beginning of current stack
		k2 = k1 + sectorCount + 1;      // beginning of next stack

		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{
			// 2 triangles per sector excluding first and last stacks
			// k1 => k2 => k1+1
			if (i != 0)
			{
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}

			// k1+1 => k2 => k2+1
			if (i != (stackCount - 1))
			{
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}

			// store indices for lines
			// vertical lines for all stacks, k1 => k2
			lineIndices.push_back(k1);
			lineIndices.push_back(k2);
			if (i != 0)  // horizontal lines except 1st stack, k1 => k+1
			{
				lineIndices.push_back(k1);
				lineIndices.push_back(k1 + 1);
			}
		}
	}
}