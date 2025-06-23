#pragma once
#include "graphics/Model.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"

struct Material {
    Texture* diffuse;
    Texture* specular;
    Texture* normal;
    float shininess;
};

class Entity {
public:
    Entity(Model* mesh, Shader* shader);

    void SetMaterial(Material mat);
    void Draw();

    void ResetTransform();
    void Translate(glm::vec3 offset);
    void Rotate(glm::vec3 axis);
    void Scale(glm::vec3 scaleFactor);

    void SetPosition(const glm::vec3& pos) { position = pos; UpdateModelMatrix(); }
    void SetRotation(const glm::vec3& rot) { rotation = rot; UpdateModelMatrix(); }
    void SetScale(const glm::vec3& scl) { scale = scl; UpdateModelMatrix(); }

    glm::vec3 GetPosition() const { return position; }
    glm::vec3 GetRotation() const { return rotation; }
    glm::vec3 GetScale() const { return scale; }

    glm::mat4 GetModelMatrix() const;
private:
    Model* model;
    Shader* shader;

    Material material;

    glm::mat4 model_matrix;
    glm::vec3 position = glm::vec3(0.0);
    glm::vec3 rotation = glm::vec3(0.0);
    glm::vec3 scale = glm::vec3(1.0);

    void UpdateModelMatrix();
};