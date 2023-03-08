#include "include/Shader.h"
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
	if (isLinked) {
		std::cout << "Shader program already linked!" << std::endl;
		return;
	}

	isLinked = true;

	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	if (TEShader != -1) {
		glAttachShader(shaderProgram, TEShader);
	}
	if (TCShader != -1) {
		glAttachShader(shaderProgram, TCShader);
	}
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
	if (TEShader != -1) {
		glDeleteShader(TEShader);
	}
	if (TCShader != -1) {
		glDeleteShader(TCShader);
	}

	this->ID = shaderProgram;
}

void Shader::readShader(std::string file, std::string& shaderSource, std::string name)
{
	std::ifstream inFile(file);
	std::string str;
	if (inFile.is_open()) {
		while (inFile) {
			str += inFile.get();
		}
	}
	else {
		std::cout << name + " file could not open" << std::endl;
	}
	shaderSource = str;

	inFile.close();
}

void Shader::addVertFragShaders()
{
	//there's an added character at the end that must be removed to be compiled properly
	vertexShaderSource.pop_back();
	fragShaderSource.pop_back();

	const GLchar* vertexShaderSourceC = vertexShaderSource.c_str();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSourceC, NULL);
	glCompileShader(vertexShader);
	checkShaderError(vertexShader, std::string("VERTEX"));

	const GLchar* fragmentShaderSourceC = fragShaderSource.c_str();
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSourceC, NULL);
	glCompileShader(fragmentShader);
	checkShaderError(fragmentShader, std::string("FRAGMENT"));
}

void Shader::addTessellationShaders()
{
	if (TEShaderSource.size() > 0) {
		TEShaderSource.pop_back();

		const GLchar* TEShaderSourceC = TEShaderSource.c_str();

		TEShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
		glShaderSource(TEShader, 1, &TEShaderSourceC, NULL);
		glCompileShader(TEShader);
		checkShaderError(TEShader, std::string("TESSELLATION EVALUATION"));
	}
	if (TCShaderSource.size() > 0) {
		TCShaderSource.pop_back();

		const GLchar* TCShaderSourceC = TCShaderSource.c_str();

		TCShader = glCreateShader(GL_TESS_CONTROL_SHADER);
		glShaderSource(TCShader, 1, &TCShaderSourceC, NULL);
		glCompileShader(TCShader);
		checkShaderError(TCShader, std::string("TESSELLATION CONTROL"));
	}
}

void Shader::readTessellationShaders(const char* TEFile, const char* TCFile)
{

	if (TEFile != nullptr) {
		readShader(TEFile, TEShaderSource, "tessellation evaluation");
	}
	else {
		return;
	}
	if (TCFile != nullptr) {
		readShader(TCFile, TCShaderSource, "tessellation control");
	}
}

Shader::Shader(const char* vertexFile, const char* fragFile, const char* TEFile, const char* TCFile)
{
	readShader(vertexFile, vertexShaderSource, "vertex");
	readShader(fragFile, fragShaderSource, "fragment");
	readTessellationShaders(TEFile, TCFile);
	addTessellationShaders();
	addVertFragShaders();
	makeShaderProgram();
}

void Shader::use()
{
	glUseProgram(this->ID);
}
