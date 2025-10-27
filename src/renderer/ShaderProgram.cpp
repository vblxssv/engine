#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLuint vs = 0, fs = 0;

	if (!loadShader(vertexShader, GL_VERTEX_SHADER, vs)) {
		std::cout << "Can`t load vertex shader!\n";
		return;
	}

	if (!loadShader(fragmentShader, GL_FRAGMENT_SHADER, fs)) {
		std::cout << "Can`t load fragment shader!\n";
		glDeleteShader(vs);
		return;
	}

	programID = glCreateProgram();
	glAttachShader(programID, vs);
	glAttachShader(programID, fs);
	glLinkProgram(programID);
	glDeleteShader(vs);
	glDeleteShader(fs);
	isCompiled = true;
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(programID);
}

void ShaderProgram::use()
{
	glUseProgram(programID);
}

bool ShaderProgram::loadShader(const std::string& source, GLenum shaderType, GLuint& shaderID)
{
	shaderID = glCreateShader(shaderType);
	const char* src = source.c_str();
	std::cout << src << std::endl;
	glShaderSource(shaderID, 1, &src, nullptr);
	glCompileShader(shaderID);
	GLint success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	return success == GL_TRUE;
}
