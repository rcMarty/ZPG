//
// Created by rc_marty on 1.10.23.
//

#include "shader_handler.h"

Shader_handler Shader_handler::add_shader(Shader_wrapper shader) {
    shaders.push_back(shader);
    return *this;
}

Shader_handler Shader_handler::add_shader(std::vector<Shader_wrapper> shader) {
    shaders.insert(shaders.end(), shader.begin(), shader.end());
    return *this;
}

Shader_ID Shader_handler::find_shader(std::string name) {
    for (auto &shader : shaders) {
        if (shader.name == name) {
            return shader.get_shader();
        }
    }
    printf("Shader %s not found\n", name.c_str());
}

