#include "VAO.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &id_);
}

VertexArray::~VertexArray()
{
	if (id_ != 0) {
		glDeleteVertexArrays(1, &id_);
	}
}

VertexArray::VertexArray(VertexArray&& other) noexcept
	: id_(other.id_)
{
	other.id_ = 0;
}

VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
{
	if (this != &other) {
		if (id_ != 0) {
			glDeleteVertexArrays(1, &id_);
		}
		id_ = other.id_;
		other.id_ = 0;
	}
	return *this;
}

void VertexArray::bind() const
{
	glBindVertexArray(id_);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}

GLuint VertexArray::id() const
{
	return id_;
}

void VertexArray::addVertexBuffer(const VertexBuffer& vbo, const AttributeLayout& layout)
{
	bind();
	vbo.bind();
	layout.apply();
	vbo.unbind();
	unbind();
}

void VertexArray::setIndexBuffer(const IndexBuffer& ebo)
{
	bind();
	ebo.bind();
	unbind();
}
