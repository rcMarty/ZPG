//
// Created by rc_marty on 1.10.23.
//

#pragma once


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <string>


class Window {
private:
    std::shared_ptr<GLFWwindow> window;
    int width;
    int height;
    std::string title;
public:
    Window() = default;

    Window(int width, int height, const std::string &name);

    void init();

    void destroy();

    void run();

    void set_width(int width);

    void set_height(int height);

    void set_name(std::string name);

    int get_width();

    int get_height();

    std::string get_name();

    GLFWwindow *get_window();
};


