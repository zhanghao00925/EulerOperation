#version 440 core

uniform vec3 incolor;

out vec4 fragColor;

void main() {

    fragColor = vec4(incolor, 1.0f);
}
