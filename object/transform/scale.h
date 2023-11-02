//
// Created by rc_marty on 5.10.23.
//
#pragma once

#include "transform.h"

namespace Transforms {


    class Scale : public Transform {
    private:
        glm::vec3 scale;
        std::function<glm::vec3(glm::vec3)> dynamic_function = nullptr;

    public:

        Scale(float x, float y, float z) : scale(x, y, z) {}

        Scale(glm::vec3 scale) : scale(scale) {}

        Scale(float x) : scale(x, x, x) {}

        Scale() : scale(1, 1, 1) {}

        Scale set_scale(float x, float y, float z) {
            scale = glm::vec3(x, y, z);
            return *this;
        }

        std::shared_ptr<Transform> set_dynamic_function(std::function<glm::vec3(glm::vec3)> dynamic_function) {
            this->dynamic_function = dynamic_function;
            return std::make_shared<Scale>(*this);
        }

        void tick(float delta_time) override {
            if (dynamic_function) {
                scale = dynamic_function(this->scale * delta_time);
            }
        }

        virtual glm::mat4x4 get_matrix(glm::mat4x4 input_matrix) override {
            return glm::scale(input_matrix, scale);
        }


    };
}