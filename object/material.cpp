//
// Created by rc_marty on 25.10.23.
//

#include "material.h"

Material::Material(glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, float shininess) {
    this->ambient = ambient;
    this->color = diffuse;
    this->specularStrength = specularStrength;
    this->specularPower = specularPower;
}

Material Material::set_color(glm::vec4 color) {
    this->color = color;
    return *this;
}

Material Material::set_ambient(glm::vec4 ambient) {
    this->ambient = ambient;
    return *this;
}

Material Material::set_specular_strength(float specularStrength) {
    this->specularStrength = specularStrength;
    return *this;
}

Material Material::set_specular_power(int specularPower) {
    this->specularPower = specularPower;
    return *this;
}


void Material::set_variables(std::shared_ptr<Base_shader> shader) {

//    struct Material {
//        vec4 meshColor;
//        vec4 ambientColor;
//        float specularStrength;
//        int specularPower;
//    };

//  uniform Material material;

    shader->set_variable("material.ambientColor", ambient);
    shader->set_variable("material.meshColor", color);
    shader->set_variable("material.specularStrength", specularStrength);
    shader->set_variable("material.specularPower", specularPower);

}

Material::Material(glm::vec4 color, glm::vec4 ambient, float specularStrength, int specularPower) {
    this->color = color;
    this->ambient = ambient;
    this->specularStrength = specularStrength;
    this->specularPower = specularPower;
}
