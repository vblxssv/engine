#pragma once
#include <string>
#include "../geometry/geometry.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Actor {
private:
	glm::vec3 _position;
	glm::vec3 _rotation;
	glm::vec3 _scale;

	glm::mat4 _model_cache;
	bool is_changed;

	static GLuint counter;
	static std::vector<GLuint> free_indices;

	GLuint index;

	void update_matrix();
public:
	Actor();

	~Actor();

	void move(const glm::vec3& delta);   //is_changed = true

	void rotate(const glm::vec3& delta); //is_changed = true

	void scale(const glm::vec3& delta);  //is_changed = true

	bool has_changed();

	glm::mat4 get_model();               //is_changed = false


	std::vector<GLuint> get_free() {
		return free_indices;
	}
	GLuint get_id() {
		return index;
	}
};







