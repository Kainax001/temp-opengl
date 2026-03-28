#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <string>
#include <glad/glad.h>
#include <stb_image.h>

#include "shader.h"

class Texture
{
	public:
	// Assigns a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	// Binds a texture
	void Bind();
	// Unbinds a texture
	void Unbind();
	// Deletes a texture
	void Delete();

	std::string getType() const;

	protected :
	GLuint ID;
	std::string type;
	GLuint unit;
	GLenum texTarget;
};

class Texture2D : public Texture
{
	public :
	Texture2D(const char* image, std::string texType, GLuint slot, GLenum format = 0, GLenum pixelType = GL_UNSIGNED_BYTE);
};

#endif