#version 330 core

in vec3 fragColor;
in vec3 fragPos;
in vec3 fragNormal;

uniform vec3 lightPos;
uniform vec3 lightColor;

out vec4 colorOut;

void main() {
    vec3 norm = normalize(fragNormal);
    vec3 lightDirection = normalize(lightPos - fragPos);

    vec3 diffuse = max(dot(norm, lightDirection), 0.0) * lightColor;
    vec3 ambient = 0.1 * lightColor;

    colorOut = vec4((ambient + diffuse) * fragColor, 1.0f);
} 