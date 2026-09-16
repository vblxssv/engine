#include "Screen.h"

Screen::Screen(int w, int h) : width(w), height(h), pwindow(nullptr, glfwDestroyWindow)
{
    #ifdef __APPLE__
        std::cout << "Works on apple!" << std::endl;
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    pwindow.reset(glfwCreateWindow(width, height, "Screen", nullptr, nullptr));

    if (!pwindow) {
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
