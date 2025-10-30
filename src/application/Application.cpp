#include "Application.h"
#include "../resourceLoader/ShaderLoader.h"
#include "../resourceLoader/TextureLoader.h"
#include "../memory/VAO.h"

Application::~Application()
{
    glfwTerminate();
}

Application::Application(int width, int height)
    : screen(width, height, true),
    camera({ 0,0,3 }, { 0,0,-1 }, 90.f),
    limiter(144)
{

}

bool Application::init()
{
    if (!glfwInit()) {
        std::cerr << "Ошибка инициализации GLFW!" << std::endl;
        return false; 
    }

    if (!screen.isInited()) return false;

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Ошибка инициализации GLAD!" << std::endl;
        return false;
    }

    glEnable(GL_DEPTH_TEST);

    glfwSetWindowUserPointer(screen.getWin(), this);
    glfwSetInputMode(screen.getWin(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetKeyCallback(screen.getWin(), key_callback);
    glfwSetCursorPosCallback(screen.getWin(), mouse_callback);

    event_manager.subscribe<KeyPressEvent>([this](const KeyPressEvent& e) { /// кнопка
        int key = e.getKey();
        int action = e.getAction();
        PRESSED_EN type = action == GLFW_PRESS || action == GLFW_REPEAT ? PRESSED_EN::PRESSED : PRESSED_EN::RELEASED;
        keyboard.update_key(key, type);
    });

    event_manager.subscribe<MouseEvent>([this](const MouseEvent& e) { /// мышь 
            std::pair<double, double> mouse_pos = { e.get_xpos() ,e.get_ypos() };
            auto offsets = cursor.get_offset(mouse_pos.first, mouse_pos.second);
            cursor.update(mouse_pos.first, mouse_pos.second);
            camera.rotate_horizontal(offsets.first);
            camera.rotate_vertical(offsets.second);
        }
    );

    return true;
}



void Application::test_run()
{
  
    resource_manager.add_resource("standart_shader", ShaderLoader::load(
        "instanced_texture/vertex.txt",
        "instanced_texture/fragment.txt"
    ));
    resource_manager.add_resource("kaben", TextureLoader::load("kaban.png"));

    std::shared_ptr<Texture> texture = std::static_pointer_cast<Texture>(resource_manager.get_resource("kaben"));
    std::shared_ptr<Shader> shader = std::static_pointer_cast<Shader>(resource_manager.get_resource("standart_shader"));


    shader->use();
    texture->activate();
    texture->bind();
    shader->set_uniform_int("texture1", 0);


    std::vector<float> vertices = {
        // Front face (z = +1)
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

        // Back face (z = -1)
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

        // Left face (x = -1)
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

        // Right face (x = +1)
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

         // Top face (y = +1)
         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,

         // Bottom face (y = -1)
         -0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
          0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
          0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         -0.5f, -0.5f,  0.5f,  1.0f, 0.0f
    };
    std::vector<unsigned int> indices = {
        0, 1, 2,  2, 3, 0,
        4, 5, 6,  6, 7, 4,
        8, 9,10, 10,11, 8,
       12,13,14, 14,15,12,
       16,17,18, 18,19,16,
       20,21,22, 22,23,20
    };

    int side = 30;
    float spacing = 1.f;
    std::vector<glm::mat4> models;

    for (int x = 0; x < side; ++x) {
        for (int z = 0; z < side; ++z) {
            // стены по краям
            if (x == 0 || z == 0 || x == side - 1 || z == side - 1) {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x * spacing, 0.f, z * spacing));
                models.push_back(model);
            }
            else {
                // внутри лабиринта рандомно ставим стены с 30% вероятностью
                if ((rand() % 100) < 30) {
                    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x * spacing, 0.f, z * spacing));
                    models.push_back(model);
                }
            }
        }
    }

    std::vector<GLuint> indices_vbo(side * side);
    for (int i = 0; i < side * side; ++i)
        indices_vbo[i] = i;

    shader->use();

    glm::mat4 projection = glm::perspective(glm::radians(camera.get_fov()), screen.aspect(), 0.1f, 100.0f);

    shader->set_uniform_mat4("view", camera.get_view());
    shader->set_uniform_mat4("projection", projection);



    VBO<GLfloat> vbo;
    vbo.set_data(vertices);

    EBO ebo;
    ebo.setData(indices);

    VBO<GLuint> instance_vbo;
    instance_vbo.set_data(indices_vbo);

    AttributeLayout atr;
    atr.add_attribute<GLfloat>(3);
    atr.add_attribute<GLfloat>(2);

    VAO vao;

    vao.link_vertex_vbo(vbo, atr);
    vao.link_instance_vbo(instance_vbo, 2);
    vao.link_ebo(ebo);
    vao.bind();

    SSBO ssbo;
    ssbo.set_data(models);

    double rotation_speed = 50.0;
    double angle = 0.0;

    while (!glfwWindowShouldClose(screen.getWin())) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        double dt = limiter.getDeltaTime();
        

        glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, side * side);

        shader->set_uniform_mat4("view", camera.get_view());

        glfwSwapBuffers(screen.getWin());
        screen.update();
        camera.set_speed_on_keys(keyboard);
        camera.update_position(dt);
        limiter.wait();
    }


}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    KeyPressEvent kpe(key, scancode, action, mods);
    auto events = app->get_event_manager();
    events.emit(kpe);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    MouseEvent me(xpos, ypos);
    auto events = app->get_event_manager();
    events.emit(me);
}
