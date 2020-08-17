#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;
//layout (location = 1) in vec3 aColor;

uniform mat4 TIModel; // the transposed of the inverted model matrix for scaling normals
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//uniform vec3 lightPos;

//out vec3 colour;
out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;
//out vec3 LightPos;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0); // VClip = Mprojection * Mview * Mmodel * Vlocal
    //    colour = aColor;
    texCoord = aTexCoord;
    normal = mat3(TIModel) * aNormal;
    //    normal = mat3(TIModel) * aNormal;
    //    normal = mat3(transpose(inverse(model))) * aNormal;
    fragPos = vec3(model * vec4(aPos, 1.0));
    //    LightPos = vec3(view * vec4(lightPos, 1.0));
}
