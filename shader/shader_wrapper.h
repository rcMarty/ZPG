//
// Created by rc_marty on 1.10.23.
//
#pragma once

#include "shader.h"

typedef GLuint Shader_ID;


class Shader_wrapper {
private:
    Shader_ID shader;

    Shader_wrapper set_shader(Shader_ID shader);
public:
    //todo this is not good
    // refactor this to use some kind of predefined types
    // this gonna be inportant when ill have like 10 shaders and just ids is not good idea
    // mby fck it and make just everytime new shader for each object
    std::string name;

    Shader_wrapper() = delete;
    Shader_wrapper(const std::string &vertex_shader_path,const std::string &fragment_shader_path);
    Shader_wrapper(const std::string &vertex_shader_path,const std::string &fragment_shader_path, std::string name);
    Shader_wrapper set_name(std::string name);
    Shader_ID get_shader() const;

};
