#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>
#include <vector>

class EBO
{
    public:
    EBO(GLuint* indices, GLsizeiptr size);
    EBO(std::vector<GLuint>& indices);
    
    void Bind();
    void Unbind();
    void Delete();

    private:
    GLuint ID;
};

#endif