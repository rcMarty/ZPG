//# version 330
//in vec4 worldPos;
//in vec3 worldNor;
//out vec4 fragColor;
//

//
//
//void main (void)
//{
//    vec4 objectColor = vec4 (0.385, 0.647, 0.812, 1.0);
//
//    vec3 lightVector = normalize (lightPosition - vec3(worldPos));
//    //vec4 lightDir = normalize (lightPosition - vec3(worldPos));
//    float diff = max (dot (lightVector, normalize (worldNor)), 0.0);
//    vec4 diffuse = diff * lightColor;
//    vec4 ambient = vec4 (0.1, 0.1, 0.1, 1.0);
//
//    fragColor = (ambient + diffuse) * objectColor;
//}

#version 330

in vec3 worldPosition;
in vec3 worldNormal;

uniform vec3 lightPosition;
uniform vec4 lightColor;
//uniform vec4 meshColor;
//vec3 lightPosition = vec3(0.0, 0.0, 0.0);
//vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);
vec4 meshColor = vec4(0.385, 0.647, 0.812, 1.0);

out vec4 fragColor;

void main() {
    vec3 lightVector = normalize(lightPosition - worldPosition);

    float diff = max(dot(lightVector, worldNormal), 0);
    vec4 diffuse = diff * lightColor;
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    fragColor = (ambient + diffuse) * meshColor;
}