#version 330

in vec3 worldPosition;
in vec3 worldNormal;

//enum for light types
const int directional = 0;
const int point = 1;
const int spot = 2;


uniform vec3 cameraPosition;

//uniform vec3 lightPosition;
//uniform vec4 lightColor;
//uniform vec3 lightAttenuation;


struct lightSource {
    vec3 position;
    vec4 color;
    vec3 attenuation;


    vec3 direction;
    float cutOff;
    float outerCutOff;
    int type;
};
//struct Material {
//    sampler2D diffuse;
//    vec3      specular;
//    float     shininess;
//};

struct Material {
    vec4 meshColor;
    vec4 ambientColor;
    float specularStrength;
    int specularPower;
};




//vec4 meshColor = vec4(0.385, 0.647, 0.812, 1.0);


vec4 CalcSpotLight(lightSource light, Material material)
{
    vec3 lightVector = normalize(light.position - worldPosition);
    vec3 cameraVector = normalize(cameraPosition - worldPosition);
    vec3 reflectVector = reflect(-lightVector, worldNormal);

    float spec = pow(max(dot(cameraVector, reflectVector), 0.0), material.specularPower);

    float angle = dot(lightVector, worldNormal);
    if (angle < 0) {
        spec = 0;
        //lightVector = worldNormal * -1;
    }
    vec4 specular = material.specularStrength * spec * light.color;

    float diff = max(dot(lightVector, worldNormal), 0);
    vec4 diffuse = diff * light.color;

    float attenuation = 1.0 / (light.attenuation.x + light.attenuation.y * length(light.position - worldPosition) + light.attenuation.z * pow(length(light.position - worldPosition), 2));

    //cone things
    float cutOff = cos(radians(light.cutOff));
    float outerCutOff = cos(radians(light.outerCutOff));
    float theta = dot(lightVector, normalize(-light.direction));
    float epsilon = (cutOff - outerCutOff);
    float intensity = clamp((theta - outerCutOff) / epsilon, 0, 1);

    return (diffuse * intensity + specular * intensity) * material.meshColor * attenuation;
}


vec4 CalcDirLight(lightSource light, Material material)
{
    vec3 lightVector = -light.direction;
    vec3 cameraVector = normalize(cameraPosition - worldPosition);
    vec3 reflectVector = normalize(lightVector + worldNormal);

    float spec = pow(max(dot(cameraVector, reflectVector), 0.0), material.specularPower);

    float angle = dot(lightVector, worldNormal);
    if (angle < 0) {
        spec = 0;
        //lightVector = worldNormal * -1;
    }
    vec4 specular = material.specularStrength * spec * light.color;

    float diff = max(dot(lightVector, worldNormal), 0);
    vec4 diffuse = diff * light.color;

    return (diffuse + specular) * material.meshColor;
}

vec4 CalcPointLight(lightSource light, Material material)
{
    vec3 lightVector = normalize(light.position - worldPosition);
    vec3 cameraVector = normalize(cameraPosition - worldPosition);
    vec3 reflectVector = reflect(-lightVector, worldNormal);

    float spec = pow(max(dot(cameraVector, reflectVector), 0.0), material.specularPower);

    float angle = dot(lightVector, worldNormal);
    if (angle < 0) {
        spec = 0;
    }
    vec4 specular = material.specularStrength * spec * light.color;

    float diff = max(dot(lightVector, worldNormal), 0);
    vec4 diffuse = diff * light.color;

    float attenuation = 1.0 / (light.attenuation.x + light.attenuation.y * length(light.position - worldPosition) + light.attenuation.z * pow(length(light.position - worldPosition), 2));
    //float attenuation = 5.0;

    return (diffuse + specular) * material.meshColor * attenuation;
}

uniform int no_lights;
uniform Material material;
uniform lightSource lights[10];


uniform sampler2D textureDiffuse;
uniform sampler2D textureSpecular;
uniform int hasTexture;

in vec2 TexCoord;

Material texMaterial;

out vec4 fragColor;


void main() {

    if (hasTexture == 1) {
        texMaterial.meshColor = texture(textureDiffuse, TexCoord);
        texMaterial.specularStrength = texture(textureSpecular, TexCoord).r;
        texMaterial.ambientColor = vec4(texture(textureDiffuse, TexCoord).xyz * 0.05, 1.0);
        texMaterial.specularPower = material.specularPower;
    }
    else {
        texMaterial = material;
    }

    // define an output color value
    vec4 outputColor = vec4(0.0f);

    // do the same for all point lights
    for (int i = 0; i < no_lights; i++) {
        if (lights[i].type == point) {
            outputColor += CalcPointLight(lights[i], texMaterial);
        }
        else if (lights[i].type == spot) {
            outputColor += CalcSpotLight(lights[i], texMaterial);
        }
        else if (lights[i].type == directional) {
            outputColor += CalcDirLight(lights[i], texMaterial);
        }
    }
    outputColor += texMaterial.ambientColor;

    fragColor = vec4(outputColor.xyz, 1.0);

}