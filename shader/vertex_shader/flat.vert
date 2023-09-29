#version 330
layout(location=0) in vec4 position;
layout(location=1) in vec4 vertex_Color;
out vec4 colorInput;
void main () {
     gl_Position = position;
     colorInput = vertex_Color;
}
