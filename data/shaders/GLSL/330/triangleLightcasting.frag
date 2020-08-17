#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shine;
};

struct Light {
    vec3 position;
//    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

out vec4 FragColor;
in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

uniform vec3 lightColor;
//uniform vec3 lightPos;

uniform Light light;

uniform vec3 viewPosition;

uniform Material material;

float specularStrength = 0.5f;

void main() {
//    vec3 lightDir = normalize(-light.direction);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ///ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));
    ambient *= attenuation;

    ///diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 diffuse = light.diffuse * (max(dot(norm, lightDir), 0.0) * vec3(texture(material.diffuse, texCoord)));
    diffuse *= attenuation;

    ///specular
    vec3 viewDir = normalize(viewPosition - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    vec3 specular = light.specular * (pow(max(dot(viewDir, reflectDir), 0.0), material.shine) * vec3(texture(material.specular, texCoord)));
    specular *= attenuation;

    vec3 result = (ambient + diffuse + specular);

    FragColor = vec4(result, 1.0); //* texture(texture1, texCoord);
}
