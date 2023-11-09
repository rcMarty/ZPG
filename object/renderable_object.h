//
// Created by rc_marty on 30.9.23.
//
#pragma once

#include "model/mesh.h"
#include "transformable_object.h"
#include "material.h"

typedef GLuint Shader_ID;

class Renderable_object : public Transformable_object {
protected:
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Material> material;
    std::shared_ptr<Base_shader> shader;
    bool has_texture = false;


public:
    std::string name;

    // std::function<void()> move = nullptr; //todo tick functions for rotation and so on
    Renderable_object() = default;

    Renderable_object(std::shared_ptr<Mesh> mesh, std::shared_ptr<Base_shader> shader) : shader(shader), mesh(mesh) {};

    virtual void init();

    virtual void render(double delta_time);

    Renderable_object set_name(std::string name);

    Renderable_object set_shader(std::shared_ptr<Base_shader> shader);

    Renderable_object set_transform_operations(std::shared_ptr<Transforms::Transform> transform_operations, bool static_tr = false);

    Renderable_object set_material(std::shared_ptr<Material> material);

    Renderable_object set_has_texture(bool has_texture);

    Renderable_object set_mesh(const Mesh &mesh);
};
