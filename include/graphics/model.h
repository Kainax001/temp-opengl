#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "texture.h"

class Model
{
    public :
    Model() = default;
    Model(const char* file);
    ~Model();

    void loadModel(const std::string& path);
    void Draw(Shader& shader);

    private :
    std::vector<Mesh> meshes;
    std::string directory;
    
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture2D> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

#endif