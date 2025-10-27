#include "VAO.h"



VAO::VAO(const std::unique_ptr<VBO<GLfloat>>& vbo,
	const std::unique_ptr<VBO<GLuint>>& instance_vbo,
	const std::unique_ptr<EBO>& ebo,
	const AttributeLine& attribs)
{
	glGenVertexArrays(1, &_id);
	bind();
	vbo->bind();
	ebo->bind();

	auto attr = attribs.get_attributes();
	GLsizei stride = static_cast<GLsizei>(attribs.get_full_size());

	for (int i = 0, end = attr.size(); i < end; ++i) {
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(
			i,
			attr[i].size,
			attr[i].type,
			GL_FALSE,
			stride,
			reinterpret_cast<void*>(attr[i].offset)
		);
	}

	instance_vbo->bind();
	glVertexAttribIPointer(2, 1, GL_UNSIGNED_INT, sizeof(GLuint), (void*)0);
	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1);

	unbind();
}


VAO::~VAO()
{
	glDeleteVertexArrays(1, &_id);
}

void VAO::bind()
{
	glBindVertexArray(_id);
}

void VAO::unbind()
{
	glBindVertexArray(0);
}

