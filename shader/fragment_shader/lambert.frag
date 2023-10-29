#version 330

in vec3 worldPosition;
in vec3 worldNormal;

uniform vec3 lightPosition;
uniform vec4 lightColor;
uniform vec3 lightAttenuation;

//material things
uniform vec4 meshColor;
uniform vec4 ambientColor;


out vec4 fragColor;

void main() {
    vec3 lightVector = normalize(lightPosition - worldPosition);

    float diff = max(dot(lightVector, worldNormal), 0);

    float attenuation = 1.0 / (lightAttenuation.x + lightAttenuation.y * length(lightPosition - worldPosition) + lightAttenuation.z * pow(length(lightPosition - worldPosition), 2));
    vec4 diffuse = diff * lightColor * attenuation;

    fragColor = (ambientColor + diffuse) * meshColor;
}