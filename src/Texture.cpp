#include "Texture.h"

Texture::Texture()
{
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void Texture::loadImage(GLint format, const char* filePath)
{
    int width, height, nChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(filePath, &width, &height, &nChannels, 0);
    
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "[unable to load texture from image]: " << filePath << std::endl;
    }

    stbi_image_free(data);
}

void Texture::bindTexture()
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::activateTexFromUnit(GLenum unit)
{
    glActiveTexture(unit);
}

void Texture::bindAndActivate(GLenum unit)
{
    bindTexture();
    activateTexFromUnit(unit);
}
