//
// Created by rc_marty on 25.10.23.
//

#pragma once

#include <glm/vec4.hpp>
#include "../shader/base_shader.h"
#include <functional>


class Material {

private:
    glm::vec4 color = {0.3f, 0.6f, 0.9f, 1.0f};
    glm::vec4 ambient = {0.1f, 0.1f, 0.1f, 1.0f};
    float specularStrength = 0.75f;
    int specularPower = 32;

public:

    Material() = default;

    Material(glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, float shininess);

    Material set_color(glm::vec4 color);

    Material set_ambient(glm::vec4 ambient);

    Material set_specular_strength(float specularStrength);

    Material set_specular_power(int specularPower);

    void set_variables(std::shared_ptr<Base_shader> shader);

};


