#include "EBO.h"

EBO::EBO()
{
    glGenBuffers(1, &_id);
    setData({}); 
}

EBO::EBO(const std::vector<GLuint>& data)
{
    glGenBuffers(1, &_id);
    indices = data.size();
    setData(data);
}

EBO::~EBO()
{
    glDeleteBuffers(1, &_id);
}

void EBO::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
}

void EBO::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::setData(const std::vector<GLuint>& data)
{
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(GLuint), data.data(), GL_STATIC_DRAW);
    unbind();
}

GLuint EBO::getId() const
{
    return _id;
}

GLuint EBO::get_indices()
{
    return indices;
}
