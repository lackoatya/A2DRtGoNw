#include "Engine\Graphics\Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <assert.h>

Engine::Graphics::Shader::Shader(const GLchar *_vertexPath, const GLchar *_fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vShaderFile(_vertexPath);
	std::ifstream fShaderFile(_fragmentPath);
	std::stringstream vShaderStream, fShaderStream;

	vShaderStream << vShaderFile.rdbuf();
	fShaderStream << fShaderFile.rdbuf();

	vShaderFile.close();
	fShaderFile.close();

	vertexCode = vShaderStream.str();
	fragmentCode = fShaderStream.str();

	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		assert(false && "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" && infoLog);
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		assert(false && "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" && infoLog);
	}

	this->shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertex);
	glAttachShader(shaderProgram, fragment);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		assert(false && "ERROR::SHADER::VERTEX::LINKING_FAILED\n" && infoLog);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Engine::Graphics::Shader::~Shader()
{
	glDeleteProgram(shaderProgram);
	// TODO WTF
}