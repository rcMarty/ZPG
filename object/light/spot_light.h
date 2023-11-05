//
// Created by rc_marty on 2.11.23.
//
#pragma once

#include "point_light.h"

class Spot_light : public Point_light, public Observer {
protected:
    std::shared_ptr<Camera> camera;

    glm::vec3 direction = glm::vec3(0.0f, 0.0f, 1.0f);
    float cut_off = glm::cos(glm::radians(12.5f));
    float outer_cut_off = glm::cos(glm::radians(15.0f));
public:

    Spot_light() : Point_light() {};

    //Light(glm::vec4 light_color, glm::vec3 light_position);
    Spot_light(glm::vec4 light_color, glm::vec3 position, glm::vec3 direction, float cut_off, float outer_cut_off) :
            Point_light(light_color, position), direction(direction), cut_off(cut_off), outer_cut_off(outer_cut_off) {};

    void set_direction(glm::vec3 direction);

    void set_cut_off(float cut_off);

    void set_outer_cut_off(float outer_cut_off);

    void set_camera(std::shared_ptr<Camera> observer);

    virtual void render(double delta_time) override;

    virtual void update() override;

    Spot_light set_transform_operations(std::shared_ptr<Transforms::Transform> transform_operations, bool static_tr = false);

    virtual std::unordered_map<std::string, std::variant<glm::mat4, glm::vec4, glm::vec3, float, int>> get_variables() override;

    Spot_light set_object(std::shared_ptr<Mesh> mesh, std::shared_ptr<Base_shader> shader, std::shared_ptr<Material> material);

};
