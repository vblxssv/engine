#pragma once
#include <GLFW/glfw3.h>
#include <memory>
#include <stdexcept>
#include <iostream>

class Screen {
private:
    int width, height;
    bool windowed;
    std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> pwindow;

public:
    Screen(int w, int h, bool windowed);

    float aspect() const {
        return static_cast<float>(width) / static_cast<float>(height);
    }

    GLFWwindow* getWin() const {
        return pwindow.get();
    }

    bool isInited() const {
        return pwindow != nullptr;
    }

    void update();
};