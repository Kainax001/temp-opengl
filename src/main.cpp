#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include <stb_image.h>

#include "UBO.h"
#include "shader.h"
#include "inputmanager.h"
#include "colorControl.h"
#include "camera.h"
#include "setting.h"
#include "Mesh.h"
#include "Texture.h"

Vertex vertices[] =
{
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

GLuint indices[] = 
{ 
    0, 1, 2, 
    0, 2, 3 
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

int main() {
    Setting ourSetting;
    ourSetting.loadConfig();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(ourSetting.getWindowWidth(), ourSetting.getWindowHeight(), "OpenGL_Setup", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    Shader ourShader("assets/shaders/default.vert", "assets/shaders/default.frag");
    Shader lightShader("assets/shaders/light.vert", "assets/shaders/light.frag");
    InputManager ourInputmanager(window);
    ColorControl ourColorcontroler(window, &ourInputmanager);
    Camera ourCamera(glm::vec3(0.0f, 0.5f, 3.0f), &ourInputmanager);

    std::string parentDir = std::filesystem::current_path().parent_path().string();
    std::string texPath = "/temp-opengl/assets/textures/test.png";
    Texture2D testTex((parentDir + texPath).c_str(), "diffuse", 0);
    
    std::vector<Texture2D> floorTextures;
    floorTextures.push_back(testTex);

    std::vector<Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
    std::vector<GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
    
    std::vector<Vertex> lVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
    std::vector<GLuint> lInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));

    std::vector<Texture2D> emptyTex;

    Mesh floorMesh(verts, ind, floorTextures);
    Mesh lightMesh(lVerts, lInd, emptyTex);

    UBO matricesUBO(2 * sizeof(glm::mat4), 0);
    matricesUBO.LinkToShader(ourShader.getID(), "Matrices", 0);
    matricesUBO.LinkToShader(lightShader.getID(), "Matrices", 0);

    glViewport(0, 0, ourSetting.getWindowWidth(), ourSetting.getWindowHeight());
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    glm::vec3 lightPos = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) 
    {
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if(ourInputmanager.isKeyPressed(GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, true);
        }

        glfwPollEvents();
        ourColorcontroler.changeColor();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourCamera.update(deltaTime);

        glm::mat4 view = ourCamera.getViewMatrix();
        glm::mat4 projection = glm::perspective(ourSetting.getRadian(), ourSetting.getAspect(), ourSetting.getZNear(), ourSetting.getZFar());
        matricesUBO.UpdateData(0, sizeof(glm::mat4), glm::value_ptr(projection));
        matricesUBO.UpdateData(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));

        glm::mat4 model = glm::mat4(1.0f);
        ourShader.use();
        ourShader.setMat4("model", model);
        ourShader.setVec4("lightColor", lightColor);
        ourShader.setVec3("lightPos", lightPos);
        floorMesh.Draw(ourShader, ourCamera);

        glm::mat4 lightModel = glm::mat4(1.0f);
        lightModel = glm::translate(lightModel, lightPos);
        lightModel = glm::scale(lightModel, glm::vec3(1.0f));
        lightShader.use();
        lightShader.setMat4("model", lightModel);
        lightShader.setVec4("lightColor", lightColor);
        lightMesh.Draw(lightShader, ourCamera);
        
        glfwSwapBuffers(window);
        ourInputmanager.update();
    }

    glfwTerminate();
    return 0;
}