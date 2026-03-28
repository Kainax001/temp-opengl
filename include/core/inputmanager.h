#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

struct KeyboardState {
    bool keys[1024] = { false };
    bool isDown(int key) const;
};

struct MouseState {
    double lastX = 0.0;
    double lastY = 0.0;
    double deltaX = 0.0;
    double deltaY = 0.0;
    bool firstMouse = true;
    bool buttons[8] = { false };
    bool isDown(int button) const;
};

class InputManager 
{
    public:
        InputManager(GLFWwindow* window);
        const KeyboardState& getKeyboard() const;
        const MouseState& getMouse() const;
        bool isKeyPressed(int key) const;
        bool isMouseButtonPressed(int button) const;
        void update();

    private:
        GLFWwindow* window;
        KeyboardState kbd;
        MouseState mouse;

        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        void handleKey(int key, int scancode, int action, int mods);
        void handleMouseMove(double xpos, double ypos);
        void handleMouseButton(int button, int action, int mods);
};

#endif