#include "application.h"

#include <iostream>
#include <filesystem>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

Vertex vertices[] =
{
    Vertex{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
    Vertex{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
    Vertex{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},

    Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
    Vertex{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
    Vertex{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},

    Vertex{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
    Vertex{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
    Vertex{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},

    Vertex{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
    Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
    Vertex{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},

    Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
    Vertex{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
    Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},

    Vertex{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
    Vertex{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
    Vertex{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)}
};

GLuint indices[] = 
{ 
    0,  1,  2,   0,  2,  3,
    4,  5,  6,   4,  6,  7,
    8,  9, 10,   8, 10, 11,
   12, 13, 14,  12, 14, 15,
   16, 17, 18,  16, 18, 19,
   20, 21, 22,  20, 22, 23
};

Vertex lightVertices[] =
{
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)}, Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)}, Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)}, Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)}, Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
	0, 1, 2, 0, 2, 3, 0, 4, 7, 0, 7, 3, 3, 7, 6, 3, 6, 2, 
    2, 6, 5, 2, 5, 1, 1, 5, 4, 1, 4, 0, 4, 5, 6, 4, 6, 7 
};



Application::Application() : 
    window(nullptr), inputManager(nullptr), colorController(nullptr), camera(nullptr),
    defaultShader(nullptr), lightShader(nullptr), matricesUBO(nullptr),
    floorMesh(nullptr), lightMesh(nullptr), mainCube(nullptr), lightCube(nullptr), testModel(nullptr)
{
    // Initialize
}

Application::~Application() 
{
    delete mainCube; delete lightCube;
    delete floorMesh; delete lightMesh;
    delete defaultShader; delete lightShader;
    delete matricesUBO;
    delete camera; delete colorController; delete inputManager; delete testModel;
    
    glfwTerminate();
}

bool Application::init()
{
    setting.loadConfig();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(setting.getWindowWidth(), setting.getWindowHeight(), "temp-opengl", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    inputManager = new InputManager(window);
    colorController = new ColorControl(window, inputManager);
    camera = new Camera(glm::vec3(0.0f, 0.5f, 3.0f), inputManager);

    return true;
}

void Application::run()
{
    setupScene();
    renderloop();
}

void Application::setupScene()
{
    defaultShader = new Shader("assets/shaders/default.vert", "assets/shaders/test.frag");
    lightShader = new Shader("assets/shaders/light.vert", "assets/shaders/light.frag");

    std::string parentDir = std::filesystem::current_path().parent_path().string();
    Texture2D testTex((parentDir + "/temp-opengl/assets/textures/blackTile.png").c_str(), "diffuse", 0);
    std::vector<Texture2D> floorTextures = { testTex };
    std::vector<Texture2D> emptyTex;

    std::vector<Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
    std::vector<GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
    std::vector<Vertex> lVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
    std::vector<GLuint> lInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));

    floorMesh = new Mesh(verts, ind, floorTextures);
    lightMesh = new Mesh(lVerts, lInd, emptyTex);

    mainCube = new Entity("MainCube", floorMesh, inputManager);
    lightCube = new Entity("LightCube", lightMesh, inputManager);

    lightCube->getTransform().translateObject(glm::vec3(1.0f, 1.0f, 1.0f));

    matricesUBO = new UBO(2 * sizeof(glm::mat4), 0);
    matricesUBO->LinkToShader(defaultShader->getID(), "Matrices", 0);
    matricesUBO->LinkToShader(lightShader->getID(), "Matrices", 0);

    std::string modelPath = parentDir + "/temp-opengl/assets/models/bunny.obj";
    testModel = new Model(modelPath.c_str());

    glViewport(0, 0, setting.getWindowWidth(), setting.getWindowHeight());
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void Application::renderloop()
{
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) 
    {
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if(inputManager->isKeyPressed(GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, true);
        }

        glfwPollEvents();
        colorController->changeColor();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera->update(deltaTime);
        mainCube->update(deltaTime); 

        glm::mat4 view = camera->getViewMatrix();
        glm::mat4 projection = glm::perspective(setting.getRadian(), setting.getAspect(), setting.getZNear(), setting.getZFar());
        matricesUBO->UpdateData(0, sizeof(glm::mat4), glm::value_ptr(projection));
        matricesUBO->UpdateData(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));

        defaultShader->use();
        defaultShader->setVec4("lightColor", lightColor);
        defaultShader->setVec3("lightPos", lightCube->getTransform().getPos());
        defaultShader->setVec3("camPos", camera->getPos());
        //mainCube->Draw(*defaultShader);

        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(10.0f));
        modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        defaultShader->setMat4("model", modelMatrix);
        testModel->Draw(*defaultShader);

        lightShader->use();
        lightShader->setVec4("lightColor", lightColor);
        lightCube->Draw(*lightShader);
        
        glfwSwapBuffers(window);
        inputManager->update();
    }
}

void Application::cleanup()
{
    
}