//
// Created by rc_marty on 2.11.23.
//

#ifndef ZPG_DIRECTIONAL_LIGHT_H
#define ZPG_DIRECTIONAL_LIGHT_H
#pragma once

#include "light.h"
#include <variant>
#include <map>

class Directional_light : public Light {
private:
    glm::vec3 direction;
public:
    Directional_light(glm::vec4 color, glm::vec3 direction) : Light(color), direction(direction) {};

    std::unordered_map<std::string, std::variant<glm::mat4, glm::vec4, glm::vec3, float, int>> get_variables() override;

    Directional_light set_direction(glm::vec3 direction);

};


#endif //ZPG_DIRECTIONAL_LIGHT_H
