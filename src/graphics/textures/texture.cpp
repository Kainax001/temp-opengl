#include "texture.h"
#include <iostream>

const char* Texture::getType() const { return type; }

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
    // Sets texture uniform location to each shader
    GLuint texUni = glGetUniformLocation(shader.getID(), uniform);
    shader.use();
    glUniform1i(texUni, unit);
}

void Texture::Bind()
{
    // Active texture class's texture slot
    glActiveTexture(GL_TEXTURE0 + unit);
    // Bind activated texture
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