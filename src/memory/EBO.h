#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <unordered_map>



class EBO {
private:
	GLuint _id;
	GLuint indices;
public:
	EBO();
	EBO(const std::vector<GLuint>& data);
	~EBO();
	void bind() const;
	void unbind() const;
	void setData(const std::vector<GLuint>& data);
	GLuint getId() const;
	GLuint get_indices();
};
