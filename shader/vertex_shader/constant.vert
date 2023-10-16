#version 330
layout(location=0) in vec4 position;
uniform vec4 colorInput;
out vec4 colorInput;
void main () {
    gl_Position = position;
}
