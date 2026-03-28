#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>

#include <shader.h>
#include "transform.h"
#include "mesh.h"

class Entity
{
    public :
    std::string name;

    Entity(std::string entityName, Mesh* targetMesh, InputManager* inputManager);
    ~Entity();

    Transform& getTransform();
    void update(float deltaTime);
    void Draw(Shader& shader);
    

    private :
    Transform transform;
    Mesh* mesh;
};

#endif