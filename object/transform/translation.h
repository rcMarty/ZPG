//
// Created by rc_marty on 5.10.23.
//
#pragma once

#include "transform.h"

namespace Transforms {

    class Translation : public Transform {
    private:
        glm::vec3 translation;
        std::function<glm::vec3(glm::vec3)> dynamic_function = nullptr;
    public:

        Translation(float x, float y, float z) : translation(x, y, z) {}

        Translation(glm::vec3 translation) : translation(translation) {}

        Translation(float x) : translation(x, x, x) {}

        Translation() : translation(0, 0, 0) {}

        //todo mby remove idk yet
        // definitely not without pointer
        Translation set_translation(float x, float y, float z) {
            translation = glm::vec3(x, y, z);
            return *this;
        }

        std::shared_ptr<Translation> set_dynamic_function(std::function<glm::vec3(glm::vec3)> dynamic_function) {
            this->dynamic_function = dynamic_function;
            return std::make_shared<Translation>(*this);
        }

        virtual void tick(float delta_time) override {
            if (dynamic_function) {
                //printf("[DEBUG] Translation: tick\n");
                translation = dynamic_function(this->translation * delta_time);
            }
        }

        virtual glm::mat4x4 get_matrix(glm::mat4x4 input_matrix) override {
            print_matrix(input_matrix);
            return glm::translate(input_matrix, translation);

        }
    };

}