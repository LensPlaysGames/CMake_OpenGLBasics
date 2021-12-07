#version 460 core

float near = 0.1;
float far = 500.0;

out vec4 FragColor;

float LinearizeDepth(float depth){
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{
    FragColor = vec4(vec3(1-(LinearizeDepth(gl_FragCoord.z) / far)), 1.0);
}