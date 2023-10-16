//
// Created by rc_marty on 29.9.23.
//

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "stdio.h"
#include "stdlib.h"
#include "../input_handle/input_handler.h"
#include "../render/scene.h"
#include <memory>


class Engine {
protected:
    //shared pointer na okno
    std::shared_ptr<GLFWwindow> window;
    std::shared_ptr<input::Input_handler> input_handler;
    std::shared_ptr<Scene> scene;
    //shared pointer na shader
    //shared pointer na kameru
    //shared pointer na světlo
    //shared pointer na renderer




public:
    void init();

    void run();

    void destroy();

    ~Engine() {
        destroy();
    };

};


