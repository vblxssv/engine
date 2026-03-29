#include "Mesh.h"

Mesh::Mesh(const std::vector<float>& vertices,
           const std::vector<uint32_t>& indices,
           const AttributeLayout& layout)
{
    _vao.bind();
    _vbo.set_data(vertices); // Тут он забиндился и сразу разбиндился (плохо)
    _vbo.bind();           // <--- ВОЗВРАЩАЕМ БИНД для настройки!


    _ebo.set_data(indices);  // EBO можно оставить как есть, он биндится к VAO иначе

    layout.apply();          // Теперь glVertexAttribPointer видит наш VBO

    _vao.unbind();
    _vbo.unbind();
}


void Mesh::bind() const
{
    _vao.bind();
    _vbo.bind();
    _ebo.bind();
}

void Mesh::unbind() const
{
    _vao.unbind();
    _vbo.unbind();
    _ebo.unbind();
}

GLuint Mesh::get_count() const
{
    return _ebo.get_count();
}




