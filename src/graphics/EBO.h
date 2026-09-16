#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>


class IndexBuffer {
private:
	GLuint id_ = 0;
	GLuint count_ = 0;
	GLenum usage_;
public:
	IndexBuffer(GLenum usage = GL_STATIC_DRAW);
	IndexBuffer(const std::vector<uint32_t>& data, GLenum usage = GL_STATIC_DRAW);
	~IndexBuffer();

	IndexBuffer(const IndexBuffer&) = delete;
	IndexBuffer& operator=(const IndexBuffer&) = delete;

	IndexBuffer(IndexBuffer&& other) noexcept;
	IndexBuffer& operator=(IndexBuffer&& other) noexcept;

	void bind() const;
	void unbind() const;

	void setData(const uint32_t* data, size_t count);

	void setData(const std::vector<uint32_t>& data) {
		setData(data.data(), data.size());
	}

	uint32_t id() const;
	uint32_t count() const;
};
