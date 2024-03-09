#version 330 core


in vec3 fragCol;

out vec4 sreenCol;

void main() {
    screenCol = vec4(fragCol, 1.0);

}