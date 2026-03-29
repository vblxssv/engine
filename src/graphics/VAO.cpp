#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &_id);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &_id);
}

void VAO::bind() const
{
	glBindVertexArray(_id);
}

void VAO::unbind() const
{
	glBindVertexArray(0);
}

GLuint VAO::id() const
{
	return _id;
}
