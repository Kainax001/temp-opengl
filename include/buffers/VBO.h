#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

class VBO 
{
    public:
        VBO(GLfloat* vertices, GLsizeiptr size);
        
        void Bind();
        void Unbind();
        void Delete();
    
    private:
        GLuint ID;
};

#endif