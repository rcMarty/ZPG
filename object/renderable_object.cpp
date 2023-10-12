//
// Created by rc_marty on 30.9.23.
//

#include "renderable_object.h"

#include <utility>

Renderable_object::Renderable_object(Mesh mesh, std::shared_ptr<Shader> &shader) {
    this->mesh = std::make_shared<Mesh>(mesh);
    this->shader = shader;
}

void Renderable_object::init() {
    mesh->init();
}

void Renderable_object::render() {
    shader->use_shader();
    shader->set_variable("modelMatrix", Matrix);
    mesh->render();

}

Renderable_object Renderable_object::set_name(std::string render_name) {
    this->name = std::move(render_name);
    return *this;
}

Renderable_object Renderable_object::set_shader(Shader input_shader) {
    this->shader = std::make_shared<Shader>(input_shader);
    return *this;
}

Renderable_object Renderable_object::set_mesh(const Mesh &input_mesh) {
    this->mesh = std::make_shared<Mesh>(input_mesh);
    return *this;
}

Renderable_object
Renderable_object::set_transform_operations(std::shared_ptr<Transforms::Transform> transform_operations) {
    this->transform_operations = transform_operations;
    Matrix = transform_operations->get_matrix(Matrix);
    return *this;
}


