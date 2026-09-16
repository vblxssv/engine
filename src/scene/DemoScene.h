#pragma once
#include "scene/Scene.h"
#include "graphics/Mesh.h"
#include "graphics/Camera.h"
#include "resources/Resource.h"
#include <memory>

class DemoScene : public Scene {
private:
    std::unique_ptr<Mesh> mesh_;
    std::shared_ptr<Shader> shader_;
    std::shared_ptr<Texture> texture_;
    Camera camera_;
    float rotationAngle_ = 0.0f;
    float rotationSpeed_ = 90.0f;

public:
    DemoScene(float fov = 90.0f);
    ~DemoScene() override = default;

    void onInit(SceneContext& context) override;
    void onUpdate(float dt, SceneContext& context) override;
    void onRender(SceneContext& context) override;
    void onMouseMove(double xOffset, double yOffset) override;

    Camera& getCamera() { return camera_; }
};
