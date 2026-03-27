#include "transform.h"

Transform::Transform(InputManager* inputManager) 
{
    // Initialize
    this->inputManager = inputManager;
}
Transform::~Transform() {}

glm::mat4 Transform::getModelMatrix() { return modelMatrix; }

void Transform::update(float deltaTime)
{
    float velocity = speed * deltaTime;
    if(inputManager->isKeyPressed(GLFW_KEY_I)) statusInfo.pos += statusInfo.front * velocity;
    if(inputManager->isKeyPressed(GLFW_KEY_K)) statusInfo.pos -= statusInfo.front * velocity;
    if(inputManager->isKeyPressed(GLFW_KEY_J)) statusInfo.pos -= statusInfo.right * velocity;
    if(inputManager->isKeyPressed(GLFW_KEY_L)) statusInfo.pos += statusInfo.right * velocity;
    if(inputManager->isKeyPressed(GLFW_KEY_N)) statusInfo.pos += statusInfo.up    * velocity;
    if(inputManager->isKeyPressed(GLFW_KEY_M)) statusInfo.pos -= statusInfo.up    * velocity;

    if(inputManager->isKeyPressed(GLFW_MOUSE_BUTTON_LEFT)) {
        statusInfo.yaw     += (float)inputManager->getMouse().deltaX * sensitivity;
        statusInfo.pitch   += (float)inputManager->getMouse().deltaY * sensitivity;

        if (statusInfo.pitch > 89.0f) statusInfo.pitch = 89.0f;
        if (statusInfo.pitch < -89.0f) statusInfo.pitch = -89.0f;
    }

    updateObjectVectors();
    updateModelMatrix();
}

void Transform::rotateObject(glm::vec3 degrees)
{
    statusInfo.pitch   += degrees.x;
    statusInfo.yaw     += degrees.y;
    statusInfo.roll    += degrees.z;

    updateObjectVectors();
    updateModelMatrix();
}

void Transform::translateObject(glm::vec3 newPos)
{
    statusInfo.pos += newPos;
    updateModelMatrix();
}

void Transform::scaleObject(float addScale)
{
    statusInfo.scale += addScale;
    updateModelMatrix();
}

void Transform::updateObjectVectors()
{
    glm::vec3 f;
    f.x = cos(glm::radians(statusInfo.yaw)) * cos(glm::radians(statusInfo.pitch));
    f.y = sin(glm::radians(statusInfo.pitch));
    f.z = sin(glm::radians(statusInfo.yaw)) * cos(glm::radians(statusInfo.pitch));
    
    statusInfo.front = glm::normalize(f);
    statusInfo.right = glm::normalize(glm::cross(statusInfo.front, glm::vec3(0.0f, 1.0f, 0.0f)));
    statusInfo.up    = glm::normalize(glm::cross(statusInfo.right, statusInfo.front));
}

void Transform::updateModelMatrix()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, statusInfo.pos);
    model = glm::rotate(model, glm::radians( statusInfo.yaw),    glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(-statusInfo.pitch),  glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians( statusInfo.roll),   glm::vec3(0.0f, 0.0f, 1.0f));

    model = glm::scale(model, statusInfo.scale);
    
    modelMatrix = model;
}