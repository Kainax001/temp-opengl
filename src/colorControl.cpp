#include "colorControl.h"

ColorControl::ColorControl(GLFWwindow* window, InputManager* inputManager) 
    : window(window), inputManager(inputManager) 
{
}

void ColorControl::changeColor() 
{
    float currentColor[4];
    glGetFloatv(GL_COLOR_CLEAR_VALUE, currentColor);

    const KeyboardState& kbd = inputManager->getKeyboard();
    bool changed = false;
    const float step = 0.01f;

    if (kbd.isDown(GLFW_KEY_F1)) { currentColor[0] += step; changed = true; } 
    if (kbd.isDown(GLFW_KEY_F2)) { currentColor[0] -= step; changed = true; } 
    if (kbd.isDown(GLFW_KEY_F3)) { currentColor[1] += step; changed = true; } 
    if (kbd.isDown(GLFW_KEY_F4)) { currentColor[1] -= step; changed = true; } 
    if (kbd.isDown(GLFW_KEY_F5)) { currentColor[2] += step; changed = true; } 
    if (kbd.isDown(GLFW_KEY_F6)) { currentColor[2] -= step; changed = true; }

    if (changed) {
        for (int i = 0; i < 3; ++i) {
            if (currentColor[i] > 1.0f) currentColor[i] = 1.0f;
            if (currentColor[i] < 0.0f) currentColor[i] = 0.0f;
        }
        glClearColor(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
    }
}