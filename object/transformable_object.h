//
// Created by rc_marty on 3.11.23.
//
#pragma once

#include <glm/glm.hpp>
#include <functional>
#include "transform/transform_node.h"
#include "../shader/base_shader.h"
#include <memory>
#include <string>

class Transformable_object {
protected:
    std::shared_ptr<Transforms::Transform> transform_operations;
    glm::mat4 Matrix = glm::mat4(1.0f);
    glm::mat4 Matrix_transformed = glm::mat4(1.0f);
public:

    Transformable_object() = default;

    virtual void render(double delta_time);

    Transformable_object set_transform_operations(std::shared_ptr<Transforms::Transform> transform_operations, bool static_tr = false);

    Transformable_object set_shader(std::shared_ptr<Base_shader> shader);
};

