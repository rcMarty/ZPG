//
// Created by rc_marty on 19.10.23.
//

#include "blinn_shader.h"


//void Shader::update_camera() {
//
//    use_shader();
//    set_variable("viewMatrix", camera->get_view_matrix());
//    set_variable("projectionMatrix", camera->get_projection_matrix());
//
//    //printf("[DEBUG] Camera updated in shader: %d\n", shader_id);
//
//}
Blinn_shader::Blinn_shader(std::shared_ptr<Camera> &camera_ptr, std::shared_ptr<Light> &light_ptr, const std::string &vertex_shader_path, const std::string &fragment_shader_path)
        : Base_shader(
        vertex_shader_path,
        fragment_shader_path) {

    printf("[DEBUG] Creating Phong shader\n");
    this->camera = camera_ptr;
    this->light = light_ptr;
}

void Blinn_shader::update_light() {
    use_shader();
    set_variable("lightColor", light->get_color());
    set_variable("lightPosition", light->get_position());
    //printf("[DEBUG] Light updated in shader: %f ,%f ,%f \n", light->get_position().x, light->get_position().y, light->get_position().z);
    //printf("[DEBUG] Light updated in shader: %d\n", shader_id);
}

void Blinn_shader::update_camera() {

    use_shader();
    set_variable("viewMatrix", camera->get_view_matrix());
    set_variable("projectionMatrix", camera->get_projection_matrix());
    set_variable("cameraPosition", camera->get_position());
    //printf("[DEBUG] Camera updated in shader: %d\n", shader_id);
}


void Blinn_shader::update() {
    use_shader();
    update_camera();
    update_light();
    //printf("[DEBUG] Light updated in shader: %d\n", shader_id);
    //update_light();
}

void Blinn_shader::set_camera(std::shared_ptr<Camera> camera) {
    this->camera = camera;
}

void Blinn_shader::set_light(std::shared_ptr<Light> light) {
    this->light = light;
}

