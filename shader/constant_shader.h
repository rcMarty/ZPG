//
// Created by rc_marty on 19.10.23.
//

#ifndef ZPG_CONSTANT_SHADER_H
#define ZPG_CONSTANT_SHADER_H


#include "base_shader.h"

class Constant_shader : public Base_shader {
protected:
    glm::vec4 color = glm::vec4(0.5f, 0.2f, 0.7f, 1.0f);
public:
    Constant_shader(glm::vec3 color, const std::string &vertex_shader_path, const std::string &fragment_shader_path) : Base_shader(vertex_shader_path, fragment_shader_path) {};

    void set_color(glm::vec4 color);

};


#endif //ZPG_CONSTANT_SHADER_H
