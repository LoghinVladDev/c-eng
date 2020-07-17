#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shine;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;
in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 lightColor;
uniform vec3 lightPos;

uniform Light light;

uniform vec3 viewPosition;

uniform Material material;

float specularStrength = 0.5f;

void main() {
    ///ambient
    vec3 ambient = light.ambient * material.ambient;

    ///diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 diffuse = light.diffuse * (max(dot(norm, lightDir), 0.0) * material.diffuse);

    ///specular
    vec3 viewDir = normalize(viewPosition - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    vec3 specular = light.specular * (pow(max(dot(viewDir, reflectDir), 0.0), material.shine) * material.specular);

    vec3 result = (ambient + diffuse + specular);

    FragColor = vec4(result, 1.0);// * mix(texture(texture1, texCoord), texture(texture2, texCoord), interpolation);
}
