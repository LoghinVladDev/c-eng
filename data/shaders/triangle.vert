#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
//layout (location = 1) in vec3 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//out vec3 colour;
out vec2 texCoord;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0); // VClip = Mprojection * Mview * Mmodel * Vlocal
//    colour = aColor;
    texCoord = aTexCoord;
}
