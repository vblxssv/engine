#include "Camera.h"

Camera::Camera(const glm::vec3& pos, const glm::vec3& forward, float fov) : forward(forward), position(pos), fov(fov), speed(0, 0 ,0)
{
	yaw = glm::degrees(atan2(forward.z, forward.x));  
	pitch = glm::degrees(asin(forward.y));  
    acceleration = 5;
    damping = 0.91;
}

void Camera::move(const glm::vec3& delta)
{
	position += delta;
}

void Camera::rotate_yaw(float delta_yaw)
{
    yaw += delta_yaw;
    yaw = glm::mod(yaw, 360.f);
    if (yaw < 0.f) {
        yaw += 360.f;
    }

    update_forward();
}

void Camera::rotate_pitch(float delta_pitch)
{
    pitch += delta_pitch;

    pitch = glm::clamp(pitch, -89.9f, 89.9f);

    update_forward();
}

glm::mat4 Camera::get_view()
{
    return glm::lookAt(position ,position + forward, { 0.f, 1.f, 0.f });
}

float Camera::get_fov()
{
    return fov;
}

glm::vec3 Camera::get_forward()
{
    return forward;
}

void Camera::set_speed_on_keys(const Keyboard& keyboard)
{
    bool _forward = keyboard.get_state(key_forward) == PRESSED;
    bool _back = keyboard.get_state(key_back) == PRESSED;
    bool _right = keyboard.get_state(key_right) == PRESSED;
    bool _left = keyboard.get_state(key_left) == PRESSED;

    if (_forward && _back) {
        _forward = _back = false;
    }
    if (_left && _right) {
        _left = _right = false;
    }
    
    
    
    if (_forward || _back || _right || _left) {
        glm::vec3 forward_horiz = glm::normalize(glm::vec3(forward.x, 0.f, forward.z));
        glm::vec3 right = glm::normalize(glm::cross(forward_horiz, glm::vec3(0, 1, 0)));

        glm::vec3 direction(0.f);
        if (_forward) direction += forward_horiz;
        if (_back)    direction -= forward_horiz;
        if (_right)   direction += right;
        if (_left)    direction -= right;

        if (glm::length(direction) > 0)
            direction = glm::normalize(direction);

        speed = acceleration * direction;
    }
}



void Camera::update_position(float dt)
{
    move(speed * dt);
    std::cout << glm::length(speed) << std::endl;
    //float damping_factor = std::pow(damping, dt);
    speed *= damping;
 

    

    if (glm::length(speed) < 0.001f)
        speed = glm::vec3(0.0f);
}

void Camera::rotate_horizontal(double x_offset)
{
    rotate_yaw(x_offset * horizontal_speed);
}

void Camera::rotate_vertical(double y_offset)
{
    rotate_pitch(-y_offset * vertical_speed);
}

void Camera::update_forward()
{
    float yaw_radians = glm::radians(yaw);
    float pitch_radians = glm::radians(pitch);

    forward.x = cos(pitch_radians) * cos(yaw_radians);
    forward.y = sin(pitch_radians);
    forward.z = cos(pitch_radians) * sin(yaw_radians);


    forward = glm::normalize(forward);
}

void Camera::update_view()
{
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(get_view()));
}
