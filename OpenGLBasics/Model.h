#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/material.h>

struct Material {
    glm::vec3 color;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;

    Material() {
        color = glm::vec3(1.0f);
        ambient = glm::vec3(1.0f);
        diffuse = glm::vec3(0.8f);
        specular = glm::vec3(0.5f);
        shininess = 32.0f;
    }

    Material(const Material& other) {
        color = other.color;
        ambient = other.ambient;
        diffuse = other.diffuse;
        specular = other.specular;
        shininess = other.shininess;
    };

    Material(const Material& other, glm::vec3 _color) {
        color = _color;
        ambient = other.ambient;
        diffuse = other.diffuse;
        specular = other.specular;
        shininess = other.shininess;
    };

    Material(glm::vec3 _color) {
        color = _color;
        ambient = glm::vec3(1.0f);
        diffuse = glm::vec3(0.8f);
        specular = glm::vec3(0.5f);
        shininess = 32.0f;
    }

    Material(glm::vec3 _color, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _shininess) {
        color = _color;
        ambient = _ambient;
        diffuse = _diffuse;
        specular = _specular;
        shininess = _shininess;
    }
};

class Model {
public:
    std::vector<Mesh*> Meshes;
    std::vector<Material*> Materials;

    Model();

    Model(const char* filePath);

    Model(Mesh* mesh);

    Model(std::vector<Mesh*>& meshes);

    Model(Mesh* mesh, Material* material);

    Model(std::vector<Mesh*>& meshes, Material* material);

    Model(std::vector<Mesh*>& meshes, std::vector<Material*> materials);

    void SetMaterial(Material* material);
    void SetMaterial(unsigned int materialIndex, Material* material);

private:
    const char* filePath;
    std::string directory;

    void LoadModel(std::string path);
    void ProcessScene(const aiScene* scene);
    Material* ProcessMaterial(aiMaterial* aimaterial);
    Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
};

#endif