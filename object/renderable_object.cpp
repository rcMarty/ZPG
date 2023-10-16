//
// Created by rc_marty on 30.9.23.
//

#include "renderable_object.h"

#include <utility>

Renderable_object::Renderable_object(Mesh mesh, std::shared_ptr<Base_shader> &shader) {
    this->mesh = std::make_shared<Mesh>(mesh);
    this->shader = shader;
}

void Renderable_object::init() {
    mesh->init();
}

void Renderable_object::render() {
    shader->use_shader();

    if (animated)
        Matrix = transform_operations->get_matrix(Matrix);


    shader->set_variable("modelMatrix", Matrix);
    shader->update();
    mesh->render();


}

Renderable_object Renderable_object::set_name(std::string render_name) {
    this->name = std::move(render_name);
    return *this;
}

Renderable_object Renderable_object::set_shader(std::shared_ptr<Base_shader> input_shader) {
    this->shader = input_shader;
    return *this;
}

Renderable_object Renderable_object::set_mesh(const Mesh &input_mesh) {
    this->mesh = std::make_shared<Mesh>(input_mesh);
    return *this;
}

Renderable_object
Renderable_object::set_transform_operations(std::shared_ptr<Transforms::Transform> transform_operations, bool animated) {
    this->transform_operations = transform_operations;
    this->animated = animated;
    Matrix = transform_operations->get_matrix(Matrix);
    return *this;
}


