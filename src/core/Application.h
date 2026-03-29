#include <time.h>
#include <math.h>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "resources/ResourceManager.h"
#include "resources/ShaderLoader.h"
#include "resources/TextureLoader.h"
#include "resources/Resource.h"

#include "graphics/Camera.h"
#include "graphics/Attribute.h"
#include "graphics/VAO.h"
#include "graphics/SSBO.h"

#include "input/Cursor.h"
#include "input/Event.h"
#include "input/Keyboard.h"

#include "core/Screen.h"
#include "core/FrameLimiter.h"
#include "graphics/Mesh.h"
#include "graphics/MeshFactory.h"






class Application {
private:
	Camera camera;
	Cursor cursor;
	Keyboard keyboard;
	Screen screen;
	FrameLimiter limiter;
	ResourceManager resource_manager;
	EventManager event_manager;
public:
	Application(int width, int height);

	~Application();

	Camera& get_camera() {
		return camera;
	}

	EventManager& get_event_manager() {
		return event_manager;
	}

	bool init();

	void mac_run();
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);