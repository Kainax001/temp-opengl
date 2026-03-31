#ifndef MESH_H
#define MESH_H

#include <string>
#include "VAO.h"
#include "EBO.h"
#include "camera.h"
#include "mytexture.h"

struct PosInfo
{
    glm::vec3 centerPos;
    glm::vec3 minPos;
    glm::vec3 maxPos;
};

class Mesh
{
    public :
    Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture2D>& textures);
    ~Mesh();

    void Draw(Shader& shader);
    void initializePosInfo();
    void setCenterPos(glm::vec3 newCenterPos);
    glm::vec3 getCenter();
    glm::vec3 getMinPos();
    glm::vec3 getMaxPos();
    
    private :
    VAO VAO;
    std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture2D> textures;
    PosInfo posInfo;
};

#endif