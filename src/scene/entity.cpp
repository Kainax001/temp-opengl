#include "entity.h"

Entity::Entity(std::string entityName, Mesh* targetMesh, InputManager* inputManager)
: name(entityName), transform(inputManager), mesh(targetMesh)
{
    // Initialize
}
Entity::~Entity(){}

Transform& Entity::getTransform() { return transform; }

void Entity::update(float deltaTime)
{
    transform.update(deltaTime);
}

void Entity::Draw(Shader& shader)
{
    if (mesh == nullptr) return;

    shader.setMat4("model", transform.getModelMatrix());

    mesh->Draw(shader);
}