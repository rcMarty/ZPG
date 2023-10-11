//
// Created by rc_marty on 10.10.23.
//

#pragma once

#include <memory>
#include <glm/mat4x4.hpp>

class Shader; // dopredna deklarace (z duvodu krizoveho odkazu)
class Camera {
private:
    glm::vec3 eye = glm::vec3(0, 0, 0);
    glm::vec3 target = glm::vec3(0, 0, 1);
    glm::vec3 up = glm::vec3(0, 1, 0);
    float fov = 45.0f;
    float near = 0.1f;
    float far = 100.0f;

public:
    explicit Camera() = default;

    glm::mat4 getCamera();

    //todo observer camera

};