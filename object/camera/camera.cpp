//
// Created by rc_marty on 10.10.23.
//

#include "camera.h"
#include "../../shader/base_shader.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"


void Camera::attach(std::shared_ptr<Observer> observer) {
    this->observers.push_back(observer);
}

void Camera::notify() {
    for (auto &observer: observers) {
        //printf("[DEBUG] Notifying shader\n");
        observer->update();
    }
}

glm::mat4x4 Camera::get_projection_matrix() {
    return glm::perspective(glm::radians(fov), aspect_ratio, near, far);
    //return glm::mat4x4(1.0f);
}

glm::mat4x4 Camera::get_view_matrix() {
    //printf("[DEBUG] eye: %f, %f, %f\n", eye.x, eye.y, eye.z);
    return glm::lookAt(eye, eye + target, up);
    //return glm::mat4x4(1.0f);
}

glm::vec3 Camera::get_position() {
    return this->eye;
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
    this->notify();
    //printf("[DEBUG] go_forward eye: %f, %f, %f\n", eye.x, eye.y, eye.z);
}

void Camera::go_sideways(float distance) {
    this->eye += glm::cross(this->target, this->up) * distance;
    this->notify();
    //printf("[DEBUG] go_sideways eye: %f, %f, %f\n", eye.x, eye.y, eye.z);
}

void Camera::look_sideways(float angle) {
    this->target = glm::rotate(this->target, glm::radians(angle), this->up);
    this->notify();
    //printf("[DEBUG] look_sideways eye: %f, %f, %f\n", eye.x, eye.y, eye.z);
}

void Camera::look_up(float angle) {
    this->target = glm::rotate(this->target, glm::radians(angle), glm::cross(this->target, this->up));
    this->notify();
    //printf("[DEBUG] look_up eye: %f, %f, %f\n", eye.x, eye.y, eye.z);
}

void Camera::go_vertical(float distance) {
    this->eye += this->up * distance;
    this->notify();
    //printf("[DEBUG] go_vertical eye: %f, %f, %f\n", eye.x, eye.y, eye.z);
}

void Camera::look_mouse(double data_x, double data_y) {
    double x = data_x - last_x;
    double y = last_y - data_y;

    last_x = data_x;
    last_y = data_y;

    x *= mouse_sensitivity;
    y *= mouse_sensitivity;

    yaw += x;
    pitch += y;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->target = glm::normalize(front);


    this->notify();
}

void Camera::set_aspect_ratio(float aspect_ratio) {
    this->aspect_ratio = aspect_ratio;
    this->fov = 90.0f / this->aspect_ratio;
    printf("[DEBUG] camera notifying aspect_ratio: %f\n", this->aspect_ratio);
    this->notify();
}