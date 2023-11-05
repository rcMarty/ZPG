//
// Created by rc_marty on 3.11.23.
//

#include "light.h"

void Light::render(double delta_time) {
    if (has_object) {
        Renderable_object::render(delta_time);
    } else {
        Transformable_object::render(delta_time);
    }
}

void Light::set_transform_operations(std::shared_ptr<Transforms::Transform> transform_operations, bool static_tr) {
    Renderable_object::set_transform_operations(transform_operations, static_tr);
}

void Light::set_object(std::shared_ptr<Mesh> mesh, std::shared_ptr<Base_shader> shader, std::shared_ptr<Material> material) {
    this->mesh = mesh;
    this->shader = shader;
    this->material = material;
    this->has_object = true;
}