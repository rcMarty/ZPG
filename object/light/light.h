//
// Created by rc_marty on 3.11.23.
//

#pragma once

#include "../renderable_object.h"
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <memory>
#include "../../utils/observer.h"
#include "../transform/transform.h"
#include "../renderable_object.h"
#include <variant>

//enum for light types
//const int directional = 0;
//const int point = 1;
//const int spot = 2;

enum class Light_type {
    DIRECTIONAL_LIGHT = 0,
    POINT_LIGHT = 1,
    SPOT_LIGHT = 2
};

class Light : public Renderable_object {

protected:
    glm::vec4 light_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    bool has_object = false;
public:
    Light() = default;

    Light(glm::vec4 light_color) : light_color(light_color) {};

    virtual void render(double delta_time);

    virtual std::unordered_map<std::string, std::variant<glm::mat4, glm::vec4, glm::vec3, float, int>> get_variables() = 0;

    void set_transform_operations(std::shared_ptr<Transforms::Transform> transform_operations, bool static_tr = false);

    void set_object(std::shared_ptr<Mesh> mesh, std::shared_ptr<Base_shader> shader, std::shared_ptr<Material> material);

};

