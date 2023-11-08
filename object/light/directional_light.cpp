//
// Created by rc_marty on 2.11.23.
//

#include "directional_light.h"

std::unordered_map<std::string, std::variant<glm::mat4, glm::vec4, glm::vec3, float, int>> Directional_light::get_variables() {
    std::unordered_map<std::string, std::variant<glm::mat4, glm::vec4, glm::vec3, float, int>> variables;
    variables["type"] = static_cast<int>(Light_type::DIRECTIONAL_LIGHT);
    variables["color"] = light_color;
    variables["direction"] = direction;
    variables["modelMatrix"] = Matrix_transformed;
    return variables;
}
Directional_light Directional_light::set_direction(glm::vec3 direction) {
    this->direction = direction;
    return *this;
}
