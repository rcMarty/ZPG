//
// Created by rc_marty on 30.9.23.
//

#pragma once

#include <vector>
#include "../object/renderable_object.h"
#include "../input_handle/input_handler.h"
#include "../object/light/light_wrapper.h"
#include "../object/skybox/sky_box.h"
#include "../shader/shader_wrapper.h"

class Scene {
private:

    std::vector<std::shared_ptr<Renderable_object>> objects;
    std::vector<std::shared_ptr<Shader_wrapper>> shaders;
    std::vector<std::shared_ptr<Light_wrapper>> lights;
    std::shared_ptr<input::Input_handler> input_handler;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Sky_box> sky_box;
    std::shared_ptr<GLFWwindow> window;

    bool is_active = false;


    void set_inputs();

public:

    Scene() = delete;

    Scene(std::shared_ptr<input::Input_handler> input_handler, std::shared_ptr<GLFWwindow> glfWwindow) : input_handler(input_handler), window(glfWwindow) {};

    Scene add_object(std::shared_ptr<Renderable_object> object);

    Scene add_object(std::shared_ptr<Light_wrapper> object);

    Scene set_skybox(std::shared_ptr<Sky_box> object);

    std::shared_ptr<Renderable_object> find_object(const std::string &name);

    void set_active();

    void set_inactive();

    std::shared_ptr<Renderable_object> get_object_at(int x, int y);

    void clicked_pixel(std::function<void(std::shared_ptr<Renderable_object> obj)> callback);

    void get_clicked_point(glm::vec3 &point_3d, glm::vec3 &point_screen);

    void init();

    void render(double delta_time);

    void set_debug_scene();

    void set_phong_scene();

    void set_rotation_scene();

    void set_check_phong_scene();
};

