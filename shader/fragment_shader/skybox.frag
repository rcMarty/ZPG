#version 330
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube textureDiffuse;

void main()
{
    FragColor = texture(textureDiffuse, TexCoords);
}