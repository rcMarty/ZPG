//
// Created by rc_marty on 19.10.23.
//

#include "shader_wrapper.h"


Shader_wrapper::Shader_wrapper(std::shared_ptr<Camera> camera_ptr, std::shared_ptr<Light_wrapper> light_ptr, const std::string &vertex_shader_path, const std::string &fragment_shader_path)
        : Base_shader(
        vertex_shader_path,
        fragment_shader_path) {

    printf("[DEBUG] Creating Phong shader\n");
    this->camera = camera_ptr;
    this->light = light_ptr;
}

void Shader_wrapper::update_light() {

    use_shader();
    light->set_variables(*this);
//    set_variable("lightColor", light->get_color());
//    set_variable("lightPosition", light->get_position());
//    set_variable("lightAttenuation", light->get_attenuation());
}

void Shader_wrapper::update_camera() {

    use_shader();
    set_variable("viewMatrix", camera->get_view_matrix());
    set_variable("projectionMatrix", camera->get_projection_matrix());
    set_variable("cameraPosition", camera->get_position());
    //printf("[DEBUG] Camera updated in shader: %d\n", shader_id);
}


void Shader_wrapper::update() {
    use_shader();
    update_camera();
    update_light();
    //printf("[DEBUG] Light updated in shader: %d\n", shader_id);
    //update_light();
}

void Shader_wrapper::set_camera(std::shared_ptr<Camera> camera) {
    this->camera = camera;
}

void Shader_wrapper::set_light(std::shared_ptr<Light_wrapper> light) {
    this->light = light;
}

