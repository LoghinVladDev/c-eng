#version 330 core
layout (location = 0) in vec3 aPos;

//out vec4 fragmentColor;

//uniform vec3 objectColor;
//uniform vec3 lightColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
