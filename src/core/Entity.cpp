#include "core/Entity.h"
#include "glm/ext/matrix_transform.hpp"

Entity::Entity(Model* m, Shader* s) 
: model(m), shader(s), model_matrix(glm::mat4(1.0f)) {
    material = {nullptr, nullptr, nullptr, 32.0f};
}

void Entity::SetMaterial(Material mat) { 
    material = mat;
}

void Entity::ResetTransform() {
    model_matrix = glm::mat4(1.0f);
}

void Entity::Translate(glm::vec3 offset) {
    position += offset;

    UpdateModelMatrix();
}

void Entity::Rotate(glm::vec3 axis) {
    rotation += axis;

    UpdateModelMatrix();
}

void Entity::Scale(glm::vec3 scaleFactor) {
    scale *= scaleFactor;

    UpdateModelMatrix();
}

glm::mat4 Entity::GetModelMatrix() const {
    return model_matrix;
}

void Entity::Draw() {
    if (!model || !shader) return;

    shader->Use();
    shader->SetUniformMat4("model", model_matrix);

    bool hasTextures = (material.diffuse && material.specular);
    bool hasNormalMap = material.normal;

    shader->SetUniform1i("useTexture", hasTextures);
    shader->SetUniform1i("useNormalMap", hasNormalMap);
    shader->SetUniformVec3("color", glm::vec3(1.0f));
    shader->SetUniform1f("material.shininess", material.shininess);

    if (hasTextures) {
        shader->SetUniform1i("material.diffuse", 0);
        shader->SetUniform1i("material.specular", 1);
        
        material.diffuse->Bind(0);
        material.specular->Bind(1);
    }

    if (hasNormalMap) {
        shader->SetUniform1i("material.normal", 2);

        material.normal->Bind(2);
    }

    model->Draw(shader);

    if (hasTextures) {
        material.diffuse->Unbind();
        material.specular->Unbind();
    }

    if (hasNormalMap) {
        material.normal->Unbind();
    }
}

void Entity::UpdateModelMatrix() {
    model_matrix = glm::mat4(1.0f);

    model_matrix = glm::translate(model_matrix, position);

    model_matrix = glm::rotate(model_matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    model_matrix = glm::rotate(model_matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    model_matrix = glm::rotate(model_matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));

    model_matrix = glm::scale(model_matrix, scale);
}
