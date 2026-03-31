#include "entity.h"

// Only Mesh entity
Entity::Entity(std::string entityName, Mesh* targetMesh, InputManager* inputManager)
: name(entityName), transform(inputManager), mesh(targetMesh), model(nullptr)
{
    // Initialize
    if (mesh != nullptr) {
        transform.updateCenterPos(mesh->getCenter());
    }
}
// Model entity
Entity::Entity(std::string entityName, Model* targetModel, InputManager* inputManager)
: name(entityName), transform(inputManager), model(targetModel), mesh(nullptr)
{
    // Initialize
    if (model != nullptr) {
        transform.updateCenterPos(model->getCenter());
    }
}
Entity::~Entity() {}

Transform& Entity::getTransform() { return transform; }

void Entity::update(float deltaTime)
{
    transform.update(deltaTime);
}

void Entity::centerUpdate(glm::vec3 newCenterPos)
{
    transform.updateCenterPos(newCenterPos);
}

void Entity::Draw(Shader& shader)
{
    shader.setMat4("model", transform.getModelMatrix());

    if (mesh != nullptr) {
        mesh->Draw(shader);
    }
    else if (model != nullptr) {
        model->Draw(shader);
    }
}