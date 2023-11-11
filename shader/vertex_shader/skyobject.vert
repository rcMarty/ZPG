#version 330

layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 vn;
layout (location = 2) in vec2 vt;

uniform mat4 projection;
uniform mat4 view;

out vec2 TexCoords;

void main() {
    gl_Position = projection * view * vec4(vp, 1.0);
    TexCoords = vt;
}

