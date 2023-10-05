//
// Created by rc_marty on 5.10.23.
//

#pragma once

#include "transform.h"

namespace Transforms {


    class Rotation : public Transform {
    private:
        float angle;
        glm::vec3 axis;
    public:

        Rotation(float angle, glm::vec3 axis) : angle(angle * M_PI / 180), axis(axis) {}

        Rotation(float angle, float x, float y, float z) : angle(angle * M_PI / 180), axis(x, y, z) {}

        Rotation(float angle) : angle(angle * M_PI / 180), axis(0, 0, 0) {}

        Rotation() : angle(0), axis(0, 0, 0) {}

        Rotation set_angle(float angle) {
            this->angle = angle * M_PI / 180;
            return *this;
        }

        Rotation set_axis(float x, float y, float z) {
            axis = glm::vec3(x, y, z);
            return *this;
        }

        Rotation set_rotation(float angle, glm::vec3 axis) {
            //convert angle from degrees to radians
            this->angle = angle * M_PI / 180;
            this->axis = axis;
            return *this;
        }

        virtual glm::mat4x4 get_matrix(glm::mat4x4 input_matrix) override {
            return glm::rotate(input_matrix, this->angle, this->axis);
        }
    };
}