//
// Created by rc_marty on 30.9.23.
//

#include "renderable_object.h"

#include <utility>
#include <stdexcept>

void Renderable_object::init() {


    if (shader == nullptr)
        throw std::runtime_error("Shader is not set");
    if (mesh == nullptr)
        throw std::runtime_error("Mesh is not set");
    if (material == nullptr)
        throw std::runtime_error("Material is not set");


    if (has_texture) {
        shader->use_shader();
        shader->set_variable("textureDiffuse", 0); //glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0); // set it manually
        shader->set_variable("textureSpecular", 1);
        shader->set_variable("hasTexture", 1);
        printf("[DEBUG] has texture\n");

    } else {
        shader->set_variable("hasTexture", 0);
        printf("[DEBUG] has NOT texture\n");
    }

    mesh->init();

}

void Renderable_object::render(double delta_t) {

    shader->use_shader();

    if (has_texture) {
        shader->set_variable("hasTexture", 1);
    } else {
        shader->set_variable("hasTexture", 0);
    }

    if (transform_operations) {
//        transform_operations->tick(delta_t);
//        auto mat = transform_operations->get_matrix(Matrix);
//        //printf("[DEBUG] Renderable_object: %s,Matrix:\n%s\n", this->name.c_str(), transform_operations->print_matrix(mat).c_str());
        Transformable_object::render(delta_t);
        shader->set_variable("modelMatrix", Matrix_transformed);
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


Renderable_object Renderable_object::set_mesh(const Mesh &input_mesh) {
    this->mesh = std::make_shared<Mesh>(input_mesh);
    return *this;
}


Renderable_object Renderable_object::set_material(std::shared_ptr<Material> material) {
    this->material = material;
    return *this;
}

Renderable_object Renderable_object::set_shader(std::shared_ptr<Base_shader> shader) {
    this->shader = shader;
    return *this;
}

Renderable_object Renderable_object::set_transform_operations(std::shared_ptr<Transforms::Transform> transform_operations, bool static_tr) {
    Transformable_object::set_transform_operations(transform_operations, static_tr);
    return *this;
}

Renderable_object Renderable_object::set_has_texture(bool has_texture) {
    this->has_texture = has_texture;
    return *this;
}




