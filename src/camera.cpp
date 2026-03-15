#include "camera.h"

Camera::Camera(glm::vec3 position) : pos(position), worldUp(glm::vec3(0.0f, 1.0f, 0.0f)), yaw(-90.0f), pitch(0.0f), speed(2.5f), sensitivity(0.1f) 
{
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const 
{
    return glm::lookAt(pos, pos + front, up);
}

void Camera::update(const KeyboardState& kbd, const MouseState& mouse, float deltaTime) 
{
    float velocity = speed * deltaTime;
    if (kbd.isDown(GLFW_KEY_W)) pos += front * velocity;
    if (kbd.isDown(GLFW_KEY_S)) pos -= front * velocity;
    if (kbd.isDown(GLFW_KEY_A)) pos -= right * velocity;
    if (kbd.isDown(GLFW_KEY_D)) pos += right * velocity;
    if (kbd.isDown(GLFW_KEY_SPACE)) pos += worldUp * velocity;
    if (kbd.isDown(GLFW_KEY_LEFT_CONTROL)) pos -= worldUp * velocity;

    if (kbd.isDown(GLFW_KEY_UP) && speed < 4.0f) speed += 0.2f;
    if (kbd.isDown(GLFW_KEY_DOWN) && speed > 0.5f) speed -= 0.2f;

    yaw += (float)mouse.deltaX * sensitivity;
    pitch += (float)mouse.deltaY * sensitivity;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

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