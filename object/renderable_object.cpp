//
// Created by rc_marty on 30.9.23.
//

#include "renderable_object.h"

#include <utility>
#include <stdexcept>

Renderable_object::Renderable_object(Mesh mesh, std::shared_ptr<Base_shader> shader) {
    this->mesh = std::make_shared<Mesh>(mesh);
    this->shader = shader;
}

void Renderable_object::init() {
    if (mesh == nullptr)
        throw std::runtime_error("Mesh is not set");
    if (shader == nullptr)
        throw std::runtime_error("Shader is not set");
    if (material == nullptr)
        throw std::runtime_error("Material is not set");


    mesh->init();
}

void Renderable_object::render() {
    shader->use_shader();
    if (move != nullptr)
        shader->set_variable("modelMatrix", move(Matrix));

    else if (animated) {
        Matrix = transform_operations->get_matrix(Matrix);
        shader->set_variable("modelMatrix", Matrix);
    } else
        shader->set_variable("modelMatrix", Matrix);

    material->set_variables(shader);

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

Renderable_object Renderable_object::set_material(std::shared_ptr<Material> material) {
    this->material = material;
    return *this;
}

Renderable_object Renderable_object::set_move(std::function<glm::mat4(glm::mat4)> transformations) {
    this->move = transformations;
    return *this;
}



