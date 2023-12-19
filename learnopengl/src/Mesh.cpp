#include "Mesh.h"

Mesh::Mesh() {}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures){
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setupMesh();
}

Mesh::Mesh(const Mesh &mesh){
    this->vertices = mesh.vertices;
    this->indices = mesh.indices;
    this->textures = mesh.textures;
    this->VAO = mesh.VAO;
    this->VBO = mesh.VBO;
    this->EBO = mesh.EBO;
}

void Mesh::Draw(std::shared_ptr<Shader> shader, GLenum DRAW_ENUM){
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;

    for(unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++);

        shader->setInt(("material." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    glUseProgram(shader->ID);

    // draw mesh
    glBindVertexArray(VAO);
    if(indices.size() == 0){
        glDrawArrays(DRAW_ENUM, 0, vertices.size());
    }
    else{
        glDrawElements(DRAW_ENUM, indices.size(), GL_UNSIGNED_INT, 0);
    }

    glBindVertexArray(0);
}

void Mesh::setupMesh(){
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//bind the vertex array. this can store multiple vertex buffer objects
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0].position, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); //position
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(vertices[0].position)); //color
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vertices[0].position) + sizeof(vertices[0].color))); //texture
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vertices[0].position) + sizeof(vertices[0].color) + sizeof(vertices[0].texture))); //normal

  // for lines only!! checks 
  if(vertices[0].distFromStart > -1){
    std::cout << vertices[0].distFromStart;
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vertices[0].position) + sizeof(vertices[0].color) + sizeof(vertices[0].texture) + sizeof(vertices[0].normal))); //distFromStart
  }

	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbinds the vertex buffer
	glBindVertexArray(0); //unbinds the vertex array
}