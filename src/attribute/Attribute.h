#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>


class AttributeLine {
	class Attribute {
	public:
		GLenum type;
		GLint size;          
		size_t offset;
	public:
		Attribute(GLint size, GLenum type, size_t offset) {
			this->size = size;
			this->offset = offset;
			this->type = type;
		}
	};

private:
	std::vector<Attribute> _attributes;
	size_t full_size;
public:
	AttributeLine();

	std::vector<Attribute> get_attributes() const {
		return _attributes;
	}

	size_t get_full_size() const {
		return full_size;
	}

	void push_back(GLint size, GLenum type);

private:
	size_t get_type_size(GLenum type) const;
};