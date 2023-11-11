//
// Created by rc_marty on 30.9.23.
//

#pragma once


#include <vector>
#include "../object/renderable_object.h"
#include "../input_handle/input_handler.h"
#include "../object/light/light_wrapper.h"
#include "../object/skybox/sky_box.h"

class Scene {
private:

    std::vector<std::shared_ptr<Renderable_object>> objects;
    std::vector<std::shared_ptr<Light_wrapper>> lights;
    std::shared_ptr<input::Input_handler> input_handler;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Sky_box> sky_box;
    std::shared_ptr<GLFWwindow> window;

    void set_inputs();


public:
    Scene() = delete;

    Scene(std::shared_ptr<input::Input_handler> input_handler, std::shared_ptr<GLFWwindow> glfWwindow) : input_handler(input_handler), window(glfWwindow) {};

    Scene add_object(std::shared_ptr<Renderable_object> object);

    Scene add_object(std::shared_ptr<Light_wrapper> object);

    Scene set_skybox(std::shared_ptr<Sky_box> object);

    std::shared_ptr<Renderable_object> find_object(const std::string &name);

    void init();

    void render(double delta_time);

    void set_debug_scene();

    void set_phong_scene();

    void set_rotation_scene();

    void set_check_phong_scene();
};

