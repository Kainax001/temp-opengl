#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>

#include "shader.h"
#include "transform.h"
#include "model.h"

class Entity
{
    public :
    std::string name;

    Entity(std::string entityName, Mesh* targetMesh,    InputManager* inputManager);
    Entity(std::string entityName, Model* targetModel,  InputManager* inputManager);
    ~Entity();

    Transform& getTransform();
    void update(float deltaTime);
    void centerUpdate(glm::vec3 centerPos);
    void Draw(Shader& shader);

    private :
    Transform transform;
    Mesh* mesh;
    Model* model;
};

#endif