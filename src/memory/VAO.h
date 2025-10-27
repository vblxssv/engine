#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include "VBO.h"
#include "EBO.h"
#include "../attribute/Attribute.h"


class VAO {
private:
	GLuint _id;
public:
	VAO(const std::unique_ptr<VBO<GLfloat>>& vbo,
		const std::unique_ptr<VBO<GLuint>>& instance_vbo, 
		const std::unique_ptr<EBO>& ebo, 
		const AttributeLine& attribs);

	~VAO();
	void bind();
	void unbind();
	GLuint getId() {
		return _id;
	}
};





