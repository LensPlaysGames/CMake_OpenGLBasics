#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <vector>
#include "Model.h"

class Primitives {
public:
    static glm::vec3 GetFaceNormal(glm::vec3 A, glm::vec3 B, glm::vec3 C) {
        // Given three non-aligned points on a plane ABC, the normal can be calculated as follows:
        // u = B - A
        // v = C - A
        // normal = u * v
        // TODO: Add colinear check.
        return glm::normalize(glm::cross(B - A, C - A));
    }

    /* EQUILATERAL TRIANGLE */
    static Model Triangle() {
        std::vector<Vertex> vertices(3, Vertex());
        vertices[0].Position = glm::vec3(-0.5f, -0.5f, 0.0f);
        vertices[0].Normal = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[0].Color = glm::vec3(0.0f, 1.0f, 0.0f);
        vertices[0].TexCoords = glm::vec2(0.0f, 0.0f);
        vertices[1].Position = glm::vec3(0.0f, 0.366f, 0.0f);
        vertices[1].Normal = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[1].Color = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[1].TexCoords = glm::vec2(0.5f, 1.0f);
        vertices[2].Position = glm::vec3(0.5f, -0.5f, 0.0f);
        vertices[2].Normal = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[2].Color = glm::vec3(1.0f, 0.0f, 0.0f);
        vertices[2].TexCoords = glm::vec2(1.0f, 0.0f);

        std::vector<unsigned int> indices = { 2, 1, 0 };

        return Model(new Mesh(vertices, indices));
    }

    static Model Square() {
        /* SQUARE */
        std::vector<Vertex> vertices(4, Vertex());
        vertices[0].Position = glm::vec3(-0.5f, -0.5f, 0.0f); // Bottom left
        vertices[0].Normal = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[0].Color = glm::vec3(1.0f, 1.0f, 1.0f);
        vertices[0].TexCoords = glm::vec2(0.0f, 0.0f);
        vertices[1].Position = glm::vec3(-0.5f, 0.5f, 0.0f);  // Top left
        vertices[1].Normal = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[1].Color = glm::vec3(1.0f, 0.0f, 0.0f);
        vertices[1].TexCoords = glm::vec2(0.0f, 1.0f);
        vertices[2].Position = glm::vec3(0.5f, -0.5f, 0.0f);  // Bottom right
        vertices[2].Normal = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[2].Color = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[2].TexCoords = glm::vec2(1.0f, 0.0f);
        vertices[3].Position = glm::vec3(0.5f, 0.5f, 0.0f);   // Top right
        vertices[3].Normal = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[3].Color = glm::vec3(0.0f, 1.0f, 0.0f);
        vertices[3].TexCoords = glm::vec2(1.0f, 1.0f);

        std::vector<unsigned int> indices = {
            // Vertex order: bottom left, top left, bottom right, top right
            // Triangle indices CCW order: bl, br, tl, tl, br, tr
            0, 2, 1,
            1, 2, 3
        };

        return Model(new Mesh(vertices, indices));
    }

    static Model Cube() {
        /* UNIT CUBE */
        std::vector<Vertex> vertices(24, Vertex());
        // FRONT FACE
        vertices[0].Position = glm::vec3(-0.5f, -0.5f, 0.5f);   // Front bottom left
        vertices[0].Normal = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[0].Color = glm::vec3(0.0f);
        vertices[0].TexCoords = glm::vec2(0.0f);
        vertices[1].Position = glm::vec3(-0.5f, 0.5f, 0.5f);    // Front top left
        vertices[1].Normal = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[1].Color = glm::vec3(1.0f, 0.0f, 0.0f);
        vertices[1].TexCoords = glm::vec2(0.0f, 1.0f);
        vertices[2].Position = glm::vec3(0.5f, -0.5f, 0.5f);    // Front bottom right
        vertices[2].Normal = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[2].Color = glm::vec3(0.0f, 1.0f, 0.0f);
        vertices[2].TexCoords = glm::vec2(1.0f, 0.0f);
        vertices[3].Position = glm::vec3(0.5f, 0.5f, 0.5f);     // Front top right
        vertices[3].Normal = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[3].Color = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[3].TexCoords = glm::vec2(1.0f);
        // BACK FACE
        vertices[4].Position = glm::vec3(0.5f, -0.5f, -0.5f);   // Back bottom left
        vertices[4].Normal = glm::vec3(0.0f, 0.0f, -1.0f);
        vertices[4].Color = glm::vec3(0.0f);
        vertices[4].TexCoords = glm::vec2(0.0f);
        vertices[5].Position = glm::vec3(0.5f, 0.5f, -0.5f);    // Back top left
        vertices[5].Normal = glm::vec3(0.0f, 0.0f, -1.0f);
        vertices[5].Color = glm::vec3(1.0f, 0.0f, 0.0f);
        vertices[5].TexCoords = glm::vec2(0.0f, 1.0f);
        vertices[6].Position = glm::vec3(-0.5f);                // Back bottom right
        vertices[6].Normal = glm::vec3(0.0f, 0.0f, -1.0f);
        vertices[6].Color = glm::vec3(0.0f, 1.0f, 0.0f);
        vertices[6].TexCoords = glm::vec2(1.0f, 0.0f);
        vertices[7].Position = glm::vec3(-0.5f, 0.5f, -0.5f);   // Back top right
        vertices[7].Normal = glm::vec3(0.0f, 0.0f, -1.0f);
        vertices[7].Color = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[7].TexCoords = glm::vec2(1.0f);
        // LEFT FACE
        vertices[8].Position = glm::vec3(-0.5f);                // Left bottom left
        vertices[8].Normal = glm::vec3(-1.0f, 0.0f, 0.0f);
        vertices[8].Color = glm::vec3(0.0f);
        vertices[8].TexCoords = glm::vec2(0.0f);
        vertices[9].Position = glm::vec3(-0.5f, 0.5f, -0.5f);   // Left top left
        vertices[9].Normal = glm::vec3(-1.0f, 0.0f, 0.0f);
        vertices[9].Color = glm::vec3(1.0f, 0.0f, 0.0f);
        vertices[9].TexCoords = glm::vec2(0.0f, 1.0f);
        vertices[10].Position = glm::vec3(-0.5f, -0.5f, 0.5f);  // Left bottom right
        vertices[10].Normal = glm::vec3(-1.0f, 0.0f, 0.0f);
        vertices[10].Color = glm::vec3(0.0f, 1.0f, 0.0f);
        vertices[10].TexCoords = glm::vec2(1.0f, 0.0f);
        vertices[11].Position = glm::vec3(-0.5f, 0.5f, 0.5f);   // Left top right
        vertices[11].Normal = glm::vec3(-1.0f, 0.0f, 0.0f);
        vertices[11].Color = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[11].TexCoords = glm::vec2(1.0f);
        // RIGHT FACE
        vertices[12].Position = glm::vec3(0.5f, -0.5f, 0.5f);   // Right bottom left
        vertices[12].Normal = glm::vec3(1.0f, 0.0f, 0.0f);
        vertices[12].Color = glm::vec3(0.0f);
        vertices[12].TexCoords = glm::vec2(0.0f);
        vertices[13].Position = glm::vec3(0.5f, 0.5f, 0.5f);    // Right top left
        vertices[13].Normal = glm::vec3(1.0f, 0.0f, 0.0f);
        vertices[13].Color = glm::vec3(1.0f, 0.0f, 0.0f);
        vertices[13].TexCoords = glm::vec2(0.0f, 1.0f);
        vertices[14].Position = glm::vec3(0.5f, -0.5f, -0.5f);  // Right bottom right
        vertices[14].Normal = glm::vec3(1.0f, 0.0f, 0.0f);
        vertices[14].Color = glm::vec3(0.0f, 1.0f, 0.0f);
        vertices[14].TexCoords = glm::vec2(1.0f, 0.0f);
        vertices[15].Position = glm::vec3(0.5f, 0.5f, -0.5f);   // Right top right
        vertices[15].Normal = glm::vec3(1.0f, 0.0f, 0.0f);
        vertices[15].Color = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[15].TexCoords = glm::vec2(1.0f);
        // TOP FACE
        vertices[16].Position = glm::vec3(-0.5f, 0.5f, 0.5f);    // Top bottom left
        vertices[16].Normal = glm::vec3(0.0f, 1.0f, 0.0f);
        vertices[16].Color = glm::vec3(0.0f);
        vertices[16].TexCoords = glm::vec2(0.0f);
        vertices[17].Position = glm::vec3(-0.5f, 0.5f, -0.5f);   // Top top left
        vertices[17].Normal = glm::vec3(0.0f, 1.0f, 0.0f);
        vertices[17].Color = glm::vec3(1.0f, 0.0f, 0.0f);
        vertices[17].TexCoords = glm::vec2(0.0f, 1.0f);
        vertices[18].Position = glm::vec3(0.5f, 0.5f, 0.5f);     // Top bottom right
        vertices[18].Normal = glm::vec3(0.0f, 1.0f, 0.0f);
        vertices[18].Color = glm::vec3(0.0f, 1.0f, 0.0f);
        vertices[18].TexCoords = glm::vec2(1.0f, 0.0f);
        vertices[19].Position = glm::vec3(0.5f, 0.5f, -0.5f);    // Top top right
        vertices[19].Normal = glm::vec3(0.0f, 1.0f, 0.0f);
        vertices[19].Color = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[19].TexCoords = glm::vec2(1.0f);
        // BOTTOM FACE
        vertices[20].Position = glm::vec3(-0.5f);               // Bottom bottom left
        vertices[20].Normal = glm::vec3(0.0f, -1.0f, 0.0f);
        vertices[20].Color = glm::vec3(0.0f);
        vertices[20].TexCoords = glm::vec2(0.0f);
        vertices[21].Position = glm::vec3(-0.5f, -0.5f, 0.5f);  // Bottom top left
        vertices[21].Normal = glm::vec3(0.0f, -1.0f, 0.0f);
        vertices[21].Color = glm::vec3(1.0f, 0.0f, 0.0f);
        vertices[21].TexCoords = glm::vec2(0.0f, 1.0f);
        vertices[22].Position = glm::vec3(0.5f, -0.5f, -0.5f);  // Bottom bottom right
        vertices[22].Normal = glm::vec3(0.0f, -1.0f, 0.0f);
        vertices[22].Color = glm::vec3(0.0f, 1.0f, 0.0f);
        vertices[22].TexCoords = glm::vec2(1.0f, 0.0f);
        vertices[23].Position = glm::vec3(0.5f, -0.5f, 0.5f);   // Bottom top right
        vertices[23].Normal = glm::vec3(0.0f, -1.0f, 0.0f);
        vertices[23].Color = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[23].TexCoords = glm::vec2(1.0f);

        std::vector<unsigned int> indices = {
            // Face order: front, back, left, right, top, bottom
            // Vertex order per face: bottom left, top left, bottom right, top right
            // Triangle indices CCW order per face: bl, br, tl, tl, br, tr
            0,2,1, 1,2,3,
            4,6,5, 5,6,7,
            8,10,9, 9,10,11,
            12,14,13, 13,14,15,
            16,18,17, 17,18,19,
            20,22,21, 21,22,23
        };

        return Model(new Mesh(vertices, indices));
    }

    static Model Pyramid() {
        /* PYRAMID */
        std::vector<Vertex> vertices(16, Vertex());
        // BOTTOM SQUARE
        vertices[0].Position = glm::vec3(-0.5f, 0.0f, -0.5f);    // Bottom bottom left
        vertices[0].Normal = glm::vec3(0.0f, -1.0f, 0.0f);
        vertices[0].Color = glm::vec3(0.0f);
        vertices[0].TexCoords = glm::vec2(0.0f, 0.0f);
        vertices[1].Position = glm::vec3(-0.5f, 0.0f, 0.5f);     // Bottom top left
        vertices[1].Normal = glm::vec3(0.0f, -1.0f, 0.0f);
        vertices[1].Color = glm::vec3(1.0f, 0.0f, 0.0f);
        vertices[1].TexCoords = glm::vec2(0.0f, 1.0f);
        vertices[2].Position = glm::vec3(0.5f, 0.0f, -0.5f);     // Bottom bottom right
        vertices[2].Normal = glm::vec3(0.0f, -1.0f, 0.0f);
        vertices[2].Color = glm::vec3(0.0f, 1.0f, 0.0f);
        vertices[2].TexCoords = glm::vec2(1.0f, 0.0f);
        vertices[3].Position = glm::vec3(0.5f, 0.0f, 0.5f);      // Bottom top right
        vertices[3].Normal = glm::vec3(0.0f, -1.0f, 0.0f);
        vertices[3].Color = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[3].TexCoords = glm::vec2(1.0f);
        // FRONT FACE
        glm::vec3 A(0.0f, 1.0f, 0.0f);  // Pyramid tip
        glm::vec3 B(-0.5f, 0.0f, 0.5f); // Bottom top left
        glm::vec3 C(0.5f, 0.0f, 0.5f);  // Bottom top right
        glm::vec3 normal = GetFaceNormal(A, B, C);
        vertices[4].Position = A;
        vertices[4].Normal = normal;
        vertices[4].Color = glm::vec3(0.0f);
        vertices[4].TexCoords = glm::vec2(0.5f, 1.0f);
        vertices[5].Position = B;
        vertices[5].Normal = normal;
        vertices[5].Color = glm::vec3(0.0f);
        vertices[5].TexCoords = glm::vec2(0.0f);
        vertices[6].Position = C;
        vertices[6].Normal = normal;
        vertices[6].Color = glm::vec3(0.0f);
        vertices[6].TexCoords = glm::vec2(1.0f, 0.0f);
        // BACK FACE
        B = glm::vec3(0.5f, 0.0f, -0.5f);   // Bottom bottom right
        C = glm::vec3(-0.5f, 0.0f, -0.5f);  // Bottom bottom left
        normal = GetFaceNormal(A, B, C);
        vertices[7].Position = A;
        vertices[7].Normal = normal;
        vertices[7].Color = glm::vec3(0.0f);
        vertices[7].TexCoords = glm::vec2(0.5f, 1.0f);
        vertices[8].Position = B;
        vertices[8].Normal = normal;
        vertices[8].Color = glm::vec3(0.0f);
        vertices[8].TexCoords = glm::vec2(0.0f);
        vertices[9].Position = C;
        vertices[9].Normal = normal;
        vertices[9].Color = glm::vec3(0.0f);
        vertices[9].TexCoords = glm::vec2(1.0f, 0.0f);
        // LEFT FACE
        B = glm::vec3(-0.5f, 0.0f, -0.5f);  // Bottom bottom left
        C = glm::vec3(-0.5f, 0.0f, 0.5f);   // Bottom top left
        normal = GetFaceNormal(A, B, C);
        vertices[10].Position = A;
        vertices[10].Normal = normal;
        vertices[10].Color = glm::vec3(0.0f);
        vertices[10].TexCoords = glm::vec2(0.5f, 1.0f);
        vertices[11].Position = B;
        vertices[11].Normal = normal;
        vertices[11].Color = glm::vec3(0.0f);
        vertices[11].TexCoords = glm::vec2(0.0f);
        vertices[12].Position = C;
        vertices[12].Normal = normal;
        vertices[12].Color = glm::vec3(0.0f);
        vertices[12].TexCoords = glm::vec2(1.0f, 0.0f);
        // RIGHT FACE
        B = glm::vec3(0.5f, 0.0f, 0.5f);    // Bottom top right
        C = glm::vec3(0.5f, 0.0f, -0.5f);   // Bottom bottom right
        normal = GetFaceNormal(A, B, C);
        vertices[13].Position = A;
        vertices[13].Normal = normal;
        vertices[13].Color = glm::vec3(0.0f);
        vertices[13].TexCoords = glm::vec2(0.5f, 1.0f);
        vertices[14].Position = B;
        vertices[14].Normal = normal;
        vertices[14].Color = glm::vec3(0.0f);
        vertices[14].TexCoords = glm::vec2(0.0f);
        vertices[15].Position = C;
        vertices[15].Normal = normal;
        vertices[15].Color = glm::vec3(0.0f);
        vertices[15].TexCoords = glm::vec2(1.0f, 0.0f);

        std::vector<unsigned int> indices = {
            // Triangle order: Bottom_1, Bottom_2, Front, Back, Left, Right
            // Square face vertex order: bl, br, tl, tl, br, tr
            // Triangle face vertex order: top, bl, br
            0, 2, 1,
            1, 2, 3,
            4, 5, 6,
            7, 8, 9,
            10, 11, 12,
            13, 14, 15
        };

        return Model(new Mesh(vertices, indices));
    }
};

#endif