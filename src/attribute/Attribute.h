#pragma once
#include <vector>
#include <cstddef> 
#include <type_traits>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class AttributeLayout {
private:
    struct Attribute {
        GLintptr offset;
        GLint component_count;
        GLsizei component_size; 
        GLenum gl_type;
    };

    std::vector<Attribute> _attributes;
    size_t _stride = 0;
public:
    AttributeLayout() = default;

    template<typename T>
    void add_attribute(GLint component_count)
    {
        Attribute a;
        a.offset = _stride;
        a.component_count = component_count;
        a.component_size = sizeof(T);
        a.gl_type = gl_type<T>();
        _stride += sizeof(T) * component_count;
        _attributes.push_back(a);
    }

    size_t stride() const;

    void print_attrs() const;

    const std::vector<Attribute>& get_attributes() const;
private:
    template<typename T>
    constexpr GLenum gl_type() {
        if constexpr (std::is_same_v<T, float>) return GL_FLOAT;
        else if constexpr (std::is_same_v<T, double>) return GL_DOUBLE;
        else if constexpr (std::is_same_v<T, int8_t>) return GL_BYTE;
        else if constexpr (std::is_same_v<T, uint8_t>) return GL_UNSIGNED_BYTE;
        else if constexpr (std::is_same_v<T, int16_t>) return GL_SHORT;
        else if constexpr (std::is_same_v<T, uint16_t>) return GL_UNSIGNED_SHORT;
        else if constexpr (std::is_same_v<T, int32_t>) return GL_INT;
        else if constexpr (std::is_same_v<T, uint32_t>) return GL_UNSIGNED_INT;
        else if constexpr (std::is_same_v<T, bool>) return GL_BOOL;
        else if constexpr (std::is_same_v<T, int64_t>) return GL_INT64_ARB;
        else if constexpr (std::is_same_v<T, uint64_t>) return GL_UNSIGNED_INT64_ARB;
        else static_assert(sizeof(T) == 0, "Unsupported type for OpenGL attribute");
    }
};
