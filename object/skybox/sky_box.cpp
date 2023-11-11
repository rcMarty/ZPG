//
// Created by rc_marty on 10.11.23.
//

#include "sky_box.h"
#include "../transform/transform.h"


Sky_box::Sky_box(files path, std::shared_ptr<Shader_wrapper> shader, std::shared_ptr<Camera> camera) {
    this->camera = camera;
    this->mesh = std::make_shared<Mesh>(path.path + "/" + path.object);
    mesh->init();
    this->textures = std::make_shared<Texture>(path.path, path, CUBEMAP, GL_TEXTURE_CUBE_MAP);
    this->shader = shader;

    this->shader->use_shader();
    this->shader->set_variable("skybox", 0);
    this->shader->set_variable("view", glm::mat4(glm::mat3(this->camera->get_view_matrix())));
    this->shader->set_variable("projection", this->camera->get_projection_matrix());

}

void Sky_box::render() {
    glDepthMask(GL_FALSE);
    this->shader->use_shader();
    this->textures->bind(0);
    this->mesh->render();
    glDepthMask(GL_TRUE);
}

void Sky_box::update() {

    this->shader->use_shader();
    this->shader->set_variable("view", glm::mat4(glm::mat3(this->camera->get_view_matrix())));
    this->shader->set_variable("projection", this->camera->get_projection_matrix());

}
