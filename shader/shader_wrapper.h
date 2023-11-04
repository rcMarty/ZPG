//
// Created by rc_marty on 19.10.23.
//
#pragma once

#include "base_shader.h"
#include "../object/light/light_wrapper.h"

class Shader_wrapper : public Base_shader {

protected:
    std::shared_ptr<Camera> camera;

    void update_camera();

    std::shared_ptr<Light_wrapper> light;

    void update_light();

public:
    Shader_wrapper(std::shared_ptr<Camera> camera_ptr, std::shared_ptr<Light_wrapper> light, const std::string &vertex_shader_path, const std::string &fragment_shader_path);

    virtual ~Shader_wrapper() = default;

    virtual void update() override;

    void set_camera(std::shared_ptr<Camera> camera);

    void set_light(std::shared_ptr<Light_wrapper> light);
};
