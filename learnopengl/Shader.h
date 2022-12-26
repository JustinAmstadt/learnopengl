#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>

class Shader
{
private:
    std::string vertexShaderSource;
    std::string fragShaderSource;

    void checkShaderError(unsigned int shaderHandle, std::string name);
    void makeShaderProgram();
    void readShaders(std::string vertexFile, std::string fragFile);

public:
    // the program ID
    GLuint ID = -1;

    // constructor reads and builds the shader
    Shader(const char* vertexFile, const char* fragFile);
    // use/activate the shader
    void use();
};
#endif