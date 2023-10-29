//
// Created by rc_marty on 1.10.23.
//

#include "window.h"

Window::Window(int width, int height, const std::string &name) {
    this->width = width;
    this->height = height;
    this->title = name;
}


void Window::init() {
    this->window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(width, height, title.c_str(), NULL, NULL), glfwDestroyWindow);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window.get());
    glfwSwapInterval(1);

    int width, height;
    glfwGetFramebufferSize(this->window.get(), &width, &height);
    glViewport(0, 0, width, height);

}

GLFWwindow *Window::get_window() {
    return window.get();
}
