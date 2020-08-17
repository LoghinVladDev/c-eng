#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shine;
};

struct Light {
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float cutoff;
    float outerCutoff;
};

out vec4 FragColor;
in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

uniform Light light;

uniform vec3 viewPosition;

uniform Material material;

float specularStrength = 0.5f;

void main() {
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);

    vec3 ambient =
        light.ambient *
        texture(material.diffuse, texCoord).rgb;

    vec3 diffuse =
        light.diffuse *
        max(dot(norm, lightDir), 0.0) *
        texture(material.diffuse, texCoord).rgb;

    vec3 specular =
        light.specular *
        pow(max(dot(normalize(viewPosition - fragPos), reflect(-lightDir, norm)), 0.0), material.shine) *
        texture(material.specular, texCoord).rgb;

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = (light.cutoff - light.outerCutoff);
    float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);

    diffuse *= intensity;
    specular *= intensity;

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    FragColor = vec4(vec3(ambient + diffuse + specular), 1.0);
}
