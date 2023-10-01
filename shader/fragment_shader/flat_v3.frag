#version 330
in vec3 colorInput;
out vec4 color;
void main() {
     color = vec4(colorInput, 1.0f);
}
//fragment shader