#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


class ShaderProgram {
public:
	ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
	~ShaderProgram();
	void use();
	bool compiled() const { return isCompiled; }
	GLuint getID() const { return programID; }
private:
	bool loadShader(const std::string& source, GLenum shaderType, GLuint& shaderID);
	GLuint programID = 0;
	bool isCompiled = false;
};
