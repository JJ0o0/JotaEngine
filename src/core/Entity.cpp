#include "core/Entity.h"
#include "glm/ext/matrix_transform.hpp"

Entity::Entity(Model* m, Shader* s) 
: model(m), shader(s), model_matrix(glm::mat4(1.0f)) {}

void Entity::SetTexture(Texture* t) { 
    texture = t; 
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
    if (!model) {
        return;
    }

    if (!shader) {
        return;
    }

    shader->Use();
    shader->SetUniformMat4("model", model_matrix);

    if (texture) {
        shader->SetUniform1i("useTexture", 1);
        shader->SetUniformVec3("color", glm::vec3(1.0f));
        shader->SetUniform1i("texture0", 0);
        texture->Bind(0);
    } else {
        shader->SetUniform1i("useTexture", 0);
        shader->SetUniformVec3("color", glm::vec3(1.0f));
    }

    model->Draw(shader);

    if (texture) texture->Unbind();
}

void Entity::UpdateModelMatrix() {
    model_matrix = glm::mat4(1.0f);

    model_matrix = glm::translate(model_matrix, position);

    model_matrix = glm::rotate(model_matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    model_matrix = glm::rotate(model_matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    model_matrix = glm::rotate(model_matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));

    model_matrix = glm::scale(model_matrix, scale);
}
