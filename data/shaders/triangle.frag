#version 330 core
out vec4 FragColor;
in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;
//in vec3 lightPos;

uniform sampler2D texture1;
uniform sampler2D texture2;
float interpolation = 0.2f;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

uniform int specularShineStrength;

uniform vec3 viewPosition;

float specularStrength = 0.5f;

void main() {
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff* lightColor;

    //specular
    vec3 viewDir = normalize(viewPosition - fragPos);
//    vec3 viewDir = normalize(-fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    vec3 specular = specularStrength * pow(max(dot(viewDir, reflectDir), 0.0), specularShineStrength) * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;

    FragColor = vec4(result, 1.0); // * mix(texture(texture1, texCoord), texture(texture2, texCoord), interpolation);
}
