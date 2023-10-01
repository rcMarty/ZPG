//
// Created by rc_marty on 30.9.23.
//

#include "renderable_object.h"

Renderable_object::Renderable_object(Mesh mesh, Shader_ID shader) {
    this->mesh = std::make_shared<Mesh>(mesh);
    this->shader = shader;
}

void Renderable_object::init() {
    mesh->init();
}

void Renderable_object::render() {
    mesh->render();
    glUseProgram(shader);

}

Renderable_object Renderable_object::set_name(std::string name) {
    this->name = name;
    return *this;
}

Renderable_object Renderable_object::set_shader(Shader_ID shader) {
    this->shader = shader;
    return *this;
}

Renderable_object Renderable_object::set_mesh(Mesh mesh) {
    this->mesh = std::make_shared<Mesh>(mesh);
    return *this;
}

