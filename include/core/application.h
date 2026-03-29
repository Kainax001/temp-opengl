#ifndef APPLICATION_H
#define APPLICATION_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "setting.h"
#include "inputmanager.h"
#include "colorControl.h"
#include "camera.h"
#include "shader.h"
#include "mesh.h"
#include "entity.h"
#include "UBO.h"
#include "model.h"

class Application
{
    public :
    Application();
    ~Application();

    bool init();
    void run();

    private :
    void setupScene();
    void renderloop();
    void cleanup();

    GLFWwindow* window;
    Setting setting;

    InputManager* inputManager;
    ColorControl* colorController;
    Camera* camera;

    Shader* defaultShader;
    Shader* lightShader;
    UBO* matricesUBO;
    Mesh* floorMesh;
    Mesh* lightMesh;
    Entity* mainCube;
    Entity* lightCube;
    Model* testModel;
};

#endif