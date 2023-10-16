//
// Created by rc_marty on 19.10.23.
//

#ifndef ZPG_LAMBERT_SHADER_H
#define ZPG_LAMBERT_SHADER_H

#include "base_shader.h"
#include "../object/light/light.h"

class Lambert_shader : public Base_shader {
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

    Lambert_shader(std::shared_ptr<Camera> &camera_ptr, std::shared_ptr<Light> &light, const std::string &vertex_shader_path, const std::string &fragment_shader_path);

    virtual ~Lambert_shader() = default;

    virtual void update() override;

    void set_camera(std::shared_ptr<Camera> camera);

    void set_light(std::shared_ptr<Light> light);


};


#endif //ZPG_LAMBERT_SHADER_H
