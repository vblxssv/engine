#include "Screen.h"

Screen::Screen(double w, double h, bool windowed) : width(w), height(h), windowed(windowed), pwindow(nullptr, glfwDestroyWindow)
{
    if (!glfwInit()) {
        throw std::runtime_error("GLFW initialization failed!");
    }

    #ifdef __APPLE__
        std::cout << "Works on apple!" << std::endl;
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

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
