#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include "VBO.h"
#include "EBO.h"
#include "../attribute/Attribute.h"

class VAO {
private:
    GLuint _id;
public:
    VAO();
    ~VAO();
    void bind() const noexcept;
    void unbind() const noexcept;
    GLuint id() const noexcept;

    template <typename T>
    void link_vertex_vbo(const VBO<T>& vbo, const AttributeLayout& layout) const;

    template <typename T>
    void link_instance_vbo(const VBO<T>& instance_vbo, GLuint attribute_index) const;

    void link_ebo(const EBO& ebo) const;
};




template <typename T>
void VAO::link_vertex_vbo(const VBO<T>& vbo, const AttributeLayout& layout) const {
    bind();
    vbo.bind();
    const auto& attributes = layout.get_attributes();    
    for (GLuint i = 0; i < attributes.size(); ++i) {
        const auto& attr = attributes[i];

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(
            i,                          // индекс атрибута
            static_cast<GLint>(attr.component_count), // количество компонентов
            attr.gl_type,                    // тип данных компонента 
            GL_FALSE,                     // нормализация
            static_cast<GLsizei>(layout.stride()), // stride
            reinterpret_cast<void*>(attr.offset)        // смещение
        );
    }
    vbo.unbind();
    unbind();
}

template<typename T>
void VAO::link_instance_vbo(const VBO<T>& instance_vbo, GLuint attribute_index) const
{
    static_assert(std::is_same_v<T, GLuint>, "Instance VBO must be of type GLuint");

    bind();
    instance_vbo.bind();
    glEnableVertexAttribArray(attribute_index);
    glVertexAttribIPointer(
        attribute_index,     // индекс атрибута
        1,                // количество компонентов (только один uint)
        GL_UNSIGNED_INT,  // тип данных
        sizeof(T),        // stride между элементами
        reinterpret_cast<void*>(0) // смещение внутри буфера
    );
    glVertexAttribDivisor(attribute_index, 1); // инстансинг: один атрибут на один instance

    instance_vbo.unbind();
    unbind();
}





