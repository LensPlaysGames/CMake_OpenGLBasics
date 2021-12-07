#include "Mesh.h"

Mesh::Mesh(){
    VAO = 0;
    VBO = 0;
    EBO = 0;
    materialIndex = 0;
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
    Vertices = vertices;
    Indices = indices;
    VAO = 0;
    VBO = 0;
    EBO = 0;
    materialIndex = 0;

    SetupMesh();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, unsigned int _materialIndex)
{
    Vertices = vertices;
    Indices = indices;
    VAO = 0;
    VBO = 0;
    EBO = 0;
    materialIndex = _materialIndex;

    SetupMesh();
}



Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Mesh::SetupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind vertex array to write buffers into.
    glBindVertexArray(VAO);

    // Bind + write vertex buffer.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);
    // Bind + write index buffer.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), &Indices[0], GL_STATIC_DRAW);

    // Arrange byte layout of attributes to send to shader.
    // Attribute Zero: Position (3 floats: x, y, z)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
    // Attribute One: Normal (3 floats: x, y, z)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // Attribute Two: Color (3 floats: r, g, b)
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
    // Attribute Three: UV Coordinates (2 floats: x, y)
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    // Unbind vertex array.
    glBindVertexArray(0);
}