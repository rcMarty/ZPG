#version 330

    struct Material {
    vec4 meshColor;
    vec4 ambientColor;
    float specularStrength;
    int specularPower;
};

uniform Material material;

uniform sampler2D textureDiffuse;
uniform sampler2D textureSpecular;
uniform int hasTexture;

in vec2 TexCoord;

Material texMaterial;

out vec4 fragColor;



void main() {


    if (hasTexture == 1) {
        texMaterial.meshColor = texture(textureDiffuse, TexCoord);
    }
    else {
        texMaterial = material;
    }


    fragColor = texMaterial.meshColor;
}