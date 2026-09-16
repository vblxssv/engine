#pragma once

class Screen;
class Keyboard;
class Cursor;
class ResourceManager;
class EventManager;

struct SceneContext {
    Screen& screen;
    Keyboard& keyboard;
    Cursor& cursor;
    ResourceManager& resourceManager;
    EventManager& eventManager;
};

class Scene {
public:
    virtual ~Scene() = default;

    virtual void onInit(SceneContext& context) { (void)context; }
    virtual void onUpdate(float dt, SceneContext& context) { (void)dt; (void)context; }
    virtual void onRender(SceneContext& context) = 0;
    virtual void onMouseMove(double xOffset, double yOffset) { (void)xOffset; (void)yOffset; }
};
