#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 T;
out vec3 B;
out vec3 N;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    TexCoords = aTexCoord;

    mat3 normalMatrix = transpose(inverse(mat3(model)));
    T = normalMatrix * aTangent;
    B = normalMatrix * aBitangent;
    N = normalMatrix * aNormal;

    gl_Position = projection * view * vec4(FragPos, 1.0);
}