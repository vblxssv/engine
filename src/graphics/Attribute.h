#pragma once
#include <vector>
#include <cstdint>
#include <type_traits>
#include <glad/glad.h>


class AttributeLayout {
public:
    struct Attribute {
        GLuint index;
        GLint component_count;
        GLenum gl_type;
        GLboolean normalized;
        bool is_integer;
        GLsizei offset;
        GLuint divisor;
    };

private:
    std::vector<Attribute> _attributes;
    GLsizei _stride = 0;

public:
    AttributeLayout() = default;

    template<typename T>
    void add_attribute(GLuint index, GLint count, bool normalized = false, GLuint divisor = 0) {
        constexpr bool is_int = std::is_integral_v<T>;
        _attributes.push_back({
            index,
            count,
            get_gl_type<T>(),
            static_cast<GLboolean>(normalized ? GL_TRUE : GL_FALSE),
            is_int,
            _stride,
            divisor
        });
        _stride += static_cast<GLsizei>(sizeof(T) * count);
    }

    void add_matrix4_attribute(GLuint start_index, GLuint divisor = 1) {
        for (GLuint i = 0; i < 4; ++i) {
            add_attribute<float>(start_index + i, 4, false, divisor);
        }
    }

    void apply() const {
        for (const auto& attr : _attributes) {
            glEnableVertexAttribArray(attr.index);

            if (attr.is_integer && !attr.normalized) {
                glVertexAttribIPointer(
                    attr.index,
                    attr.component_count,
                    attr.gl_type,
                    _stride,
                    reinterpret_cast<const void*>(static_cast<uintptr_t>(attr.offset))
                );
            } else {
                glVertexAttribPointer(
                    attr.index,
                    attr.component_count,
                    attr.gl_type,
                    attr.normalized,
                    _stride,
                    reinterpret_cast<const void*>(static_cast<uintptr_t>(attr.offset))
                );
            }

            if (attr.divisor > 0) {
                glVertexAttribDivisor(attr.index, attr.divisor);
            }
        }
    }

    GLsizei stride() const { return _stride; }
    const std::vector<Attribute>& get_attributes() const { return _attributes; }

private:
    template<typename>
    static constexpr bool always_false_v = false;

    template<typename T>
    static constexpr GLenum get_gl_type() {
        if constexpr (std::is_same_v<T, float>)         return GL_FLOAT;
        else if constexpr (std::is_same_v<T, int32_t>)  return GL_INT;
        else if constexpr (std::is_same_v<T, uint32_t>) return GL_UNSIGNED_INT;
        else if constexpr (std::is_same_v<T, int8_t>)   return GL_BYTE;
        else if constexpr (std::is_same_v<T, uint8_t>)  return GL_UNSIGNED_BYTE;
        else if constexpr (std::is_same_v<T, int16_t>)  return GL_SHORT;
        else if constexpr (std::is_same_v<T, uint16_t>) return GL_UNSIGNED_SHORT;
        else if constexpr (std::is_same_v<T, double>)   return GL_DOUBLE;
        else {
            static_assert(always_false_v<T>, "Unsupported attribute type");
            return 0;
        }
    }
};
