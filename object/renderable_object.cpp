//
// Created by rc_marty on 30.9.23.
//

#include "renderable_object.h"

Renderable_object::Renderable_object(Mesh mesh, Shader shader) {
    this->mesh = std::make_shared<Mesh>(mesh);
    this->shader = std::make_shared<Shader>(shader);
}

void Renderable_object::init() {
    mesh->init();
}

void Renderable_object::render() {
    mesh->render();
    shader->use_shader();
    //glUniformMatrix3x4fv(mesh, 1, GL_FALSE, Matrix); //todo pajdíče

}

Renderable_object Renderable_object::set_name(std::string name) {
    this->name = name;
    return *this;
}

Renderable_object Renderable_object::set_shader(Shader shader) {
    this->shader = std::make_shared<Shader>(shader);
    return *this;
}

Renderable_object Renderable_object::set_mesh(Mesh mesh) {
    this->mesh = std::make_shared<Mesh>(mesh);
    return *this;
}

