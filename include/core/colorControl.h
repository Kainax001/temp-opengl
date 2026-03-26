#ifndef COLORCONTROL_H
#define COLORCONTROL_H

// Deleted overlapped headerfile
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