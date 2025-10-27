#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include <memory>
#include "../memory/VAO.h"



class Mesh {
protected:
	std::unique_ptr<VAO> vao;
	std::unique_ptr<VBO<GLfloat>> vbo;
	std::unique_ptr<VBO<GLuint>> instance_vbo;
	std::unique_ptr<EBO> ebo;
	

	void set_mesh(const std::vector<GLfloat>& vertexes,
		const std::vector<GLuint>& indexes, const AttributeLine& line);

public:
	Mesh();
	void use() { vao->bind(); }
	void unuse() { vao->unbind(); }
	void add_index(GLuint index);
	void remove_el(GLuint index);
	GLuint get_indices();
	decltype(auto) get_data_from_vbo();
};




