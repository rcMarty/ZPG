//
// Created by rc_marty on 11.11.23.
//

#include "sky_dome.h"

Sky_dome::Sky_dome(const std::string &path, std::shared_ptr<Shader_wrapper> shader, std::shared_ptr<Camera> camera) {
    this->camera = camera;
    this->shader = shader;

    this->mesh = std::make_shared<Mesh>(path);
    mesh->init();

    this->shader->use_shader();
    this->shader->set_variable("view", glm::mat4(glm::mat3(this->camera->get_view_matrix())));
    this->shader->set_variable("projection", this->camera->get_projection_matrix());
}

void Sky_dome::render() {
    glDepthMask(GL_FALSE);
    this->shader->use_shader();
    this->mesh->render();
    glDepthMask(GL_TRUE);
}