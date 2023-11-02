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
        std::function<float(float)> dynamic_function;


    public:

        Rotation(float angle, glm::vec3 axis) : angle(glm::radians(angle)), axis(axis) {}

        Rotation(float angle, float x, float y, float z) : angle(glm::radians(angle)), axis(x, y, z) {}

        Rotation(float angle) : angle(glm::radians(angle)), axis(0, 0, 0) {}

        Rotation() : angle(0), axis(1, 0, 0) {}

        std::shared_ptr<Rotation> set_dynamic_function(std::function<float(float)> dynamic_function) {
            this->dynamic_function = dynamic_function;
            return std::make_shared<Rotation>(*this);
        }

        Rotation set_axis(float x, float y, float z) {
            axis = glm::vec3(x, y, z);
            return *this;
        }

        Rotation &set_rotation(float angle, glm::vec3 axis) {
            //convert angle from degrees to radians
            this->angle = glm::radians(angle);
            this->axis = axis;
            return *this;
        }

        virtual void tick(float delta_time) override {
            if (dynamic_function) {
                //printf("[DEBUG] Rotation: tick\n");
                this->angle = glm::mod(dynamic_function(this->angle * delta_time), 360.0f);
            }
        }

        virtual glm::mat4x4 get_matrix(glm::mat4x4 input_matrix) override {
            //printf("[DEBUG] Rotation: %f get_matrix\n", this->angle);
            return glm::rotate(input_matrix, this->angle, this->axis);
        }
    };
}