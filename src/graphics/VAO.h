#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "graphics/VBO.h"
#include "graphics/EBO.h"
#include "graphics/Attribute.h"


class VertexArray {
private:
    GLuint id_ = 0;
public:
    VertexArray();
    ~VertexArray();

    // Move-only
    VertexArray(const VertexArray& other) = delete;
    VertexArray& operator=(const VertexArray& other) = delete;
    VertexArray(VertexArray&& other) noexcept;
    VertexArray& operator=(VertexArray&& other) noexcept;

    void bind() const;
    void unbind() const;
    GLuint id() const;

    //Linking
    void addVertexBuffer(const VertexBuffer& vbo, const AttributeLayout& layout);

    void setIndexBuffer(const IndexBuffer& ebo);
};

using VAO = VertexArray;
