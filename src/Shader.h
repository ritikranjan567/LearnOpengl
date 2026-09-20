#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
    unsigned int id; // shader program ID

public: // public methods
    explicit Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
    void activate();

    // utility methods
    std::string loadShaderSrc(const char* filePath);
    GLuint compileShader(const char* filepath, GLenum type);

    // uniform function
    void setMat4(const std::string& name, glm::mat4 val);
    void setInt(const std::string& name, int val);
};