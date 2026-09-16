#include "VBO.h"

VertexBuffer::VertexBuffer(GLenum usage)
    : id_(0), usage_(usage)
{
    glGenBuffers(1, &id_);
}

VertexBuffer::~VertexBuffer()
{
    if (id_ != 0) {
        glDeleteBuffers(1, &id_);
    }
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
    : id_(other.id_), usage_(other.usage_)
{
    other.id_ = 0;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
{
    if (this != &other) {
        if (id_ != 0) {
            glDeleteBuffers(1, &id_);
        }
        id_ = other.id_;
        usage_ = other.usage_;
        other.id_ = 0;
    }
    return *this;
}

GLuint VertexBuffer::id() const
{
    return id_;
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, id_);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::setData(const void* data, size_t sizeInBytes)
{
    bind();
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeInBytes), data, usage_);
    unbind();
}
