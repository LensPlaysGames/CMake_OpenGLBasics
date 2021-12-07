#version 460 core

struct Material {
    vec3 color;
}; 

out vec4 FragColor;

uniform Material _Material;

void main()
{
    FragColor = vec4(_Material.color, 1.0);
}