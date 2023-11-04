//
// Created by rc_marty on 5.10.23.
//
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stdio.h"
#include <string>


namespace Transforms {


    class Transform {
    public:
        virtual glm::mat4x4 get_matrix(glm::mat4x4 input_matrix) = 0;

        virtual void tick(float delta_time) = 0;

        static std::string print_matrix(glm::mat4x4 input_matrix) {
            std::string output = "";
            for (size_t i = 0; i < 4; i++) {
                output += std::to_string(input_matrix[i][0]) + " " + std::to_string(input_matrix[i][1]) + " " +
                          std::to_string(input_matrix[i][2]) + " " + std::to_string(input_matrix[i][3]) + "\n";
            }
            return output;
        }


    };
}