#include "SSBO.h"

void SSBO::bind()
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, _id);
}

void SSBO::unbind()
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

SSBO::SSBO()
{
	glGenBuffers(1, &_id);
	bind();
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, _id); 
	unbind();
}

SSBO::~SSBO()
{
	glDeleteBuffers(1, &_id);
}

void SSBO::set_data(const std::vector<glm::mat4>& matrices)
{
	bind();
	glBufferData(GL_SHADER_STORAGE_BUFFER, matrices.size() * sizeof(glm::mat4), matrices.data(), GL_DYNAMIC_DRAW);
	unbind();
}

void SSBO::update_single_matrix(GLuint index, const glm::mat4& matrix)
{
	bind();
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, index * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(matrix));
	unbind();
}





