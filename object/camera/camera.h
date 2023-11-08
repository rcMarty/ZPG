//
// Created by rc_marty on 10.10.23.
//

#pragma once

#include <memory>
#include <glm/mat4x4.hpp>
#include <vector>
#include "../../utils/observer.h"
#include "../../utils/subject.h"

class Observer_shader; //forward declaration

class Camera {
private:

    std::vector<std::shared_ptr<Observer>> observers;

    glm::vec3 eye = glm::vec3(0, 0, 3);
    glm::vec3 target = glm::vec3(0, 0, -1);
    glm::vec3 up = glm::vec3(0, 1, 0);
    float fov = 45.0f;
    float near = 0.1f;
    float far = 100.0f;

    float aspect_ratio = 4.0f / 3.0f;

    float mouse_sensitivity = 0.1f;
    float yaw = -90.0f;
    float pitch = 0.0f;

    double last_x, last_y;

public:
    explicit Camera() = default;

    Camera(glm::vec3 eye, glm::vec3 target, glm::vec3 up, float fov, float near, float far);

    void go_forward(float distance);

    void go_sideways(float distance);

    void go_vertical(float distance);

    void look_sideways(float angle);

    void look_up(float angle);

    void look_mouse(double x, double y);

    void set_aspect_ratio(float aspect_ratio);

    glm::mat4x4 get_projection_matrix();

    glm::mat4x4 get_view_matrix();

    glm::vec3 get_position();

    glm::vec3 get_target();

    void attach(std::shared_ptr<Observer> observer);

    void notify();

};