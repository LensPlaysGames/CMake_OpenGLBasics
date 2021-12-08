#include "Camera.h"
#include "Timer.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(int width, int height, glm::vec3 position) {
    Width = width;
    Height = height;
    Position = position;
}

void Camera::Update(GLFWwindow* window) {
    Inputs(window);
    UpdateMatrices(FOV, NearPlane, FarPlane);
}

void Camera::UpdateMatrices(float FOVDeg, float nearPlane, float farPlane) {
    view = glm::lookAt(Position, Position + Forward, g_UP);
    projection = glm::perspective(FOVDeg, (float)Width/Height, nearPlane, farPlane);
    //projection = glm::ortho(-25.0f, 25.0f, -25.0f, 25.0f, nearPlane, farPlane);
}

void Camera::UpdateScreenSize(int width, int height){
    Width = width;
    Height = height;
}

void Camera::ChangeFOV(float FOVChangeInDegrees)
{
    FOV += ZoomSensitivity * glm::radians(FOVChangeInDegrees);
    FOV = std::max(MinFOVRadians, std::min(FOV, MaxFOVRadians));
}

void Camera::ResetFOV() { FOV = glm::radians(StartFOVDegrees); }

/* Gather inputs using GLFW and then move accordingly.
*   TODO: Change to event based where when key is pressed the event calls an action using glfwSetKeyCallback()
*/
void Camera::Inputs(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){ Speed = Timer::deltaTime * InitialSpeed * 4.0f; }
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) { Speed = Timer::deltaTime * InitialSpeed; }

    // Basic movement (localized to look direction).
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){ Position += Speed * Forward; }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { Position += Speed * Right; }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { Position -= Speed * Forward; }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { Position -= Speed * Right; }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) { Position += Speed * Up; }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) { Position -= Speed * Up; }

    // Rotation (Trigonometry is greater than 1 Rylan brain).
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        double xPos = 0.0, yPos = 0.0, xDiff = 0.0, yDiff = 0.0;

        if (FirstClick) {
            glfwSetCursorPos(window, Width / 2.0f, Height / 2.0f);
            LastMousePos = glm::vec2(Width / 2.0f, Height/  2.0f);
            FirstClick = false;
        }
        else {
            // Get mouse difference in position from last frame.
            glfwGetCursorPos(window, &xPos, &yPos);
            xDiff = Timer::deltaTime * LookSensitivity * (xPos - LastMousePos.x);
            yDiff = Timer::deltaTime * LookSensitivity * (yPos - LastMousePos.y);
            LastMousePos = glm::vec2(xPos, yPos);
            Pitch += yDiff;
            Yaw += xDiff;

            // Validate pitch (don't look too far down or up).
            if (-Pitch > MaxVerticalAngle) Pitch = -MaxVerticalAngle;
            else if (-Pitch < -MaxVerticalAngle) Pitch = MaxVerticalAngle;

            // Calculate forward from pitch + yaw angles.
            Forward.x = cos(glm::radians(Yaw)) * cos(glm::radians(-Pitch));
            Forward.y = sin(glm::radians(-Pitch));
            Forward.z = sin(glm::radians(Yaw)) * cos(glm::radians(-Pitch));

            // Update local directions.
            Forward = glm::normalize(Forward);
            Right = glm::normalize(glm::cross(g_UP, Forward));
            Up = glm::normalize(glm::cross(Forward, Right));
        }
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        FirstClick = true;
    }
}
