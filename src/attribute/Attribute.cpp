#include "Attribute.h"

AttributeLine::AttributeLine()
{
	this->full_size = 0;
}

void AttributeLine::push_back(GLint size, GLenum type) 
{
	size_t size_type = get_type_size(type);
	size_t offset = 0;
	if (!_attributes.empty()) {
		offset = _attributes.back().offset + _attributes.back().size * get_type_size(_attributes.back().type);
	}
	
	_attributes.push_back(Attribute(size, type, offset));

	full_size += size_type * size;
}

size_t AttributeLine::get_type_size(GLenum type) const {
	switch (type) {
		case GL_FLOAT: return sizeof(GLfloat);
		case GL_INT:   return sizeof(GLint);
		case GL_UNSIGNED_INT: return sizeof(GLuint);
		default: return 0;
	}
}


