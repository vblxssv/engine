#pragma once
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"


class Mesh {
private:
    VAO _vao;
    VBO<GLfloat> _vbo;
    EBO _ebo;
public:
    Mesh(const std::vector<float>& vertices,
        const std::vector<uint32_t>& indices,
        const AttributeLayout& layout);

    void bind() const;
    void unbind() const;

    GLuint get_count() const;
};

