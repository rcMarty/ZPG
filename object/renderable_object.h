//
// Created by rc_marty on 30.9.23.
//
#pragma once

#include "mesh.h"
#include "../shader/base_shader.h"
#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <functional>
#include "transform/transform_node.h"


typedef GLuint Shader_ID;


class Renderable_object {
private:
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Base_shader> shader;
    glm::mat4 Matrix = glm::mat4(1.0f);
    std::shared_ptr<Transforms::Transform> transform_operations;
    bool animated = false;
    //Shader_ID shader;

public:
    std::string name;
    //std::function<void()> move = nullptr; //todo tick functions for rotation and so on

    Renderable_object() = default;

    Renderable_object(Mesh mesh, std::shared_ptr<Base_shader> &shader);

    void init();

    void render();

    Renderable_object set_name(std::string name);

    Renderable_object set_transform_operations(std::shared_ptr<Transforms::Transform> transform_operations, bool animated);

    //void set_variable(std::string variable, glm::mat4 value);
    Renderable_object set_shader(std::shared_ptr<Base_shader> shader);

    Renderable_object set_mesh(const Mesh &mesh);

};


