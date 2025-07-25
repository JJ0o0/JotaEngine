#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

struct Material {
    int useTexture;

    sampler2D diffuse;
    sampler2D specular;

    vec3 diffuseColor;
    vec3 specularColor;

    float shininess;
};

struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;
};

uniform Material material;

#define MAX_POINT_LIGHTS 32
#define MAX_SPOT_LIGHTS 32
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform DirectionalLight directionalLight;

uniform int pointLightsQuantity;
uniform int spotLightsQuantity;

uniform vec3 viewPos;

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 diffuseC, vec3 specularC, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = light.ambient * diffuseC;
    vec3 diffuse = light.diffuse * diff * diffuseC;
    vec3 specular = light.specular * spec * specularC;

    return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 diffuseC, vec3 specularC, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient = light.ambient * diffuseC;
    vec3 diffuse = light.diffuse * diff * diffuseC;
    vec3 specular = light.specular * spec * specularC;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 CalculateSpotLight(SpotLight light, vec3 diffuseC, vec3 specularC, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 ambient = light.ambient * diffuseC;
    vec3 diffuse = light.diffuse * diff * diffuseC;
    vec3 specular = light.specular * spec * specularC;

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}

void main() {
    vec3 diffuseC = material.useTexture == 1 ? texture(material.diffuse, TexCoord).rgb : material.diffuseColor;
    vec3 specularC = material.useTexture == 1 ? texture(material.specular, TexCoord).rgb : material.specularColor;

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = CalculateDirectionalLight(directionalLight, diffuseC, specularC, norm, viewDir);

    for (int i = 0; i < pointLightsQuantity; i++) {
        result += CalculatePointLight(pointLights[i], diffuseC, specularC, norm, FragPos, viewDir);
    }

    for (int i = 0; i < spotLightsQuantity; i++) {
        result += CalculateSpotLight(spotLights[i], diffuseC, specularC, norm, FragPos, viewDir);
    }

    // result += CalculateSpotLight(spotLight, norm, FragPos, viewDir);

    FragColor = vec4(result, 1.0);
}
