//
// Created by rc_marty on 10.10.23.
//

#include "camera.h"
#include "../shader/shader.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"


void Camera::attach_shader(std::shared_ptr<Shader> &shader) {
    this->shaders.push_back(shader);
}

void Camera::notify_shaders() {
    for (auto &shader: shaders) {
        //printf("[DEBUG] Notifying shader\n");
        shader->update_camera();
    }
}

glm::mat4x4 Camera::get_projection_matrix() {
    return glm::perspective(glm::radians(fov), 4.0f / 3.0f, near, far);
    //return glm::mat4x4(1.0f);
}

glm::mat4x4 Camera::get_view_matrix() {
    //printf("[DEBUG] eye: %f, %f, %f\n", eye.x, eye.y, eye.z);
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

void Camera::go_forward(float distance) {
    //move forward in direction of target but dont calculate y component
    glm::vec3 target_no_y = glm::vec3(target.x, 0, target.z);
    this->eye += glm::normalize(target_no_y) * distance;
    //printf("[DEBUG] go_forward eye: %f, %f, %f\n", eye.x, eye.y, eye.z);
}

void Camera::go_sideways(float distance) {
    this->eye += glm::cross(this->target, this->up) * distance;
    //printf("[DEBUG] go_sideways eye: %f, %f, %f\n", eye.x, eye.y, eye.z);
}

void Camera::look_sideways(float angle) {
    this->target = glm::rotate(this->target, glm::radians(angle), this->up);
    //printf("[DEBUG] look_sideways eye: %f, %f, %f\n", eye.x, eye.y, eye.z);
}

void Camera::look_up(float angle) {
    this->target = glm::rotate(this->target, glm::radians(angle), glm::cross(this->target, this->up));
    //printf("[DEBUG] look_up eye: %f, %f, %f\n", eye.x, eye.y, eye.z);

}

void Camera::go_vertical(float distance) {
    this->eye += this->up * distance;
    //printf("[DEBUG] go_vertical eye: %f, %f, %f\n", eye.x, eye.y, eye.z);
}






