#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <memory>

#include "Shader.h"

struct Vertex {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 texture;
	glm::vec3 normal;
	float distFromStart = -1; // for lines only!!
};

struct Texture {
    GLuint id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    // mesh data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;

    Mesh();
    Mesh(const Mesh &mesh);
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
    void Draw(std::shared_ptr<Shader> shader, GLenum DRAW_ENUM);
private:
    //  render data
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};

#endif