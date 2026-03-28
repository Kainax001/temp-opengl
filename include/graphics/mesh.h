#ifndef MESH_H
#define MESH_H

#include <string>

#include "VAO.h"
#include "EBO.h"
#include "Camera.h"
#include "mytexture.h"

class Mesh
{
    public :
    Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture2D>& textures);
    ~Mesh();
    void Draw(Shader& shader);

    private :
    VAO VAO;
    std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture2D> textures;
};

#endif