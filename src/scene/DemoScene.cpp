#include "DemoScene.h"
#include "core/Screen.h"
#include "resources/ResourceManager.h"
#include "resources/ShaderLoader.h"
#include "resources/TextureLoader.h"
#include "graphics/MeshFactory.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

DemoScene::DemoScene(float fov)
    : camera_({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }, fov)
{
}

void DemoScene::onInit(SceneContext& context)
{
    context.resourceManager.add_resource("basic_shader", ShaderLoader::load(
        "mac_textured_3d/vertex.txt",
        "mac_textured_3d/fragment.txt"
    ));
    context.resourceManager.add_resource("texture", TextureLoader::load("oil.jpg"));

    shader_ = context.resourceManager.get<Shader>("basic_shader");
    texture_ = context.resourceManager.get<Texture>("texture");

    mesh_ = std::make_unique<Mesh>(MeshFactory::CreateTexturedTorus());
}

void DemoScene::onUpdate(float dt, SceneContext& context)
{
    rotationAngle_ += rotationSpeed_ * dt;
    if (rotationAngle_ > 360.0f) {
        rotationAngle_ -= 360.0f;
    }

    camera_.set_speed_on_keys(context.keyboard);
    camera_.update_position(dt);
}

void DemoScene::onRender(SceneContext& context)
{
    if (!mesh_ || !shader_ || !texture_) {
        return;
    }

    auto projection = glm::perspective(
        glm::radians(camera_.get_fov()),
        context.screen.aspect(),
        0.1f,
        100.0f
    );
    auto view = camera_.get_view();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(rotationAngle_), glm::vec3(0.5f, 1.0f, 0.0f));

    mesh_->bind();
    shader_->use();
    shader_->set_uniform_mat4("projection", projection);
    shader_->set_uniform_mat4("view", view);
    shader_->set_uniform_mat4("model", model);
    shader_->set_uniform_int("u_Texture", 0);

    texture_->activate(GL_TEXTURE0);
    texture_->bind(GL_TEXTURE_2D);

    glDrawElements(GL_TRIANGLES, mesh_->get_count(), GL_UNSIGNED_INT, nullptr);
}

void DemoScene::onMouseMove(double xOffset, double yOffset)
{
    camera_.rotate_horizontal(xOffset);
    camera_.rotate_vertical(yOffset);
}
