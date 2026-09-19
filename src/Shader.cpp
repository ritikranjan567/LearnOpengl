#include <LOpengl/Shader.h>

Shader::Shader(const char * vertexShaderPath, const char * fragmentShaderPath)
{
    int success;
    char infoLog[512];

    // GLuint vertexShader = compileShader(vertexShaderPath, GL_VERTEX_SHADER),
    //     fragmentShader = compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

    id = glCreateProgram();

    // glAttachShader(id, vertexShader);
    // glAttachShader(id, fragmentShader);
    glLinkProgram(id);
}