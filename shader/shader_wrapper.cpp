//
// Created by rc_marty on 1.10.23.
//

#include "shader_wrapper.h"

#include <utility>

Shader_wrapper::Shader_wrapper(const std::string &vertex_shader_path,const std::string &fragment_shader_path) {
    this->shader = Shader::create_shader(vertex_shader_path, fragment_shader_path);
}
Shader_wrapper::Shader_wrapper(const std::string &vertex_shader_path, const std::string &fragment_shader_path,std::string name) {
    this->shader = Shader::create_shader(vertex_shader_path, fragment_shader_path);
    this->name = std::move(name);
}

Shader_wrapper Shader_wrapper::set_name(std::string name) {
    this->name = std::move(name);
    return *this;
}

Shader_wrapper Shader_wrapper::set_shader(Shader_ID shader) {
    this->shader = shader;
    return *this;
}

Shader_ID Shader_wrapper::get_shader() const {
    return shader;
}


