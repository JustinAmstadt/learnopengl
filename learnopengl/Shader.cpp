#include "Shader.h"
#include <fstream>
#include <iostream>

void Shader::checkShaderError(unsigned int shaderHandle, std::string name)
{
	int  success;
	char infoLog[512];
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderHandle, 512, NULL, infoLog);
		std::cout << "ERROR " << name << " SHADER COMPILATION FAILED\n" << infoLog << std::endl;
	}
}

void Shader::makeShaderProgram()
{
	//there's an added character at the end that must be removed to be compiled properly
	vertexShaderSource.pop_back();
	fragShaderSource.pop_back();

	const GLchar* vertexShaderSourceC = vertexShaderSource.c_str();

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSourceC, NULL);
	glCompileShader(vertexShader);
	checkShaderError(vertexShader, std::string("VERTEX"));

	const GLchar* fragmentShaderSourceC = fragShaderSource.c_str();
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSourceC, NULL);
	glCompileShader(fragmentShader);
	checkShaderError(fragmentShader, std::string("FRAGMENT"));

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);


	int  success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR SHADER PROGRAM FAILED TO LINK\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	this->ID = shaderProgram;
}

void Shader::readShaders(std::string vertexFile, std::string fragFile)
{
	std::ifstream file(vertexFile);
	std::string str;
	if (file.is_open()) {
		while (file) {
			str += file.get();
		}
	}
	else {
		std::cout << "vertex file could not open" << std::endl;
	}
	vertexShaderSource = str;

	file.close();

	str.clear();

	file.open(fragFile);
	if (file.is_open()) {
		while (file) {
			str += file.get();
		}
	}
	else {
		std::cout << "fragment file could not open" << std::endl;
	}

	//std::cout << str << std::endl;

	fragShaderSource = str;
	file.close();
}

Shader::Shader(const char* vertexFile, const char* fragFile)
{
	readShaders(vertexFile, fragFile);
	makeShaderProgram();
}

void Shader::use()
{
	glUseProgram(this->ID);
}
