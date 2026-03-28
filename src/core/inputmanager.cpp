#include "inputmanager.h"

InputManager::InputManager(GLFWwindow* window) : window(window) 
{
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouseMoveCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

const KeyboardState& InputManager::getKeyboard() const { return kbd; }
bool KeyboardState::isDown(int key) const {
    if (key >= 0 && key < 1024) return keys[key];
    return false;
}
bool MouseState::isDown(int button) const {
    if (button >= 0 && button < 8) return buttons[button];
    return false;
}
const MouseState& InputManager::getMouse() const { return mouse; }
bool InputManager::isKeyPressed(int key) const { return kbd.isDown(key); }
bool InputManager::isMouseButtonPressed(int button) const { return mouse.isDown(button); }

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

void InputManager::mouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
    InputManager* manager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    if (manager) manager->handleMouseMove(xpos, ypos);
}

void InputManager::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    InputManager* manager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    if (manager) manager->handleMouseButton(button, action, mods);
}

void InputManager::handleKey(int key, int scancode, int action, int mods) 
{
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) kbd.keys[key] = true;
        else if (action == GLFW_RELEASE) kbd.keys[key] = false;
    }
}

void InputManager::handleMouseMove(double xpos, double ypos)
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

void InputManager::handleMouseButton(int button, int action, int mods)
{
    if (button >= 0 && button < 8) {
        if (action == GLFW_PRESS) mouse.buttons[button] = true;
        else if (action == GLFW_RELEASE) mouse.buttons[button] = false;
    }
    
}