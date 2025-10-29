#pragma once
#include <vector>
#include <cstddef> 
#include <type_traits>

//class AttributeLayout {
//public:
//  
//
//private:
//    std::vector<Attribute> _attributes;
//    size_t full_size = 0; // полный stride
//
//public:
//    AttributeLayout() = default;
//
//    template<typename T>
//    void push_back(size_t component_count = 1) {
//        static_assert(std::is_arithmetic_v<T>, "AttributeLayout only supports arithmetic types");
//        size_t type_size = sizeof(T);
//        _attributes.push_back({ full_size, component_count, type_size });
//        full_size += component_count * type_size;
//    }
//
//    const std::vector<Attribute>& get_attributes() const { return _attributes; }
//    size_t get_full_size() const { return full_size; }
//};


class AttributeLayout {
private:
    struct Attribute {
        size_t offset;
        size_t component_count;
        size_t component_size; 
        GLenum gl_type;
    };

    std::vector<Attribute> _attributes;
    size_t full_size = 0;

    bool _instanced;

public:


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
