#include "Object3d.h"


GLuint Actor::counter = 0;
std::vector<GLuint> Actor::free_indices = {};

void Actor::update_matrix()
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, _position);
	model = glm::rotate(model, glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));  // Поворот вокруг оси X
	model = glm::rotate(model, glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));  // Поворот вокруг оси Y
	model = glm::rotate(model, glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));  // Поворот вокруг оси Z
	model = glm::scale(model, _scale);
	_model_cache = model;
	is_changed = true;
}

Actor::Actor()
{
	_position = { 0, 0, 0 };
	_rotation = { 0, 0, 0 };
	_scale = { 1, 1, 1 };
	_model_cache = glm::mat4(1.f);
	is_changed = true;

	if (free_indices.empty()) {
		index = counter++;
	}
	else {
		index = free_indices.front();
		free_indices.erase(free_indices.begin());
	}
	update_matrix();
}

Actor::~Actor()
{
	free_indices.push_back(index);
}

void Actor::move(const glm::vec3& delta)
{
	_position += delta;
	update_matrix();
	
}

void Actor::rotate(const glm::vec3& delta)
{
	_rotation += delta;
	update_matrix();
}

void Actor::scale(const glm::vec3& delta)
{
	_scale = delta;
	update_matrix();
}

bool Actor::has_changed()
{
	return is_changed;
}

glm::mat4 Actor::get_model()
{
	is_changed = false;
	return _model_cache;
}










