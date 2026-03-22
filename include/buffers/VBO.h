#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

class VBO 
{
    public:
        VBO(std::vector<Vertex>& vertices);
        
        void Bind();
        void Unbind();
        void Delete();
    
    private:
        GLuint ID;
};

#endif