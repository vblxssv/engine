#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <unordered_map>

template <typename T>
class VBO {
private:
	GLuint _id;
	GLenum _usage;
public:
	VBO(GLenum usage = GL_STATIC_DRAW);
	VBO(const std::vector<T>& data, GLenum usage = GL_STATIC_DRAW);
	~VBO();

	VBO(const VBO&) = delete;
	VBO& operator=(const VBO&) = delete;

	VBO(VBO&& other) noexcept;

	VBO& operator=(VBO&& other) noexcept {
		if (this != &other) {
			if (_id != 0) glDeleteBuffers(1, &_id);
			glDeleteBuffers(1, &_id);
			_id = other._id;
			_usage = other._usage;
			other._id = 0;
		}
		return *this;
	}

	GLuint get_id() const;
	void bind() const;
	void unbind() const;

	void set_data(const std::vector<T>& data);
	// void remove_el(GLuint index);
	// void push_back(T element);
	// std::vector<T> get_data();

	std::string to_string() const;
};

template<typename T>
VBO<T>::VBO(GLenum usage)
	:_usage(usage)
{
	glGenBuffers(1, &_id);
}


template<typename T>
VBO<T>::VBO(const std::vector<T>& data, GLenum usage)
	:_usage(usage)
{
	glGenBuffers(1, &_id);
	set_data(data);
}



template<typename T>
VBO<T>::VBO(VBO&& other) noexcept
: _id(other._id), _usage(other._usage) {
	other._id = 0;
}



template<typename T>
VBO<T>::~VBO()
{
	if (_id != 0)
		glDeleteBuffers(1, &_id);
}


template<typename T>
GLuint VBO<T>::get_id() const
{
	return _id;
}


template<typename T>
void VBO<T>::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, _id);
}


template<typename T>
void VBO<T>::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


template<typename T>
void VBO<T>::set_data(const std::vector<T>& data)
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), _usage);
	unbind();
}

template<typename T>
std::string VBO<T>::to_string() const {
	std::string result;
	std::string usage;

	if (_usage == GL_STATIC_DRAW) {
		usage = "GL_STATIC_DRAW";
	}
	else if (_usage == GL_DYNAMIC_DRAW) {
		usage = "GL_DYNAMIC_DRAW";
	}

	result += "id: " + std::to_string(_id) + ", usage: " + usage;
	return result;
}
//
//
// template<typename T>
// void VBO<T>::remove_el(GLuint index)
// {
// 	GLint size;
// 	bind();
// 	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
//
// 	std::vector<T> data(size / sizeof(T));
// 	glGetBufferSubData(GL_ARRAY_BUFFER, 0, size, data.data());
//
//
// 	if (index < data.size()) {
// 		data.erase(data.begin() + index);
// 	}
//
// 	set_data(data);
//
// 	unbind();
// }
//
// template<typename T>
// void VBO<T>::push_back(T element)
// {
// 	GLint size;
// 	bind();
// 	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
//
// 	std::vector<T> data(size / sizeof(T));
// 	glGetBufferSubData(GL_ARRAY_BUFFER, 0, size, data.data());
//
//
// 	data.push_back(element);
//
// 	set_data(data);
//
// 	unbind();
// }
//
// template<typename T>
// inline std::vector<T> VBO<T>::get_data()
// {
// 	GLint size;
// 	bind();
// 	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
//
// 	std::vector<T> data(size / sizeof(T));
// 	glGetBufferSubData(GL_ARRAY_BUFFER, 0, size, data.data());
// 	unbind();
// 	return data;
// }
//
//
//
//
//
//
