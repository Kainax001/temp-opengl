#include "UBO.h"

#include <iostream>

UBO::UBO(GLsizeiptr size, GLuint bindingPoint)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_UNIFORM_BUFFER, ID);
    glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, ID);
}

UBO::~UBO()
{
    Delete();
}

void UBO::Bind()
{
    glBindBuffer(GL_UNIFORM_BUFFER, ID);
}

void UBO::Unbind()
{
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UBO::Delete()
{
    if(ID != 0) {
        glDeleteBuffers(1, &ID);
        ID = 0;
    }
}

void UBO::UpdateData(GLintptr offset, GLsizeiptr size, const void* data)
{
    glBindBuffer(GL_UNIFORM_BUFFER, ID);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UBO::LinkToShader(GLuint shaderID, const char* blockName, GLuint bindingPoint)
{
    GLuint blockIndex = glGetUniformBlockIndex(shaderID, blockName); 
    
    if (blockIndex != GL_INVALID_INDEX) 
    {
        glUniformBlockBinding(shaderID, blockIndex, bindingPoint);
    } 
    else 
    {
        std::cout << "WARNING::UBO: Uniform block '" << blockName << "' not found in shader!" << std::endl;
    }
}