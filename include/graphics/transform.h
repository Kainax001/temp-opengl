#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include "inputmanager.h"

class Transform
{
    public :
    Transform(GLFWwindow* window, InputManager* inputManager);
    ~Transform();

    void update(float deltaTime);

    glm::mat4 getModelMatrix();
    void rotateObject();
    void translateObject();
    void scaleObject();

    private :
    void updateObjectVectors();
    void updateModelMatrix();

    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;

    glm::vec3 scale;

    float yaw;
    float pitch;
    float roll;

    glm::mat4 modelMatrix;
    float speed;
    float sensitivity;

    InputManager* inputManager;
    GLFWwindow* window;
};

#endif TRANSFORM_H