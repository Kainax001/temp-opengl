#include "Texture.h"

Texture2D::Texture2D(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType)
{
    type = texType;
    texTarget = GL_TEXTURE_2D;
    unit = slot;

    int widthImg;
    int heightImg;
    int numColCh;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

    glGenTextures(1, &ID);
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(texTarget, ID);

    glTexParameteri(texTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(texTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(texTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if (bytes) 
    {
        GLenum imgFormat = format;
        if (imgFormat == 0) {
            if (numColCh == 4) {
                imgFormat = GL_RGBA;
            } else {
                imgFormat = GL_RGB;
            }
        }

        glTexImage2D(texTarget, 0, imgFormat, widthImg, heightImg, 0, imgFormat, pixelType, bytes);
        glGenerateMipmap(texTarget);
    } 
    else 
    {
        std::cout << "Failed to load texture: " << image << "\n";
    }

    stbi_image_free(bytes);

    glBindTexture(texTarget, 0);
}