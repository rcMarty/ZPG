//
// Created by rc_marty on 21.10.23.
//

#pragma once

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <memory>
#include "../../shader/observer.h"
#include "../transform/transform.h"

class Light {
    glm::vec4 light_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 light_position = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::mat4 matrix = glm::mat4(1.0f);
    std::shared_ptr<Transforms::Transform> transform_operations;

public:

    glm::vec4 get_color() const;

    glm::vec3 get_position() const;

    void update();

    Light set_transform_operations(std::shared_ptr<Transforms::Transform> transform_operations);

};

