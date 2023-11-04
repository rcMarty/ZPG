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


struct Material {
    vec4 meshColor;
    vec4 ambientColor;
    float specularStrength;
    int specularPower;
};




//vec4 meshColor = vec4(0.385, 0.647, 0.812, 1.0);



//vec3 CalcDirLight(lightSource light, Material material, vec3 normal, vec3 viewDir)
//{
//    vec3 lightDir = normalize(-light.direction);
//    // diffuse shading
//    float diff = max(dot(normal, lightDir), 0.0);
//    // specular shading
//    vec3 reflectDir = reflect(-lightDir, normal);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.specularPower);
//    // combine results
//    //    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
//    //    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
//    //    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
//    vec3 ambient = light.ambient * vec3(material.meshColor);
//    vec3 diffuse = light.diffuse * diff * vec3(material.meshColor);
//    vec3 specular = light.specular * spec * vec3(material.meshColor);
//    return (ambient + diffuse + specular);
//}

vec4 CalcPointLight(lightSource light, Material material)
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    vec3 lightVector = normalize(light.position - worldPosition);
    vec3 cameraVector = normalize(cameraPosition - worldPosition);

    // checking for angle between light and normal between < -90, 90 >
    float angle = dot(lightVector, worldNormal);
    if (angle < 0) {
        lightVector = vec3(0, 0, 0);
    }

    vec3 reflectVector = reflect(-lightVector, worldNormal);
    float spec = pow(max(dot(cameraVector, reflectVector), 0.0), material.specularPower);
    vec4 specular = material.specularStrength * spec * light.color;

    float diff = max(dot(lightVector, worldNormal), 0);



    float attenuation = 1.0 / (light.attenuation.x + light.attenuation.y * length(light.position - worldPosition) + light.attenuation.z * pow(length(light.position - worldPosition), 2));

    vec4 diffuse = diff * light.color * attenuation;
    return (material.ambientColor + diffuse + specular) * material.meshColor;


}

uniform int no_lights;
uniform Material material;
uniform lightSource lights[10];

out vec4 fragColor;
void main() {

    //for (int index = 0; index < numberOfLights ; index ++) {
    //finalColor += lightIntensity ;
    //}


    // define an output color value
    vec4 output = vec4(0.0);

    // do the same for all point lights
    for (int i = 0; i < no_lights; i++) {
        if (lights[i].type == point) {
            output += CalcPointLight(lights[i], material);
        }
        //        else if (lights[i].type == spot) {
        //            output += someFunctionToCalculateSpotLight();
        //        }
        //        else if (lights[i].type == directional) {
        //            output += CalcDirLight(lights[i], worldNormal, cameraPosition);
        //        }
    }

    fragColor = vec4(output.xyz, 1.0);

}