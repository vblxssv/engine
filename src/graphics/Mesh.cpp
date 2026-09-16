#include "Mesh.h"

Mesh::Mesh(const std::vector<float>& vertices,
           const std::vector<uint32_t>& indices,
           const AttributeLayout& layout)
{
    _vbo.setData(vertices);
    _ebo.setData(indices);

    _vao.addVertexBuffer(_vbo, layout);
    _vao.setIndexBuffer(_ebo);
}


void Mesh::bind() const
{
    _vao.bind();
}

void Mesh::unbind() const
{
    _vao.unbind();
}

GLuint Mesh::get_count() const
{
    return _ebo.count();
}




