#pragma once
#include <iostream>
#include <algorithm>
#include <glad/glad.h>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>


#include "input/Keyboard.h"



class Camera {
private:
	glm::vec3 position;
	glm::vec3 forward;

	float acceleration, damping;
	glm::vec3 speed;
	float horizontal_speed = 0.15, vertical_speed = 0.15;

	float yaw, pitch, fov;

	GLuint view_loc;	
public:
	Camera(const glm::vec3& pos, const glm::vec3& forward, float fov);

	void move(const glm::vec3& delta);

	void rotate_yaw(float delta_yaw);

	void rotate_pitch(float delta_pitch);

	glm::mat4 get_view();

	float get_fov();

	glm::vec3 get_forward();

	void set_speed_on_keys(const Keyboard& keyboard);
	
	void update_position(float dt);

	void rotate_horizontal(double x_offset);

	void rotate_vertical(double y_offset);
private:
	void update_forward();

	void update_view();

	int key_forward = GLFW_KEY_W;
	int key_back = GLFW_KEY_S;
	int key_left = GLFW_KEY_A;
	int key_right = GLFW_KEY_D;
};










