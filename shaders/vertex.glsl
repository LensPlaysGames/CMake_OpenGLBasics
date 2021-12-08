#version 330 core

// layout refers to where in the buffer to get the data based on location + stride.
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexCoords;

out vec3 FragPositionInWorld;
out vec3 VertexColor;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    vec4 position = vec4(aPosition, 1.0);
    FragPositionInWorld = vec3(model * position);
    Normal = normalize(mat3(transpose(inverse(model))) * aNormal);
    VertexColor = aColor;
    TexCoords = aTexCoords;
    gl_Position = projection * view * model * position;
}