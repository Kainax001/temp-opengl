#include "transform.h"

Transform::Transform(GLFWwindow* window, InputManager* inputManager) : 
pos(0.0f), speed(0.3f), sensitivity(0.2f),
front(0.0f, 0.0f, 1.0f), right(1.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f),
yaw(0.0f), pitch(0.0f), scale(1.0f), modelMatrix(1.0f)
{
    // Initialize
    this->inputManager = inputManager;
    this->window = window;
}

glm::mat4 Transform::getModelMatrix() { return modelMatrix; }

void Transform::update(float deltaTime)
{
    float velocity = speed * deltaTime;
    if(inputManager->isKeyPressed(GLFW_KEY_I)) pos += front * velocity;
    if(inputManager->isKeyPressed(GLFW_KEY_K)) pos -= front * velocity;
    if(inputManager->isKeyPressed(GLFW_KEY_J)) pos -= right * velocity;
    if(inputManager->isKeyPressed(GLFW_KEY_L)) pos += right * velocity;
    if(inputManager->isKeyPressed(GLFW_KEY_N)) pos += up    * velocity;
    if(inputManager->isKeyPressed(GLFW_KEY_M)) pos -= up    * velocity;

    if(inputManager->isKeyPressed(GLFW_MOUSE_BUTTON_LEFT)) {
        yaw     += (float)inputManager->getMouse().deltaX * sensitivity;
        pitch   += (float)inputManager->getMouse().deltaY * sensitivity;
    }

    updateObjectVectors();
    updateModelMatrix();
}

void Transform::updateObjectVectors()
{
    glm::vec3 f;
    f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    f.y = sin(glm::radians(pitch));
    f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    
    front = glm::normalize(f);
    right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    up    = glm::normalize(glm::cross(right, front));
}

void Transform::updateModelMatrix()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::rotate(model, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(-pitch), glm::vec3(1.0f, 0.0f, 0.0f));

    model = glm::scale(model, scale);
    
    modelMatrix = model;
}