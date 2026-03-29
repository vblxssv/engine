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
	GLuint _count;
	GLenum _usage;
public:
	EBO(GLenum usage = GL_STATIC_DRAW);
	EBO(const std::vector<GLuint>& data, GLenum usage = GL_STATIC_DRAW);
	~EBO();

	EBO(const EBO&) = delete;
	EBO& operator=(const EBO&) = delete;

	EBO(EBO&& other) noexcept;
	EBO& operator=(EBO&& other) noexcept;


	void bind() const;
	void unbind() const;
	void set_data(const std::vector<GLuint>& data);
	GLuint get_id() const;
	GLuint get_count() const;
};
