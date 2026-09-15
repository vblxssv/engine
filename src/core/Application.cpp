#include "Application.h"


Application::~Application()
{
    glfwTerminate();
}

Application::Application(const AppConfig& config)
    : screen(config.width, config.height, true),
    camera({ 0,0,0 }, { 0,0,-1 }, config.fov),
    limiter(config.fps_limit)
{
    if (!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW");

    if (!screen.isInited())
        throw std::runtime_error("Failed to create window");

    glfwMakeContextCurrent(screen.getWin());

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
        camera.rotate_horizontal(offsets.first);
        camera.rotate_vertical(offsets.second);
    });
}

void Application::run()
{
    resource_manager.add_resource("basic_shader", ShaderLoader::load(
          "mac_textured_3d/vertex.txt",
        "mac_textured_3d/fragment.txt"
    ));
    resource_manager.add_resource("texture", TextureLoader::load("oil.jpg"));

    auto  shader  = resource_manager.get<Shader>("basic_shader");
    auto  texture = resource_manager.get<Texture>("texture");

    Mesh mesh = MeshFactory::CreateTexturedTorus();


    auto projection = glm::perspective(glm::radians(camera.get_fov()), screen.aspect(), 0.1f, 100.0f);
    auto view = camera.get_view();

    mesh.bind();
    shader->use();
    shader->set_uniform_mat4("projection", projection);
    shader->set_uniform_int("u_Texture", 0);
    texture->activate(GL_TEXTURE0);
    texture->bind(GL_TEXTURE_2D);


    float rotationAngle = 0.0f;
    float rotationSpeed = 90.0f;
    while (!glfwWindowShouldClose(screen.getWin())) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        double dt = limiter.getDeltaTime();

        rotationAngle += rotationSpeed * (float)dt;
        if (rotationAngle > 360.0f) rotationAngle -= 360.0f;

        view = camera.get_view();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(rotationAngle), glm::vec3(0.5f, 1.0f, 0.0f));

        shader->set_uniform_mat4("view", view);
        shader->set_uniform_mat4("model", model);

        glDrawElements(GL_TRIANGLES, mesh.get_count(), GL_UNSIGNED_INT, 0);


        glfwSwapBuffers(screen.getWin());
        screen.update();
        camera.set_speed_on_keys(keyboard);
        camera.update_position(dt);
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
