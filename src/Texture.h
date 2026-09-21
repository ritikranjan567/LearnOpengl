#include <iostream>
#include <stb_image/stb_image.h>
#include <glad/glad.h>
#include <string>

class Texture {
public:
    GLuint id;

public: // methods
    explicit Texture();
    void loadImage(GLint format, const char* filePath);
    void bindTexture();
    void activateTexFromUnit(GLenum unit);
    void bindAndActivate(GLenum unit);
};