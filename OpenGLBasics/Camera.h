#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

class Camera
{
    public:
        // Global vectors (won't ever change).
        const glm::vec3 g_FORWARD = glm::vec3(0.0f, 0.0f, -1.0f);
        const glm::vec3 g_UP = glm::vec3(0.0f, 1.0f, 0.0f);
        const glm::vec3 g_RIGHT = glm::vec3(1.0f, 0.0f, 0.0f);

        // Transformation Matrices
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        // Camera settings (static).
        const float MaxVerticalAngle = 89.0f;
        const float InitialSpeed = 2.5f;

        // Camera settings (dynamic).
        float Sensitivity = 25.0f;
        float Speed = InitialSpeed;

        glm::vec3 Position = glm::vec3(0.0f, 0.0f, 5.0f);
        glm::vec3 Forward = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 Right = glm::vec3(1.0f, 0.0f, 0.0f);
        glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

        double Pitch = 0.0;
        double Yaw = 270.0;

        int Width;
        int Height;

        bool FirstClick = true;
        glm::vec2 LastMousePos = glm::vec2(640.0f, 360.0f);

        Camera(int width, int height, glm::vec3 position);

        void Update(GLFWwindow* window);

        void UpdateMatrices(float FOVDeg, float nearPlane, float farPlane);

        void Inputs(GLFWwindow* window);

        void UpdateScreenSize(int width, int height);
};

#endif