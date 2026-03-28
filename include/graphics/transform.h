#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

#include "inputmanager.h"

struct TransformData
{
    glm::vec3 pos   = glm::vec3(0.0f);
    glm::vec3 front = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 up    = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec3 scale = glm::vec3(1.0f);

    float yaw   = 0.0f;
    float pitch = 0.0f;
    float roll  = 0.0f;
};

class Transform
{
    public :
    Transform(InputManager* inputManager);
    ~Transform();

    void update(float deltaTime);

    glm::mat4 getModelMatrix();
    glm::vec3 getPos();
    void rotateObject(glm::vec3 degrees);
    void translateObject(glm::vec3 newPos);
    void scaleObject(float addScale);

    private :
    void updateObjectVectors();
    void updateModelMatrix();

    TransformData statusInfo;

    glm::mat4 modelMatrix;
    float speed;
    float sensitivity;

    InputManager* inputManager;
};

#endif