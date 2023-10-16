//
// Created by rc_marty on 5.10.23.
//
#pragma once

#include <vector>
#include <memory>
#include "transform.h"

namespace Transforms {


    class Transform_node : public Transform {
    private:
        std::vector<std::shared_ptr<Transform>> children;

    public:

        std::shared_ptr<Transform_node> add(std::shared_ptr<Transform> child) {
            
            this->children.push_back(child);
            return std::make_shared<Transform_node>(*this);
        }

        std::shared_ptr<Transform_node> add(std::vector<std::shared_ptr<Transform>> child) {

            this->children.insert(children.end(), child.begin(), child.end());
            return std::make_shared<Transform_node>(*this);
        }

        virtual glm::mat4x4 get_matrix(glm::mat4x4 input_matrix) override {
            for (auto child: children) {
                //printf("[DEBUG] Transform_node: _____________________________________\n");
                //printf("[DEBUG] BEFORE Matrix:\n%s\n", print_matrix(input_matrix).c_str());
                input_matrix = child->get_matrix(input_matrix);
                //printf("[DEBUG] AFTER Matrix:\n%s\n", print_matrix(input_matrix).c_str());
            }
            return input_matrix;
        };
    };

}