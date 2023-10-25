#version 330

in vec3 worldPosition;
in vec3 worldNormal;

uniform vec3 cameraPosition;
uniform vec3 lightPosition;
uniform vec4 lightColor;
uniform vec4 meshColor;
//vec4 meshColor = vec4(0.385, 0.647, 0.812, 1.0);

out vec4 fragColor;

void main() {
    vec3 lightVector = normalize(lightPosition - worldPosition);
    vec3 cameraVector = normalize(cameraPosition - worldPosition);

    vec3 halfwayVector = normalize(lightVector + cameraVector);

    float spec = pow(max(dot(worldNormal, halfwayVector), 0.0), 32);
    float specularStrength = .75f;
    vec4 specular = specularStrength * spec * lightColor;

    float diff = max(dot(lightVector, worldNormal), 0);

    vec4 diffuse = diff * lightColor;
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);

    fragColor = (ambient + diffuse + specular) * meshColor;
}