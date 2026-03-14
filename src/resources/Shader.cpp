#include "Resource.h"



Shader::Shader(GLuint id)
	:id_(id)
{

}

Shader::~Shader()
{
	glDeleteProgram(id_);
}

void Shader::use()
{
	glUseProgram(id_);
}

GLuint Shader::id() const
{
	return id_;
}

void Shader::set_uniform_uint(const std::string& name, GLuint value)
{
	GLint location = glGetUniformLocation(id_, name.c_str());
	if (location == -1) {
		std::cout << "Warning: uniform '" << name << "' not found!\n";
		return;
	}
	glUniform1ui(location, value);
}

void Shader::set_uniform_int(const std::string& name, GLint value)
{
	GLint location = glGetUniformLocation(id_, name.c_str());
	if (location == -1) {
		std::cout << "Warning: uniform '" << name << "' not found!\n";
		return;
	}
	glUniform1ui(location, value);
}

void Shader::set_uniform_float(const std::string& name, GLfloat value)
{
	GLint location = glGetUniformLocation(id_, name.c_str());
	if (location == -1) {
		std::cout << "Warning: uniform '" << name << "' not found!\n";
		return;
	}
	glUniform1f(location, value);
}

void Shader::set_uniform_mat4(const std::string& name, const glm::mat4& mat4)
{
	GLint location = glGetUniformLocation(id_, name.c_str());
	if (location == -1) {
		std::cout << "Warning: uniform '" << name << "' not found!\n";
		return;
	}
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat4));
}

