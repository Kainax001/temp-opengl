#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "inputmanager.h"

class Camera {
    public:
        Camera(glm::vec3 position);

        glm::mat4 getViewMatrix() const;

        void update(const KeyboardState& kbd, const MouseState& mouse, float deltaTime);
        glm::vec3 getPos();

    private:
        void updateCameraVectors();

        glm::vec3 pos;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;

        float yaw;
        float pitch;
        float speed;
        float sensitivity;
};

#endif