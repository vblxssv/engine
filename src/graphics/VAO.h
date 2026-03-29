#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>


#include "graphics/VBO.h"
#include "graphics/EBO.h"
#include "graphics/Attribute.h"


class VAO {
private:
    GLuint _id;
public:
    VAO();
    ~VAO();
    void bind() const;
    void unbind() const;
    GLuint id() const;
};



//
//
// template <typename T>
// void VAO::link_vertex_vbo(const VBO<T>& vbo, const AttributeLayout& layout) const {
//     bind();
//     vbo.bind();
//     const auto& attributes = layout.get_attributes();
//     for (GLuint i = 0; i < attributes.size(); ++i) {
//         const auto& attr = attributes[i];
//
//         glEnableVertexAttribArray(i);
//         glVertexAttribPointer(
//             i,                          // ������ ��������
//             static_cast<GLint>(attr.component_count), // ���������� �����������
//             attr.gl_type,                    // ��� ������ ����������
//             GL_FALSE,                     // ������������
//             static_cast<GLsizei>(layout.stride()), // stride
//             reinterpret_cast<void*>(attr.offset)        // ��������
//         );
//     }
//     vbo.unbind();
//     unbind();
// }
//
// template<typename T>
// void VAO::link_instance_vbo(const VBO<T>& instance_vbo, GLuint attribute_index) const
// {
//     static_assert(std::is_same_v<T, GLuint>, "Instance VBO must be of type GLuint");
//
//     bind();
//     instance_vbo.bind();
//     glEnableVertexAttribArray(attribute_index);
//     glVertexAttribIPointer(
//         attribute_index,     // ������ ��������
//         1,                // ���������� ����������� (������ ���� uint)
//         GL_UNSIGNED_INT,  // ��� ������
//         sizeof(T),        // stride ����� ����������
//         reinterpret_cast<void*>(0) // �������� ������ ������
//     );
//     glVertexAttribDivisor(attribute_index, 1); // ����������: ���� ������� �� ���� instance
//
//     instance_vbo.unbind();
//     unbind();
// }





