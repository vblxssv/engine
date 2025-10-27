#include "Screen.h"

Screen::Screen(double w, double h, bool windowed) : width(w), height(h), windowed(windowed), pwindow(nullptr, glfwDestroyWindow)
{
    if (!glfwInit()) {
        throw std::runtime_error("GLFW initialization failed!");
    }

    glfwWindowHint(GLFW_RESIZABLE, windowed ? GL_TRUE : GL_FALSE);

    pwindow.reset(glfwCreateWindow(width, height, "Screen", nullptr, nullptr));

    if (!pwindow) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(pwindow.get());
}

void Screen::update()
{
    if (pwindow) {
        glfwPollEvents();
    }
}
