//
// Created by rc_marty on 21.10.23.
//

#pragma once

#include "light.h"

class Point_light : public Light {
protected:
    //    std::shared_ptr<Mesh> mesh;
    //    std::shared_ptr<Base_shader> shader;
    //
    //    std::shared_ptr<Transforms::Transform> transform_operations;
    //    std::shared_ptr<Material> material;
    //
    //    glm::mat4 Matrix = glm::mat4(1.0f);


    glm::vec3 light_position = glm::vec3(Matrix[3][0], Matrix[3][1], Matrix[3][2]);
    glm::vec3 light_attenuation = glm::vec3(0.9f, 0.0f, 0.01f);

public:
    Point_light() = default;

    Point_light(glm::vec4 light_color, glm::vec3 light_position) : Light(light_color), light_position(light_position) {};

    Point_light set_light_attenuation(glm::vec3 light_attenuation);

    virtual void render(double delta_time) override;

    Point_light set_transform_operations(std::shared_ptr<Transforms::Transform> transform_operations, bool static_tr = false);

    virtual std::unordered_map<std::string, std::variant<glm::mat4, glm::vec4, glm::vec3, float, int>> get_variables();

    Point_light set_object(std::shared_ptr<Mesh> mesh, std::shared_ptr<Base_shader> shader, std::shared_ptr<Material> material);

};
