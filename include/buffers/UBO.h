#ifndef UBO_H
#define UBO_H

#include <glad/glad.h>

class UBO 
{
    public :
    UBO(GLsizeiptr size, GLuint bindingPoint);
    ~UBO();
    
    void Bind();
    void Unbind();
    void Delete();

    void UpdateData(GLintptr offset, GLsizeiptr size, const void* data);
    void LinkToShader(GLuint shaderID, const char* blockName, GLuint bindingPoint);
    
    private :
    GLuint ID;
};

#endif