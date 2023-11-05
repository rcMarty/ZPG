//
// Created by rc_marty on 2.11.23.
//

#include "light_wrapper.h"
#include <variant>
#include <stdexcept>


Light_wrapper Light_wrapper::add(std::vector<std::shared_ptr<Light>> lights) {

    this->lights.insert(this->lights.end(), lights.begin(), lights.end());
    if (lights.size() > max_lights) {
        fprintf(stderr, "[ERROR] Max lights exceeded\n");
        throw std::runtime_error("Max lights exceeded");
    }
    return *this;
}

void Light_wrapper::set_variables(Base_shader &shader) {
    //todo think about setting variables if there or if in concrete light
    // something like get_variables which returns string and variable i guess

    shader.set_variable("no_lights", (int) lights.size());

    for (int i = 0; i < lights.size(); i++) {
        bool succ = true;
        auto variables = lights[i]->get_variables();
        for (auto &variable: variables) {

            std::string name = "lights[" + std::to_string(i) + "]." + variable.first;

            printf("[DEBUG] Setting variable %s\n", name.c_str());

            if (std::holds_alternative<glm::vec4>(variable.second)) {
                auto val = std::get<glm::vec4>(variable.second);
                succ &= shader.set_variable(name.c_str(), val);
            } else if (std::holds_alternative<glm::vec3>(variable.second)) {
                auto val = std::get<glm::vec3>(variable.second);
                succ &= shader.set_variable(name.c_str(), val);
            } else if (std::holds_alternative<float>(variable.second)) {
                auto val = std::get<float>(variable.second);
                succ &= shader.set_variable(name.c_str(), val);
            } else if (std::holds_alternative<int>(variable.second)) {
                auto val = std::get<int>(variable.second);
                succ &= shader.set_variable(name.c_str(), val);
            }

        }


//        printf("[DEBUG] setting variables %s\n", succ ? "succ" : "fail");
//        if (!succ)
//            fprintf(stderr, "[DEBUG] setting variables fail\n");

    }

}

void Light_wrapper::render(double delta_time) {
    for (auto &light: lights) {
        light->render(delta_time);
    }
}
