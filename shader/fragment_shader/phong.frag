#version 330

in vec3 worldPosition;
in vec3 worldNormal;

uniform vec3 cameraPosition;
uniform vec3 lightPosition;
uniform vec4 lightColor;

//material things
uniform vec4 meshColor;
uniform vec4 ambientColor;
uniform float specularStrength;
uniform int specularPower;


//vec4 meshColor = vec4(0.385, 0.647, 0.812, 1.0);

out vec4 fragColor;

void main() {



    vec3 lightVector = normalize(lightPosition - worldPosition);
    vec3 cameraVector = normalize(cameraPosition - worldPosition);

    // checking for angle between light and normal between < -90, 90 >
    float angle = dot(lightVector, worldNormal);
    if (angle < 0) {
        lightVector = vec3(0, 0, 0);
    }

    vec3 reflectVector = reflect(-lightVector, worldNormal);
    float spec = pow(max(dot(cameraVector, reflectVector), 0.0), specularPower);
    vec4 specular = specularStrength * spec * lightColor;

    float diff = max(dot(lightVector, worldNormal), 0);


    float attenuation = 1.0 / (1.0 + 0.1 * pow(length(lightPosition - worldPosition), 2));

    vec4 diffuse = diff * lightColor * attenuation;

    fragColor = (ambientColor + diffuse + specular) * meshColor;
}