//
// Created by rc_marty on 19.10.23.
//
#pragma once

#include "base_shader.h"
#include "../object/light/light.h"

class Blinn_shader : public Base_shader {
//    uniform mat4 model;
//    uniform mat4 view;
//    uniform mat4 projection;
//    uniform vec4 lightColor;
//    uniform vec4 lightPosition;


protected:
    std::shared_ptr<Camera> camera;

    void update_camera();

    std::shared_ptr<Light> light;

    void update_light();

public:

    Blinn_shader(std::shared_ptr<Camera> &camera_ptr, std::shared_ptr<Light> &light, const std::string &vertex_shader_path, const std::string &fragment_shader_path);

    virtual ~Blinn_shader() = default;

    virtual void update() override;

    void set_camera(std::shared_ptr<Camera> camera);

    void set_light(std::shared_ptr<Light> light);


};


