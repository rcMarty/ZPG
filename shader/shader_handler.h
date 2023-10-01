//
// Created by rc_marty on 1.10.23.
//
#pragma once


#include "shader_wrapper.h"

typedef GLuint Shader_ID;

class Shader_handler {
private:
    std::vector<Shader_wrapper> shaders;

public:
    Shader_handler() = default;
    Shader_handler add_shader(Shader_wrapper shader);
    Shader_handler add_shader(std::vector<Shader_wrapper> shader);
    Shader_ID find_shader(std::string name);
};
