//
// Created by rc_marty on 19.10.23.
//

#include "constant_shader.h"

void Constant_shader::set_color(glm::vec4 color) {
    set_variable("color", this->color);
}
