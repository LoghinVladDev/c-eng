#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform mat4 TIModel; // the transposed of the inverted model matrix for scaling normals
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0); // VClip = Mprojection * Mview * Mmodel * Vlocal
    texCoord = aTexCoord;
    normal = mat3(TIModel) * aNormal;
    fragPos = vec3(model * vec4(aPos, 1.0));
}
