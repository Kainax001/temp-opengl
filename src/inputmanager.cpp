#include "inputmanager.h"

bool KeyboardState::isDown(int key) const 
{
    if (key >= 0 && key < 1024) return keys[key];
    return false;
}

InputManager::InputManager(GLFWwindow* window) : window(window) 
{
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

const KeyboardState& InputManager::getKeyboard() const 
{
    return kbd;
}

const MouseState& InputManager::getMouse() const 
{
    return mouse;
}

bool InputManager::isKeyPressed(int key) const 
{
    return kbd.isDown(key);
}

void InputManager::update() 
{
    mouse.deltaX = 0.0;
    mouse.deltaY = 0.0;
}

void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
    InputManager* manager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    if (manager) manager->handleKey(key, scancode, action, mods);
}

void InputManager::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    InputManager* manager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    if (manager) manager->handleMouse(xpos, ypos);
}

void InputManager::handleKey(int key, int scancode, int action, int mods) 
{
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) kbd.keys[key] = true;
        else if (action == GLFW_RELEASE) kbd.keys[key] = false;
    }
}

void InputManager::handleMouse(double xpos, double ypos)
{
    if (mouse.firstMouse) {
        mouse.lastX = xpos;
        mouse.lastY = ypos;
        mouse.firstMouse = false;
    }

    mouse.deltaX = xpos - mouse.lastX;
    mouse.deltaY = mouse.lastY - ypos;

    mouse.lastX = xpos;
    mouse.lastY = ypos;
}