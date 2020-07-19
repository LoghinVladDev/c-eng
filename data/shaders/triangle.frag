#version 330 core

#define POINT_LIGHTS_COUNT 4

struct Material {
    sampler2D diffuse;
    sampler2D specular;

    float shine;
};

struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    bool toggle;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    bool toggle;
};

struct SpotLight {
    vec3 position;
    vec3 direction;

    float cutoff;
    float outerCutoff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    bool toggle;
};

uniform Material material;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[POINT_LIGHTS_COUNT];
uniform SpotLight spotLight;

uniform vec3 viewPosition;

in vec2 texCoord;
in vec3 fragPos;
in vec3 normal;

out vec4 FragColor;

vec3 calculateDirectionalLight(DirectionalLight, vec3, vec3);
vec3 calculatePointLight(PointLight, vec3, vec3, vec3);
vec3 calculateSpotLight(SpotLight, vec3, vec3, vec3);

void main() {
    vec3 norm = normalize(normal);
    vec3 viewDirection = normalize(viewPosition - fragPos);

    vec3 result = vec3(0.0);

    if(directionalLight.toggle)
        result += calculateDirectionalLight(directionalLight, norm, viewDirection);

    for(int i = 0; i < POINT_LIGHTS_COUNT; i++) {
        if(pointLights[i].toggle)
            result += calculatePointLight(pointLights[i], norm, fragPos, viewDirection);
    }

    // spot light calculation ...
    if(spotLight.toggle)
        result += calculateSpotLight(spotLight, norm, fragPos, viewDirection);

    FragColor = vec4(result, 1.0);
}

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection) {
    vec3 lightDirection = normalize( -light.direction );

    vec3 ambient =
        light.ambient *
        vec3( texture( material.diffuse, texCoord ) );

    vec3 diffuse =
        light.diffuse *
        max( dot( normal, lightDirection ), 0.0) *
        vec3( texture( material.diffuse, texCoord ) );

    vec3 specular =
        light.specular *
        pow( max( dot( viewDirection, reflect( -lightDirection, normal ) ), 0.0 ), material.shine ) *
        vec3( texture( material.specular, texCoord ) );

    return (ambient + diffuse + specular);
}

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection) {
    vec3 lightDirection = normalize(light.position - fragPos);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient =
        light.ambient *
        vec3( texture( material.diffuse, texCoord ) ) *
        attenuation;

    vec3 diffuse =
        light.diffuse *
        max( dot( normal, lightDirection ), 0.0 ) *
        vec3( texture( material.diffuse, texCoord ) ) *
        attenuation;

    vec3 specular =
        light.specular *
        pow( max( dot( viewDirection, reflect( -lightDirection, normal ) ), 0.0 ), material.shine ) *
        vec3( texture( material.specular, texCoord ) ) *
        attenuation;

    return (ambient + diffuse + specular);
}

vec3 calculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDirection) {
    vec3 lightDir = normalize(light.position - fragPos);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutoff - light.outerCutoff;
    float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);

    vec3 ambient =
        light.ambient *
        vec3( texture( material.diffuse, texCoord ) ) *
        attenuation *
        intensity;

    vec3 diffuse =
        light.diffuse *
        max( dot( normal, lightDir ), 0.0 ) *
        vec3( texture( material.diffuse, texCoord ) ) *
        attenuation *
        intensity;

    vec3 specular =
        light.specular *
        pow( max( dot( viewDirection, reflect( -lightDir, normal ) ), 0.0 ), material.shine ) *
        vec3( texture( material.specular, texCoord ) ) *
        attenuation *
        intensity;

    return (ambient + diffuse + specular);
}