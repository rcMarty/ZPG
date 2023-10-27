//
// Created by rc_marty on 21.10.23.
//

#include "light.h"

glm::vec4 Light::get_color() const {
    return light_color;
}

glm::vec3 Light::get_position() const {
    return light_position;
}

Light Light::set_transform_operations(std::shared_ptr<Transforms::Transform> transform_operations) {
    this->transform_operations = transform_operations;
    matrix = transform_operations->get_matrix(matrix);
    return *this;
}

void Light::update() {
    if (transform_operations != nullptr) {
        matrix = transform_operations->get_matrix(matrix);
        glm::vec3 world_normal = glm::normalize(glm::vec3(matrix * glm::vec4(light_position, 0.0f)));
        glm::vec3 world_position = glm::vec3(matrix * glm::vec4(light_position, 1.0f));
        light_position = matrix * glm::vec4(light_position, 1.0f);
        //printf("[DEBUG] Light updated: %f ,%f ,%f \n", light_position.x, light_position.y, light_position.z);
    }

}

Light::Light(glm::vec4 light_color, glm::vec3 light_position) {
    this->light_color = light_color;
    this->light_position = light_position;
}