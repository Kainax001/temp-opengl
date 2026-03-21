#ifndef COLORCONTROL_H
#define COLORCONTROL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "inputmanager.h"

class ColorControl {
    public:
    ColorControl(GLFWwindow* window, InputManager* inputManager);
    void changeColor();

    private:
    GLFWwindow* window;
    InputManager* inputManager;
};

#endif