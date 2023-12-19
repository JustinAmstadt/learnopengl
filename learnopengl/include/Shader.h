#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>

class Shader
{
public:
    // the program ID
    GLuint ID = -1;

    std::string vertexShaderName;
    std::string fragShaderName;
    std::string TCShaderName;
    std::string TEShaderName;

    // constructor reads and builds the shader
    Shader(const char* vertexFile, const char* fragFile, const char* TEFile, const char* TCFile);
    // use/activate the shader
    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

private:
    std::string vertexShaderSource;
    std::string fragShaderSource;
    std::string TCShaderSource;
    std::string TEShaderSource;

    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int TCShader = -1;
    unsigned int TEShader = -1;

    unsigned int shaderProgram;
    bool isLinked = false;

    void checkShaderError(unsigned int shaderHandle, std::string name);
    void makeShaderProgram();
    void readShader(std::string vertexFile, std::string& shaderSource, std::string name);
    void readTessellationShaders(const char* TEFile, const char* TCFile);
    void addVertFragShaders();
    void addTessellationShaders();
};
#endif