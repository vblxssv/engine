#pragma once
#include <vector>
#include <glad/glad.h>


class AttributeLayout {
private:
    struct Attribute {
        GLuint index;
        GLint component_count;
        GLenum gl_type;
        GLboolean normalized;
        GLsizei offset;
    };

    std::vector<Attribute> _attributes;
    GLsizei _stride = 0;

public:
    AttributeLayout() = default;

    template<typename T>
    void add_attribute(GLuint index, GLint count, bool normalized = false) {
        _attributes.push_back({
            index,
            count,
            get_gl_type<T>(),
            static_cast<GLboolean>(normalized ? GL_TRUE : GL_FALSE),
            _stride
        });
        _stride += static_cast<GLsizei>(sizeof(T) * count);
    }

    void apply() const {
        for (const auto& attr : _attributes) {
            glEnableVertexAttribArray(attr.index);
            glVertexAttribPointer(
                attr.index,
                attr.component_count,
                attr.gl_type,
                attr.normalized,
                _stride, // Общий шаг всей структуры
                (const void*)(uintptr_t)attr.offset // Смещение внутри структуры
            );
        }
    }

    GLsizei stride() const { return _stride; }

private:
    template<typename T>
    static constexpr GLenum get_gl_type() {
        if constexpr (std::is_same_v<T, float>)    return GL_FLOAT;
        if constexpr (std::is_same_v<T, int32_t>)  return GL_INT;
        if constexpr (std::is_same_v<T, uint32_t>) return GL_UNSIGNED_INT;
        if constexpr (std::is_same_v<T, int8_t>)   return GL_BYTE;
        if constexpr (std::is_same_v<T, uint8_t>)  return GL_UNSIGNED_BYTE;
        if constexpr (std::is_same_v<T, int16_t>)  return GL_SHORT;
        if constexpr (std::is_same_v<T, uint16_t>) return GL_UNSIGNED_SHORT;
        if constexpr (std::is_same_v<T, double>)   return GL_DOUBLE;
        return 0;
    }
};
