#version 330 core
out vec4 FragColor;
in vec3 FragPos;
in vec2 TexCoords;
in vec3 T;
in vec3 B;
in vec3 N;

uniform vec3 color;
uniform vec3 lightColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform bool useTexture;
uniform bool useNormalMap;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;
    float shininess;
};

uniform Material material;

void main() {
    // --- Definindo normal ---
    mat3 TBN = mat3(normalize(T), normalize(B), normalize(N));
    vec3 norm;

    if (useNormalMap) {
        // Normal do normal map (de [0,1] pra [-1,1]) e transforma com TBN
        vec3 normalMap = texture(material.normal, TexCoords).rgb;
        normalMap = normalize(normalMap * 2.0 - 1.0);
        norm = normalize(TBN * normalMap);
    } else {
        norm = normalize(N);
    }

    // --- Luz ambiente simples (para dar uma luz base no objeto) ---
    float ambientStrength = 0.1;
    vec3 ambient;
    if (useTexture) {
        // Amplitude da luz ambiente * cor da luz * cor da textura difusa
        ambient = ambientStrength * lightColor * vec3(texture(material.diffuse, TexCoords));
    } else {
        // Se não usar textura, usa cor base do objeto
        ambient = ambientStrength * lightColor * color;
    }

    // --- Luz difusa (luz direta, depende do ângulo da luz com a normal) ---
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0); // max pra garantir sem valores negativos

    vec3 diffuse;
    if (useTexture) {
        diffuse = diff * lightColor * vec3(texture(material.diffuse, TexCoords));
    } else {
        diffuse = diff * lightColor * color;
    }

    // --- Luz especular (reflexo da luz, cria brilho) ---
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    // Cuidado: pow com shininess alto = brilho pequeno e concentrado
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 specular;
    if (useTexture) {
        specular = lightColor * spec * vec3(texture(material.specular, TexCoords));
    } else {
        specular = lightColor * spec * vec3(1.0); // cor branca para brilho padrão
    }

    // --- Soma tudo (ambient + diffuse + specular) pra cor final ---
    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0); // Alfa 1.0, sem transparência
}