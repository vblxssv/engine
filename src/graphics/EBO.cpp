#include "EBO.h"

IndexBuffer::IndexBuffer(GLenum usage)
    : id_(0), count_(0), usage_(usage)
{
    glGenBuffers(1, &id_);
}

IndexBuffer::IndexBuffer(const std::vector<uint32_t>& data, GLenum usage)
    : id_(0), count_(0), usage_(usage)
{
    glGenBuffers(1, &id_);
    setData(data);
}

IndexBuffer::~IndexBuffer()
{
    if (id_ != 0) {
        glDeleteBuffers(1, &id_);
    }
}

IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
    : id_(other.id_), count_(other.count_), usage_(other.usage_)
{
    other.id_ = 0;
    other.count_ = 0;
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
{
    if (this != &other) {
        if (id_ != 0) {
            glDeleteBuffers(1, &id_);
        }
        id_ = other.id_;
        count_ = other.count_;
        usage_ = other.usage_;

        other.id_ = 0;
        other.count_ = 0;
    }
    return *this;
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::setData(const uint32_t* data, size_t count)
{
    bind();
    count_ = static_cast<GLuint>(count);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(count * sizeof(uint32_t)), data, usage_);
}

uint32_t IndexBuffer::id() const
{
    return id_;
}

uint32_t IndexBuffer::count() const
{
    return count_;
}
