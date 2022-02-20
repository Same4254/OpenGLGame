#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragColor;
out vec3 fragPos;
out vec3 fragNormal;

void main() {
    gl_Position = projection * view * model * vec4(pos, 1.0);
    fragPos = vec3(model * vec4(pos, 1.0));
    fragColor = color;
    fragNormal = mat3(transpose(inverse(model))) * normal;
}