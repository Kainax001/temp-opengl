#include "mesh.h"

#include <algorithm>
#include <limits>

Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture2D>& textures)
{
    Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;
	posInfo.centerPos = glm::vec3(0.0f);
    posInfo.minPos = glm::vec3(std::numeric_limits<float>::max());
    posInfo.maxPos = glm::vec3(std::numeric_limits<float>::lowest());

    VBO VBO(vertices);
    EBO EBO(indices);

	VAO.Bind();
	EBO.Bind();

	// Links VBO attributes such as coordinates and colors, normal to VAO
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, color));
    VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texUV));
    VAO.LinkAttrib(VBO, 3, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    
	// Unbind all to prevent accidentally modifying them
	VAO.Unbind();
	EBO.Unbind();
	initializePosInfo();
}
Mesh::~Mesh() {}

void Mesh::Draw(Shader& shader)
{
    shader.use();
    VAO.Bind();

    unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	// Binds texture to each slot
    for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string num;
		std::string type = textures[i].getType();
		if (type == "diffuse") {
			num = std::to_string(numDiffuse++);
		} else if (type == "specular") {
			num = std::to_string(numSpecular++);
		}
		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].Bind();
	}
	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    VAO.Unbind();
}

void Mesh::initializePosInfo() {
	if (vertices.empty()) {
        posInfo.centerPos = glm::vec3(0.0f);
        return;
    }

    for (size_t i = 0; i < vertices.size(); i++)
    {
        glm::vec3 pos = vertices[i].position;

        posInfo.minPos.x = std::min(posInfo.minPos.x, pos.x);
        posInfo.minPos.y = std::min(posInfo.minPos.y, pos.y);
        posInfo.minPos.z = std::min(posInfo.minPos.z, pos.z);

        posInfo.maxPos.x = std::max(posInfo.maxPos.x, pos.x);
        posInfo.maxPos.y = std::max(posInfo.maxPos.y, pos.y);
        posInfo.maxPos.z = std::max(posInfo.maxPos.z, pos.z);
    }

    posInfo.centerPos = (posInfo.maxPos + posInfo.minPos) / 2.0f;
}
glm::vec3 Mesh::getCenter() { return posInfo.centerPos; }
glm::vec3 Mesh::getMinPos() { return posInfo.minPos; }
glm::vec3 Mesh::getMaxPos() { return posInfo.maxPos; }