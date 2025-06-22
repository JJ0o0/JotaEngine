#include "graphics/ModelLoader.h"
#include "graphics/Vertex.h"

#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

static Mesh* ProcessMesh(aiMesh* mesh) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex v;
        v.Position = glm::vec3(
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        );

        if (mesh->HasNormals()) {
            v.Normal = glm::vec3(
                mesh->mNormals[i].x,
                mesh->mNormals[i].y,
                mesh->mNormals[i].z
            );
        } else {
            v.Normal = glm::vec3(0.0f, 0.0f, 0.0f);
        }

        if (mesh->HasTextureCoords(0)) {
            v.TexCoords = glm::vec2(
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y
            );
        } else {
            v.TexCoords = glm::vec2(0.0f);
        }

        vertices.push_back(v);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    return new Mesh(vertices, indices);
}

Model* ModelLoader::LoadModel(const std::string& path) {
    Assimp::Importer importer;

    std::cout << "[DEBUG] Carregando modelo: " << path << std::endl;
    const aiScene* scene = importer.ReadFile(path,
        aiProcess_Triangulate |
        //aiProcess_FlipUVs |
        aiProcess_GenNormals
    );

    if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
        std::cerr << "Erro com o Assimp! Erro: " << importer.GetErrorString() << std::endl;
        return nullptr;
    }

    std::vector<Mesh*> meshes;
    for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[i];
        meshes.push_back(ProcessMesh(mesh));
    }

    std::cout << "[DEBUG] Modelo carregado! (" << path << ") com " << meshes.size() << " meshes." << std::endl;
    return new Model(meshes);
}