#ifndef MESH_H
#define MESH_H

#include <vector>

#include "Shader.h"

#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 Color;
    glm::vec2 TexCoords;
};

class Mesh {
public:
    // Refers to index of Material in Materials list of Model.
    unsigned int materialIndex;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    // Vertex array object.
    GLuint VAO;

    Mesh();
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, unsigned int _materialIndex);
    ~Mesh();

private:
    // Vertex and Element buffer objects.
    GLuint VBO, EBO;

    void SetupMesh();
};

#endif