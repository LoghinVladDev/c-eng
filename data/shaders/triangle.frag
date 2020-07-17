#version 330 core
out vec4 FragColor;
in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D texture1;
uniform sampler2D texture2;
float interpolation = 0.2f;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main() {
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff* lightColor;

    vec3 result = (ambient + diffuse) * objectColor;

    FragColor = vec4(result, 1.0); // * mix(texture(texture1, texCoord), texture(texture2, texCoord), interpolation);
}
