//
// Created by rc_marty on 10.10.23.
//

#pragma once

#include <memory>
#include <glm/mat4x4.hpp>
#include <vector>

class Shader; //forward declaration

class Camera {
private:

    std::vector<std::shared_ptr<Shader>> shaders;

    glm::vec3 eye = glm::vec3(0, 0, 3);
    glm::vec3 target = glm::vec3(0, 0, -1);
    glm::vec3 up = glm::vec3(0, 1, 0);
    float fov = 90.0f;
    float near = 0.1f;
    float far = 100.0f;

public:
    explicit Camera() = default;

    Camera(glm::vec3 eye, glm::vec3 target, glm::vec3 up, float fov, float near, float far);

    void set_eye(glm::vec3 eye);

    void set_target(glm::vec3 target);

    void set_up(glm::vec3 up);

    void set_fov(float fov);

    void set_near(float near);

    void set_far(float far);


    glm::mat4x4 get_projection_matrix();

    glm::mat4x4 get_view_matrix();


    void attach_shader(std::shared_ptr<Shader> shader);

    void notify_shaders();

};