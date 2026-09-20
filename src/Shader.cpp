#include "Shader.h"

Shader::Shader(const char * vertexShaderPath, const char * fragmentShaderPath)
{
    int success;
    char infoLog[512];

    GLuint vertexShader = compileShader(vertexShaderPath, GL_VERTEX_SHADER),
        fragmentShader = compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

    id = glCreateProgram();

    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cout << "[Shader Program link fail]\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

void Shader::activate()
{
    glUseProgram(id);
}

std::string Shader::loadShaderSrc(const char * filePath)
{
    std::fstream file;
    std::stringstream buf;

    std::string ret = "";
    file.open(filePath);

    if (file.is_open()) {
        buf << file.rdbuf();
        ret = buf.str();
    } else {
        std::cout << "Could not open/find file: " << filePath << std::endl;
    }
    file.close();
    return ret;
}

GLuint Shader::compileShader(const char * filepath, GLenum type)
{
    std::string shaderSource = loadShaderSrc(filepath);
    const GLchar* shaderContent = shaderSource.c_str();
    GLuint shader = glCreateShader(type);
    int success;
    char infoLog[512];
    glShaderSource(shader, 1, &shaderContent, NULL);
    glCompileShader(shader);
    
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "[Unable to compile shader]\n" << infoLog << std::endl;
    }

    return shader;
}

void Shader::setMat4(const std::string & name, glm::mat4 val)
{
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::setInt(const std::string& name, int val)
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), val);
}

