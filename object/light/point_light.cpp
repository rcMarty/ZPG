//
// Created by rc_marty on 21.10.23.
//

#include "point_light.h"
#include "../transform/translation.h"


void Point_light::render(double delta_time) {
    Light::render(delta_time);
    if (transform_operations)
        light_position = glm::vec3(Matrix_transformed[3][0], Matrix_transformed[3][1], Matrix_transformed[3][2]);

}

Point_light Point_light::set_light_attenuation(glm::vec3 light_attenuation) {
    this->light_attenuation = light_attenuation;
    return *this;
}

std::unordered_map<std::string, std::variant<glm::mat4, glm::vec4, glm::vec3, float, int>> Point_light::get_variables() {
    //struct lightSource {
    //    vec3 position;
    //    vec4 color;
    //    vec3 attenuation;
    //
    //
    //    vec3 direction;
    //    float cutOff;
    //    float outerCutOff;
    //    int type;
    //};
    std::unordered_map<std::string, std::variant<glm::mat4, glm::vec4, glm::vec3, float, int>> variables;
    variables["type"] = static_cast<int>(Light_type::POINT_LIGHT);
    variables["color"] = light_color;
    variables["position"] = light_position;
    variables["attenuation"] = light_attenuation;
    variables["modelMatrix"] = Matrix_transformed;
    return variables;
}

Point_light Point_light::set_transform_operations(std::shared_ptr<Transforms::Transform> transform_operations, bool static_tr) {
    Transformable_object::set_transform_operations(transform_operations, static_tr);
    return *this;
}

Point_light Point_light::set_object(std::shared_ptr<Mesh> mesh, std::shared_ptr<Base_shader> shader, std::shared_ptr<Material> material) {
    Light::set_object(mesh, shader, material);
    return *this;
}

Point_light::Point_light(glm::vec4 light_color, glm::vec3 light_position) {
    this->light_color = light_color;
    //staic once transformation
    this->set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add({
                                                                        std::make_shared<Transforms::Translation>(light_position),
                                                                }
            ), true);


}
