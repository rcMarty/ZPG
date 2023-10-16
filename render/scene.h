//
// Created by rc_marty on 30.9.23.
//

#pragma once


#include <vector>
#include "../object/renderable_object.h"
#include "../input_handle/input_handler.h"

class Scene {
private:

    std::vector<Renderable_object> objects;
    std::shared_ptr<input::Input_handler> input_handler;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<GLFWwindow> window;


    void set_scene();

    void set_inputs();


public:
    Scene() = delete;

    Scene(std::shared_ptr<input::Input_handler> input_handler, std::shared_ptr<GLFWwindow> glfWwindow) : input_handler(input_handler), window(glfWwindow) {};


    Scene add_object(const Renderable_object &object);

    Renderable_object find_object(const std::string &name);

    void init();

    void render();


};

