#include "VAO.h"



VAO::VAO()
{
	glGenVertexArrays(1, &_id);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &_id);
}

void VAO::bind() const noexcept
{
	glBindVertexArray(_id);
}

void VAO::unbind() const noexcept
{
	glBindVertexArray(0);
}

void VAO::link_ebo(const EBO& ebo) const
{
	bind();       
	ebo.bind();   
	unbind();
}



