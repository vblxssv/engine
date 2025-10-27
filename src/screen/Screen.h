#pragma once
#include <GLFW/glfw3.h>
#include <memory>
#include <stdexcept>
#include <iostream>

class Screen {
private:
    double width, height;
    bool windowed;
    std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> pwindow;

public:
    Screen(double w, double h, bool windowed);

    float aspect() const {
        return width / height;
    }

    GLFWwindow* getWin() const {
        return pwindow.get();
    }

    bool isInited() const {
        return pwindow != nullptr;
    }

    void update();
};