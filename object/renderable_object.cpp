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


