#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>


class VertexBuffer {
private:
	GLuint id_ = 0;
	GLenum usage_;
public:
	VertexBuffer(GLenum usage = GL_STATIC_DRAW);
	~VertexBuffer();

	VertexBuffer(const VertexBuffer&) = delete;
	VertexBuffer& operator=(const VertexBuffer&) = delete;
	VertexBuffer(VertexBuffer&& other) noexcept;
	VertexBuffer& operator=(VertexBuffer&& other) noexcept;

	GLuint id() const;
	void bind() const;
	void unbind() const;

	void setData(const void* data, size_t sizeInBytes);

	template<typename T>
	void setData(const std::vector<T>& data) {
		setData(data.data(), data.size() * sizeof(T));
	}
};

