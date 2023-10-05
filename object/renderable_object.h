//
// Created by rc_marty on 30.9.23.
//
#pragma once

#include "mesh.h"
#include "../shader/shader.h"
#include <memory>
#include <string>
#include <glm/glm.hpp>
#include "transform/transform_node.h"


typedef GLuint Shader_ID;


class Renderable_object {
private:
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Shader> shader;
    glm::mat4 Matrix = glm::mat4(1.0f);
    std::shared_ptr<Transforms::Transform> transform_operations;
    //Shader_ID shader;

public:
    std::string name;

    Renderable_object() = default;

    Renderable_object(Mesh mesh, Shader shader);

    void init();

    void render();

    Renderable_object set_name(std::string name);

    Renderable_object set_transform_operations(std::shared_ptr<Transforms::Transform> transform_operations);

    //void set_variable(std::string variable, glm::mat4 value);
    Renderable_object set_shader(Shader shader);

    Renderable_object set_mesh(const Mesh &mesh);

};


