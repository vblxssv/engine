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


//class VAO {
//private:
//	GLuint _id;
//public:
//	VAO(const std::unique_ptr<VBO<GLfloat>>& vbo,
//		const std::unique_ptr<VBO<GLuint>>& instance_vbo, 
//		const std::unique_ptr<EBO>& ebo, 
//		const AttributeLine& attribs);
//
//	~VAO();
//	void bind();
//	void unbind();
//	GLuint getId() {
//		return _id;
//	}
//};

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
    void link_vbo(const VBO<T>& vbo, const AttributeLayout& layout) const;

    void link_ebo(const EBO& ebo) const;
};




template <typename T>
void VAO::link_vbo(const VBO<T>& vbo, const AttributeLayout& layout) const {
    bind();
    vbo.bind();
    const auto& attributes = layout.get_attributes();
    for (GLuint i = 0; i < attributes.size(); ++i) {
        const auto& attr = attributes[i];

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(
            i,                          // индекс атрибута
            static_cast<GLint>(attr.component_count), // количество компонентов
            GL_FLOAT,                    // тип данных компонента (тут float, можно расширить)
            GL_FALSE,                     // нормализация
            static_cast<GLsizei>(layout.get_full_size()), // stride
            reinterpret_cast<void*>(attr.offset)        // смещение
        );
    }

    vbo.unbind();
    unbind();
}




