#include "ObjectData.h"
#include "Camera.h"
#include <iostream>
#include <initializer_list>

std::vector<glm::vec3> ObjectData::vertices;
std::vector<glm::vec3> ObjectData::cubeVertices;
std::vector<glm::vec3> ObjectData::colors;
std::vector<GLuint> ObjectData::indices;
std::vector<glm::vec2> ObjectData::texCoords;
std::vector<glm::vec3> ObjectData::linepts;
GeometricObject* ObjectData::square;
GeometricObject* ObjectData::cube;
GeometricObject* ObjectData::circle;
std::vector<SceneObject*> ObjectData::basicGeometryVec;
std::vector<SceneObject*> ObjectData::floorLines;
std::vector<SceneObject*> ObjectData::graphLines;
float ObjectData::floorDistance = 4.0f;

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

	cubeVertices = {
		glm::vec3(-0.5f, -0.5f, -0.5f),
		 glm::vec3(0.5f, -0.5f, -0.5f),
		 glm::vec3(0.5f,  0.5f, -0.5f),
		 glm::vec3(0.5f,  0.5f, -0.5f),
		glm::vec3(-0.5f,  0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),

		glm::vec3(-0.5f, -0.5f,  0.5f),
		glm::vec3(0.5f, -0.5f,  0.5f),
		glm::vec3(0.5f,  0.5f,  0.5f),
		glm::vec3(0.5f,  0.5f,  0.5f),
		glm::vec3(-0.5f,  0.5f,  0.5f),
	glm::vec3(-0.5f, -0.5f,  0.5f),

	glm::vec3(-0.5f,  0.5f,  0.5f),
	glm::vec3(-0.5f,  0.5f, -0.5f),
	glm::vec3(-0.5f, -0.5f, -0.5f),
	glm::vec3(-0.5f, -0.5f, -0.5f),
	glm::vec3(-0.5f, -0.5f,  0.5f),
		glm::vec3(-0.5f,  0.5f,  0.5f),

		glm::vec3(0.5f,  0.5f,  0.5f),
		glm::vec3(0.5f,  0.5f, -0.5f),
	glm::vec3(0.5f, -0.5f, -0.5f),
	glm::vec3(0.5f, -0.5f, -0.5f),
	glm::vec3(0.5f, -0.5f,  0.5f),
		glm::vec3(0.5f,  0.5f,  0.5f),

		glm::vec3(-0.5f, -0.5f, -0.5f),
	glm::vec3(0.5f, -0.5f, -0.5f),
	glm::vec3(0.5f, -0.5f,  0.5f),
	glm::vec3(0.5f, -0.5f,  0.5f),
		glm::vec3(-0.5f, -0.5f,  0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),

	glm::vec3(-0.5f,  0.5f, -0.5f),
	glm::vec3(0.5f,  0.5f, -0.5f),
	glm::vec3(0.5f,  0.5f,  0.5f),
	glm::vec3(0.5f,  0.5f,  0.5f),
	glm::vec3(-0.5f,  0.5f,  0.5f),
	glm::vec3(-0.5f,  0.5f, -0.5f),
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

	
	cube = new GeometricObject(cubeVertices, colors);
	square = new GeometricObject(vertices);
	square->indices = indices;

	glm::mat4 model = glm::mat4(1.0f);

	SceneObject* list = new SceneObject();
	*list = { cube, Scene::createVAO(cube->vertexData), model, shaderProgram, GL_TRIANGLES };
	basicGeometryVec.push_back(list);

	list = new SceneObject();
	*list = { square, Scene::createVAO(square->vertexData, square->indices), model, shaderProgram, GL_TRIANGLES };
	//basicGeometryVec.push_back(list);


	for (double i = -5; i < 5; i = i + .1) {
		if (sin(i) != 0)
			linepts.push_back(glm::vec3(cos(i), sin(i), 0.0f));
	}

	circle = new GeometricObject(linepts, glm::vec3(1.0f, 1.0f, 1.0f));
	//model = glm::scale(model, glm::vec3(0.2, 0.2, 0.2));
	list = new SceneObject();
	*list = { circle, Scene::createVAO(circle->vertexData), model, shaderProgram, GL_TRIANGLE_FAN };
	//basicGeometryVec.push_back(list);


	createFloor(shaderProgram, 80);
	createLineFunc(shaderProgram);
}

void ObjectData::updateData(const Camera& camera)
{
	glm::mat4 model(1.0f);

	//rotate cube
	model = glm::rotate(model, glm::radians(1.0f) , glm::vec3(0.0f, 1.0f, 0.0f));
	basicGeometryVec[0]->model = model * basicGeometryVec[0]->model;

	//rotate graph
	//graphLines[0]->model = model * graphLines[0]->model;

	updateFloor(camera);
}

void ObjectData::updateFloor(const Camera& camera) 
{
	//std::cout << camera.Position[0] << ", " << camera.Position[1] << ", " << camera.Position[2] << std::endl;

	glm::mat4 model(1.0f);
	static float cameraOffsetX = 0.0f;
	static float cameraOffsetZ = 0.0f;

	model = glm::mat4(1.0f);

	//shifts the grid over by the distance between lines in the floor once the next line has been reached.
	//gives the illusion that you are running over the grid, but the grid is following you and you are flying
	//over the same square continuously
	if (camera.Position[0] >= cameraOffsetX + floorDistance) {
		cameraOffsetX += 4;
		model = glm::translate(model, glm::vec3(floorDistance, 0.0f, 0.0f));
		for (int i = 0; i < floorLines.size(); i++) {
			floorLines[i]->model = model * floorLines[i]->model;
		}
	}
	else if (camera.Position[0] < cameraOffsetX - floorDistance) {
		cameraOffsetX -= 4;
		model = glm::translate(model, glm::vec3(-floorDistance, 0.0f, 0.0f));
		for (int i = 0; i < floorLines.size(); i++) {
			floorLines[i]->model = model * floorLines[i]->model;
		}
	}

	if (camera.Position[2] >= cameraOffsetZ + floorDistance) {
		cameraOffsetZ += 4;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, floorDistance));
		for (int i = 0; i < floorLines.size(); i++) {
			floorLines[i]->model = model * floorLines[i]->model;
		}
	}
	else if (camera.Position[2] < cameraOffsetZ - floorDistance) {
		cameraOffsetZ -= 4;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -floorDistance));
		for (int i = 0; i < floorLines.size(); i++) {
			floorLines[i]->model = model * floorLines[i]->model;
		}
	}
}

void ObjectData::createFloor(Shader* shaderProgram, float size)
{
	//4 is the magic number for some reason lol
	size -= (int)size % 4;

	std::cout << "size: " << size << std::endl;

	SceneObject* list = new SceneObject();
	glm::mat4 model = glm::mat4(1.0f);

	GeometricObject* line = new GeometricObject(std::vector<glm::vec3> { glm::vec3(0.0f, -2.0f, -size),glm::vec3(0.0f, -2.0f, size) },
		glm::vec3(0.0f, 0.8f, 0.0f));

	GLuint VAO = Scene::createVAO(line->vertexData);

	//vertical middle line
	*list = { line, VAO, model, shaderProgram, GL_LINES };
	floorLines.push_back(list);
	
	//vertical right side
	for (int i = 0; i < size / 4; i++) {
		list = new SceneObject();
		model = glm::translate(model, glm::vec3(floorDistance, 0.0f, 0.0f));
		*list = { line, VAO, model, shaderProgram, GL_LINES };
		floorLines.push_back(list);
	}

	model = glm::mat4(1.0f);

	//vertical left side
	for (int i = 0; i < size / 4; i++) {
		list = new SceneObject();
		model = glm::translate(model, glm::vec3(-floorDistance, 0.0f, 0.0f));
		*list = { line, VAO, model, shaderProgram, GL_LINES };
		floorLines.push_back(list);
	}

	list = new SceneObject();
	model = glm::mat4(1.0f);

	//horizontal middle line
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	*list = { line, VAO, model, shaderProgram, GL_LINES };
	floorLines.push_back(list);

	for (int i = 0; i < size / floorDistance + 1; i++) {
		list = new SceneObject();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, (float) i * -floorDistance));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		*list = { line, VAO, model, shaderProgram, GL_LINES };
		floorLines.push_back(list);
	}

	for (int i = 0; i < size / floorDistance + 1; i++) {
		list = new SceneObject();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, (float)i * floorDistance));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		*list = { line, VAO, model, shaderProgram, GL_LINES };
		floorLines.push_back(list);
	}
}

void ObjectData::createLineFunc(Shader* shaderProgram)
{
	const float PI = 3.14159265359;

	std::vector<glm::vec3> verts;
	std::vector<GLuint> indices{ 
		22, 1, 0,
		22, 2, 1,
		23, 3, 2,
		24, 4, 3,
		40, 20, 19,

		23, 1, 22,
		24, 2, 23,
		25, 3, 24,
		41, 19, 40,
	};
	indices.clear();

	std::vector<glm::vec3> graphColor;


	float numLines = 100.0;
	glm::mat4 model = glm::mat4(1.0f);

	int numPoints = 200;
	for (float i = 0; i < 360.0; i += 360 / numLines) {
		model = glm::rotate(model, glm::radians(360.0f / numLines), glm::vec3(0.0f, 1.0f, 0.0f));
		for (float j = 0.0; j < numPoints / 10.0; j += 0.1) {
			glm::vec4 vec = model * glm::vec4(j, sin(j), 0, 0);
			//std::cout << counter++ << ": " << vec[0] << ", " << vec[1] << ", " << vec[2] << std::endl;
			verts.push_back(glm::vec3(vec[0], vec[1], vec[2]));
			graphColor.push_back(glm::vec3(0.2f, 0.4f, 0.6f));
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

	GeometricObject* line = new GeometricObject(verts);
	line->indices = indices;
	SceneObject* list = new SceneObject();
	*list = { line, Scene::createVAO(line->vertexData, line->indices), model, shaderProgram, GL_LINES };
	graphLines.push_back(list);
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