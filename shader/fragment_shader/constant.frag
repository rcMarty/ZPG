#version 330

    struct Material {
    vec4 meshColor;
    vec4 ambientColor;
    float specularStrength;
    int specularPower;
};

uniform Material material;

out vec4 color;
void main() {
    color = material.meshColor;
}