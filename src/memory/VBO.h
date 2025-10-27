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
public:
	VBO(const std::vector<T>& data = {});
	~VBO();
	GLuint getId();
	void bind() const;
	void unbind() const;

	void setData(const std::vector<T>& data);

	void remove_el(GLuint index);
	
	void push_back(T element);

	std::vector<T> get_data();
};






template<typename T>
VBO<T>::VBO(const std::vector<T>& data)
{
	glGenBuffers(1, &_id);
	setData(data);
}

template<typename T>
VBO<T>::~VBO()
{
	glDeleteBuffers(1, &_id);
}

template<typename T>
GLuint VBO<T>::getId()
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
void VBO<T>::setData(const std::vector<T>& data)
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_DYNAMIC_DRAW);
	unbind();
}

template<typename T>
void VBO<T>::remove_el(GLuint index)
{
	GLint size;
	bind();
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

	std::vector<T> data(size / sizeof(T));
	glGetBufferSubData(GL_ARRAY_BUFFER, 0, size, data.data());


	if (index < data.size()) {
		data.erase(data.begin() + index);
	}

	setData(data);

	unbind();
}

template<typename T>
void VBO<T>::push_back(T element)
{
	GLint size;
	bind();
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

	std::vector<T> data(size / sizeof(T));
	glGetBufferSubData(GL_ARRAY_BUFFER, 0, size, data.data());


	data.push_back(element);

	setData(data);

	unbind();
}

template<typename T>
inline std::vector<T> VBO<T>::get_data()
{
	GLint size;
	bind();
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

	std::vector<T> data(size / sizeof(T));
	glGetBufferSubData(GL_ARRAY_BUFFER, 0, size, data.data());
	unbind();
	return data;
}






