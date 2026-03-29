#include "EBO.h"


EBO::EBO(GLenum usage)
:_usage(usage), _count(0)
{
    glGenBuffers(1, &_id);
    set_data({});

}


EBO::EBO(const std::vector<GLuint>& data, GLenum usage)
:_usage(usage)
{
    glGenBuffers(1, &_id);
    _count = data.size();
    set_data(data);
}


EBO::~EBO()
{
    if (_id != 0)
        glDeleteBuffers(1, &_id);
}


EBO::EBO(EBO&& other) noexcept
    : _id(other._id), _count(other._count), _usage(other._usage) {
    other._id = 0;
    other._count = 0;
}


EBO& EBO::operator=(EBO&& other) noexcept {
    if (this != &other) {
        if (_id != 0) glDeleteBuffers(1, &_id);

        _id = other._id;
        _count = other._count;
        _usage = other._usage;

        other._id = 0;
        other._count = 0;
    }
    return *this;
}


void EBO::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
}


void EBO::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void EBO::set_data(const std::vector<GLuint>& data)
{
    bind();
    this->_count = data.size();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(GLuint), data.data(), _usage);
    unbind();
}


GLuint EBO::get_id() const {
    return _id;
}


GLuint EBO::get_count() const {
    return _count;
}
