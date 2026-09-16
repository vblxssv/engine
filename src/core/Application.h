#pragma once
#include <ctime>
#include <cmath>
#include <memory>
#include <stdexcept>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/GlfwContext.h"
#include "resources/ResourceManager.h"
#include "input/Cursor.h"
#include "input/Event.h"
#include "input/Keyboard.h"
#include "core/Screen.h"
#include "core/FrameLimiter.h"
#include "core/AppConfig.h"
#include "scene/Scene.h"


class Application {
private:
	GlfwContext		glfw;
	Screen			screen;
	ResourceManager	resource_manager;
	Cursor			cursor;
	Keyboard		keyboard;
	FrameLimiter	limiter;
	EventManager	event_manager;
	std::unique_ptr<Scene> current_scene_;
	float			default_fov_ = 90.0f;

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
public:
	Application(const AppConfig& config = {});

	~Application() = default;

	EventManager& get_event_manager() {
		return event_manager;
	}

	void setScene(std::unique_ptr<Scene> scene);

	void run();
};
