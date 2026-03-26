#include "mesh.h"

Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture2D>& textures)
{
    Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

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
}

void Mesh::Draw(Shader& shader, Camera& camera)
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
	// Take care of the camera Matrix
	shader.setVec3("camPos", camera.getPos());
	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    VAO.Unbind();
}