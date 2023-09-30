//
// Created by rc_marty on 30.9.23.
//
#pragma once

#include "mesh.h"
#include "../shader/shader.h"
#include <memory>
typedef GLuint Shader_ID;


class Renderable_object {
private:
    std::shared_ptr<Mesh> mesh;
    Shader_ID shader;

public:
    Renderable_object(Mesh mesh, Shader_ID shader);
    void init();
    void render();

};


