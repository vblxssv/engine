#include "Application.h"
#include "scene/DemoScene.h"


Application::Application(const AppConfig& config)
    : glfw(),
      screen(config.width, config.height),
      limiter(config.fps_limit),
      default_fov_(config.fov)
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD");

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    glEnable(GL_DEPTH_TEST);

    glfwSetWindowUserPointer(screen.getWin(), this);
    glfwSetInputMode(screen.getWin(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetKeyCallback(screen.getWin(), key_callback);
    glfwSetCursorPosCallback(screen.getWin(), mouse_callback);

    event_manager.subscribe<KeyPressEvent>([this](const KeyPressEvent& e) {
        int key = e.getKey();
        int action = e.getAction();
        PRESSED_EN type = (action == GLFW_PRESS || action == GLFW_REPEAT) ? PRESSED_EN::PRESSED : PRESSED_EN::RELEASED;
        keyboard.update_key(key, type);
    });

    event_manager.subscribe<MouseEvent>([this](const MouseEvent& e) {
        std::pair<double, double> mouse_pos = { e.get_xpos(), e.get_ypos() };
        auto offsets = cursor.get_offset(mouse_pos.first, mouse_pos.second);
        cursor.update(mouse_pos.first, mouse_pos.second);
        if (current_scene_) {
            current_scene_->onMouseMove(offsets.first, offsets.second);
        }
    });
}

void Application::setScene(std::unique_ptr<Scene> scene)
{
    current_scene_ = std::move(scene);
}

void Application::run()
{
    if (!current_scene_) {
        current_scene_ = std::make_unique<DemoScene>(default_fov_);
    }

    SceneContext context{ screen, keyboard, cursor, resource_manager, event_manager };
    current_scene_->onInit(context);

    while (!glfwWindowShouldClose(screen.getWin())) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        double dt = limiter.getDeltaTime();

        current_scene_->onUpdate(static_cast<float>(dt), context);
        current_scene_->onRender(context);

        glfwSwapBuffers(screen.getWin());
        screen.update();
        limiter.wait();
    }
}


void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    app->event_manager.emit(KeyPressEvent(key, scancode, action, mods));
}

void Application::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    app->event_manager.emit(MouseEvent(xpos, ypos));
}
