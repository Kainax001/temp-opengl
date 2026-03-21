#include "texture.h"
#include <iostream>

const char* Texture::getType() const { return type; }

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
    GLuint texUni = glGetUniformLocation(shader.getID(), uniform);
    shader.use();
    glUniform1i(texUni, unit);
}

void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(texTarget, ID);
}

void Texture::Unbind()
{
    glBindTexture(texTarget, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}