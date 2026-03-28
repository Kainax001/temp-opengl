#include "model.h"
#include <iostream>

// --- 생성자 & 소멸자 ---
Model::Model(const char* file)
{
    loadModel(file);
}

Model::~Model()
{
    // vector<Mesh> meshes는 소멸 시 자동으로 메모리를 해제하므로 비워두어도 무방합니다.
    // 만약 동적 할당한 데이터가 있다면 여기서 해제합니다.
}

// --- 모델 로딩 ---
void Model::loadModel(const std::string& path)
{
    Assimp::Importer importer;
    // aiProcess_Triangulate: 다각형을 삼각형으로 쪼갬
    // aiProcess_FlipUVs: OpenGL에 맞게 텍스처 Y축 반전
    // aiProcess_GenSmoothNormals: 모델에 법선(Normal) 데이터가 없으면 부드럽게 자동 생성해줌
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    
    // 파일 경로에서 마지막 '/' 위치를 찾아 디렉토리 경로만 빼옵니다. (예: assets/models)
    directory = path.substr(0, path.find_last_of('/'));

    // 루트 노드부터 순회 시작
    processNode(scene->mRootNode, scene);
}

// --- 그리기 ---
void Model::Draw(Shader& shader) 
{
    // 모델을 구성하는 모든 메쉬들을 하나씩 그립니다.
    for(unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i].Draw(shader); 
    }
}

// --- 노드 순회 (재귀) ---
void Model::processNode(aiNode* node, const aiScene* scene)
{
    // 현재 노드의 메쉬들을 변환하여 벡터에 저장
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    
    // 자식 노드 순회
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

// --- 메쉬 변환 (Assimp -> 내 엔진) ---
Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture2D> textures;

    // 1. 정점(Vertex) 데이터 추출
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        
        vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        
        if (mesh->HasNormals()) {
            vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        } else {
            vertex.normal = glm::vec3(0.0f, 1.0f, 0.0f);
        }

        vertex.color = glm::vec3(1.0f, 1.0f, 1.0f);

        if(mesh->mTextureCoords[0]) {
            vertex.texUV = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        } else {
            vertex.texUV = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<Texture2D> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        
        // Specular 맵 (반사광) - 필요시 주석 해제
        // std::vector<Texture2D> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        // textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

std::vector<Texture2D> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<Texture2D> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

        std::string fullPath = directory + "/" + std::string(str.C_Str());

        Texture2D texture(fullPath.c_str(), typeName, 0);
        textures.push_back(texture);
    }
    return textures;
}