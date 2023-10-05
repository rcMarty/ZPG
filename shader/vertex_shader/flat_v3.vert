#version 330
layout(location=0) in vec3 position;
layout(location=1) in vec3 vertex_Color;
uniform mat4 modelMatrix;
out vec3 colorInput;
void main() {
    gl_Position = modelMatrix * vec4(position, 1.0f);
    //gl_Position = vec4(position, 1.0f);
    colorInput = vertex_Color;
}
//vertex shader