//
// Created by rc_marty on 2.11.23.
//

#include "spot_light.h"

void Spot_light::set_direction(glm::vec3 direction) {
    this->direction = direction;
}

void Spot_light::set_cut_off(float cut_off) {
    this->cut_off = cut_off;
}

void Spot_light::set_outer_cut_off(float outer_cut_off) {
    this->outer_cut_off = outer_cut_off;
}

void Spot_light::render(double delta_time) {
    if (!camera)
        this->Point_light::render(delta_time);
}

void Spot_light::update() {
    if (camera) {
        direction = camera->get_target();
        light_position = camera->get_position();
    }
}

Spot_light Spot_light::set_transform_operations(std::shared_ptr<Transforms::Transform> transform_operations, bool static_tr) {
    Transformable_object::set_transform_operations(transform_operations, static_tr);
    return *this;
}

std::unordered_map<std::string, std::variant<glm::mat4, glm::vec4, glm::vec3, float, int>> Spot_light::get_variables() {
    //struct lightSource {
    //    vec3 position;
    //    vec4 color;
    //    vec3 attenuation;
    //
    //
    //    vec3 direction;
    //    float cutOff;
    //    float outerCutOff;
    //    int type;
    //};
    std::unordered_map<std::string, std::variant<glm::mat4, glm::vec4, glm::vec3, float, int>> variables;
    variables["type"] = static_cast<int>(Light_type::SPOT_LIGHT);
    variables["color"] = light_color;
    variables["position"] = light_position;
    variables["attenuation"] = light_attenuation;
    variables["modelMatrix"] = Matrix_transformed;
    variables["direction"] = direction;
    variables["cutOff"] = cut_off;
    variables["outerCutOff"] = outer_cut_off;
    return variables;
}

Spot_light Spot_light::set_object(std::shared_ptr<Mesh> mesh, std::shared_ptr<Base_shader> shader, std::shared_ptr<Material> material) {
    Light::set_object(mesh, shader, material);
    return *this;
}

void Spot_light::set_camera(std::shared_ptr<Camera> observer) {
    this->camera = observer;
}
