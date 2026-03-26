#include "Texture.h"

Texture2D::Texture2D(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType)
{
    type = texType;
    // Sets target's form
    texTarget = GL_TEXTURE_2D;
    // Share slot information to unit variable that in Texture class
    unit = slot;

    int widthImg;
    int heightImg;
    int numColCh;

    // image load activate
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

    // Generates texture object
    glGenTextures(1, &ID);
    // Activate target texture which in slot
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(texTarget, ID);

    // Set mipmap options
    glTexParameteri(texTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(texTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // Set type of image mapping
    glTexParameteri(texTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Identify type of image file
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