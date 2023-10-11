//
// Created by rc_marty on 10.10.23.
//

#include "camera.h"
#include "../shader/shader.h"
#include "glm/gtc/matrix_transform.hpp"


void Camera::attach_shader(std::shared_ptr<Shader> shader) {
    this->shaders.push_back(shader);
}

void Camera::notify_shaders() {
    for (auto &shader: shaders) {
        shader->update_camera();
    }
}

glm::mat4x4 Camera::get_projection_matrix() {
    return glm::perspective(glm::radians(fov), 4.0f / 3.0f, near, far);
    //return glm::mat4x4(1.0f);
}

glm::mat4x4 Camera::get_view_matrix() {
    return glm::lookAt(eye, eye + target, up);
    //return glm::mat4x4(1.0f);
}

Camera::Camera(glm::vec3 eye, glm::vec3 target, glm::vec3 up, float fov, float near, float far) {
    this->eye = eye;
    this->target = target;
    this->up = up;
    this->fov = fov;
    this->near = near;
    this->far = far;
}

