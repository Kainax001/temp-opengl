#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "mytexture.h"

class Model
{
    public :
    Model() = default;
    Model(const char* file);
    ~Model();

    void loadModel(const std::string& path);
    void Draw(Shader& shader);
    void setCenter(Mesh targetMesh);
    glm::vec3 getCenter();

    private :
    std::vector<Mesh> meshes;
    std::string directory;
    glm::vec3 centerPos;
    
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture2D> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

#endif