#include "camera.h"

Camera::Camera(glm::vec3 position, InputManager* inputManager) : pos(position), worldUp(glm::vec3(0.0f, 1.0f, 0.0f)), yaw(-90.0f), pitch(0.0f), speed(2.5f), sensitivity(0.1f) 
{
    this->inputManager = inputManager;
    this->window = window;
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const 
{
    return glm::lookAt(pos, pos + front, up);
}

glm::vec3 Camera::getPos()
{
    return pos;
}

void Camera::update(float deltaTime) 
{
    float velocity = speed * deltaTime;
    if (inputManager->isKeyPressed(GLFW_KEY_W)) pos += front * velocity;
    if (inputManager->isKeyPressed(GLFW_KEY_S)) pos -= front * velocity;
    if (inputManager->isKeyPressed(GLFW_KEY_A)) pos -= right * velocity;
    if (inputManager->isKeyPressed(GLFW_KEY_D)) pos += right * velocity;
    if (inputManager->isKeyPressed(GLFW_KEY_SPACE)) pos += worldUp * velocity;
    if (inputManager->isKeyPressed(GLFW_KEY_LEFT_CONTROL)) pos -= worldUp * velocity;

    if (inputManager->isKeyPressed(GLFW_KEY_UP) && speed < 4.0f) speed += 0.2f;
    if (inputManager->isKeyPressed(GLFW_KEY_DOWN) && speed > 0.5f) speed -= 0.2f;

    if (!inputManager->isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
        yaw += (float)inputManager->getMouse().deltaX * sensitivity;
    pitch += (float)inputManager->getMouse().deltaY * sensitivity;
    
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::updateCameraVectors() 
{
    glm::vec3 f;
    f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    f.y = sin(glm::radians(pitch));
    f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    
    front = glm::normalize(f);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}