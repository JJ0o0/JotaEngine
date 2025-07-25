#include "engine/MeshCreator.hpp"
#include "assimp/material.h"
#include "assimp/types.h"
#include "core/Texture.hpp"
#include "engine/ResourceManager.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <filesystem>
#include <iostream>
#include <string>

std::shared_ptr<Mesh> MeshCreator::CreatePlane() {
  std::vector<Vertex> vertices = {
      {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0, 1}},
      {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1, 1}},
      {{0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1, 0}},
      {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0, 0}},
  };

  std::vector<unsigned int> indices = {0, 1, 2, 2, 3, 0};

  return std::make_shared<Mesh>(vertices, indices);
}

std::shared_ptr<Mesh> MeshCreator::CreateCube() {
  std::vector<Vertex> vertices = {
      // Frente
      {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
      {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
      {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
      {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

      // Traseira
      {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
      {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
      {{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
      {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},

      // Esquerda
      {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
      {{-0.5f, -0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
      {{-0.5f, 0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
      {{-0.5f, 0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

      // Direita
      {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
      {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
      {{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
      {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

      // Cima
      {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
      {{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
      {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
      {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},

      // Baixo
      {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
      {{0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
      {{0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
      {{-0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
  };

  std::vector<unsigned int> indices = {
      0,  1,  2,  2,  3,  0,  // Frente
      4,  5,  6,  6,  7,  4,  // Traseira
      8,  9,  10, 10, 11, 8,  // Esquerda
      12, 13, 14, 14, 15, 12, // Direita
      16, 17, 18, 18, 19, 16, // Cima
      20, 21, 22, 22, 23, 20  // Baixo
  };

  return std::make_shared<Mesh>(vertices, indices);
}

std::shared_ptr<Model> MeshCreator::LoadModel(const std::string &path) {
  Assimp::Importer importer;

  const aiScene *scene = importer.ReadFile(
      path, aiProcess_Triangulate | aiProcess_FlipUVs |
                aiProcess_CalcTangentSpace | aiProcess_GenNormals);

  if (!scene || !scene->mRootNode ||
      scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
    std::cerr << "Erro Assimp: " << importer.GetErrorString() << std::endl;

    return nullptr;
  }

  auto model = std::make_shared<Model>();

  std::string fileName = GetFileName(path);

  for (unsigned int m = 0; m < scene->mNumMeshes; m++) {
    aiMesh *mesh = scene->mMeshes[m];

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
      Vertex vertex;

      vertex.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y,
                                  mesh->mVertices[i].z);

      if (mesh->HasNormals()) {
        vertex.Normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y,
                                  mesh->mNormals[i].z);
      } else {
        vertex.Normal = glm::vec3(0.0f);
      }

      if (mesh->mTextureCoords[0]) {
        vertex.TexCoords = glm::vec2(mesh->mTextureCoords[0][i].x,
                                     mesh->mTextureCoords[0][i].y);
      } else {
        vertex.TexCoords = glm::vec2(0.0f);
      }

      vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
      aiFace face = mesh->mFaces[i];

      for (unsigned int j = 0; j < face.mNumIndices; j++) {
        indices.push_back(face.mIndices[j]);
      }
    }

    auto newMesh = ResourceManager::LoadMesh(
        fileName + "_mesh_" + std::to_string(m), vertices, indices);

    model->AddMesh(newMesh);
  }

  for (unsigned int m = 0; m < scene->mNumMaterials; m++) {
    aiMaterial *material = scene->mMaterials[m];

    aiString diffusePath, specularPath;
    std::string diffuseName =
        fileName + "_texture_diffuse_" + std::to_string(m);
    std::string specularName =
        fileName + "_texture_specular_" + std::to_string(m);

    std::shared_ptr<Texture> diffuseTexture = nullptr;
    std::shared_ptr<Texture> specularTexture = nullptr;

    aiColor3D diffuseColor(1.0f, 1.0f, 1.0f);
    aiColor3D specularColor(1.0f, 1.0f, 1.0f);

    std::string directory = path.substr(0, path.find_last_of("/\\"));

    if (material->GetTexture(aiTextureType_DIFFUSE, 0, &diffusePath) ==
        AI_SUCCESS) {
      std::string diffusePathC = diffusePath.C_Str();
      std::string fullTexPath = directory + "/" + diffusePathC;

      diffuseTexture = ResourceManager::LoadTexture(diffuseName, fullTexPath);
    } else {
      material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor);
    }

    if (material->GetTexture(aiTextureType_SPECULAR, 0, &specularPath) ==
        AI_SUCCESS) {
      std::string specularPathC = specularPath.C_Str();
      std::string fullTexPath = directory + "/" + specularPathC;

      specularTexture = ResourceManager::LoadTexture(specularName, fullTexPath);
    } else {
      material->Get(AI_MATKEY_COLOR_SPECULAR, specularColor);
    }

    float shininess = 32.0f;
    material->Get(AI_MATKEY_SHININESS, shininess);

    glm::vec3 glm_diffuseColor(diffuseColor.r, diffuseColor.g, diffuseColor.b);
    glm::vec3 glm_specularColor(specularColor.r, specularColor.g,
                                specularColor.b);

    std::string materialName = fileName + "_material_" + std::to_string(m);
    if (diffuseTexture || specularTexture) {
      auto mat = ResourceManager::LoadMaterial(materialName, diffuseTexture,
                                               specularTexture, shininess);

      model->AddMaterial(mat);
    } else {
      auto mat = ResourceManager::LoadMaterial(materialName, glm_diffuseColor,
                                               glm_specularColor, shininess);

      model->AddMaterial(mat);
    }
  }

  return model;
}

std::string MeshCreator::GetFileName(const std::string &path) {
  size_t lastSlash = path.find_last_of("/\\");
  size_t start = (lastSlash == std::string::npos) ? 0 : lastSlash + 1;

  size_t lastDot = path.find_last_of('.');
  size_t end = (lastDot == std::string::npos || lastDot < start) ? path.length()
                                                                 : lastDot;

  return path.substr(start, end - start);
}
