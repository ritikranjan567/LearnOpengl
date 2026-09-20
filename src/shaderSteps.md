cpp```
// Running shaders here
// compile vertex shaders
unsigned int vertexShader;
vertexShader = glCreateShader(GL_VERTEX_SHADER);

std::string vertShaderSrc = loadShaderSrc("assets/vertex_core.glsl");
const GLchar* vertShader = vertShaderSrc.c_str();
glShaderSource(vertexShader, 1, &vertShader, NULL);
glCompileShader(vertexShader);

// catch error
glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "Vertex compilation error: \n" << infoLog << std::endl;
}

// compile fragment shader
unsigned int fragmentShaders[2];
fragmentShaders[0] = glCreateShader(GL_FRAGMENT_SHADER);
std::string fragmentShaderSrc = loadShaderSrc("assets/fragment_core.glsl");
const GLchar* fragShader = fragmentShaderSrc.c_str();
glShaderSource(fragmentShaders[0], 1, &fragShader, NULL);
glCompileShader(fragmentShaders[0]);

// catch error
glGetShaderiv(fragmentShaders[0], GL_COMPILE_STATUS, &success);
if (!success) {
    glGetShaderInfoLog(fragmentShaders[0], 512, NULL, infoLog);
    std::cout << "Frament compilation error: \n" << infoLog << std::endl;
}

fragmentShaders[1] = glCreateShader(GL_FRAGMENT_SHADER);
fragmentShaderSrc = loadShaderSrc("assets/fragment_core2.glsl");
fragShader = fragmentShaderSrc.c_str();
glShaderSource(fragmentShaders[1], 1, &fragShader, NULL);
glCompileShader(fragmentShaders[1]);

// catch error
glGetShaderiv(fragmentShaders[1], GL_COMPILE_STATUS, &success);
if (!success) {
    glGetShaderInfoLog(fragmentShaders[1], 512, NULL, infoLog);
    std::cout << "Frament compilation error: \n" << infoLog << std::endl;
}

// opengl need shader program that links/pairs vertex and fragment shaders
unsigned int shaderPrograms[2];
shaderPrograms[0] = glCreateProgram();
glAttachShader(shaderPrograms[0], vertexShader);
glAttachShader(shaderPrograms[0], fragmentShaders[0]);
glLinkProgram(shaderPrograms[0]);
// catch errors
glGetProgramiv(shaderPrograms[0], GL_LINK_STATUS, &success);
if (!success) {
    glGetProgramInfoLog(shaderPrograms[0], 512, NULL, infoLog);
    std::cout << "Linking error:\n" << infoLog << std::endl;
}
// now clean-up as vertex and fragment are linked they are not need anymore
glDeleteShader(vertexShader);
glDeleteShader(fragmentShaders[0]);

shaderPrograms[1] = glCreateProgram();
glAttachShader(shaderPrograms[1], vertexShader);
glAttachShader(shaderPrograms[1], fragmentShaders[1]);
glLinkProgram(shaderPrograms[1]);
// catch errors
glGetProgramiv(shaderPrograms[1], GL_LINK_STATUS, &success);
if (!success) {
    glGetProgramInfoLog(shaderPrograms[1], 512, NULL, infoLog);
    std::cout << "Linking error:\n" << infoLog << std::endl;
}
// now clean-up as vertex and fragment are linked they are not need anymore
glDeleteShader(vertexShader);
glDeleteShader(fragmentShaders[0]);
glDeleteShader(fragmentShaders[1]);
// end shader compilation and program

//Now passing data to shader program
unsigned int vertexArrayObj, vertexBufferObj, elementBufferArrayObj;
glGenVertexArrays(1, &vertexArrayObj);
glGenBuffers(1, &vertexBufferObj);
// now bind VAO, telling active object
glBindVertexArray(vertexArrayObj);
// now bind VBO, marking as active object
glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObj);
// now data triangle
// float vertices[] = {
// 	-0.5f, -0.5f, 0.0f,
// 	0.0f, 0.5f, 0.0f,
// 	0.5f, -0.5f, 0.0f
// }; // normalized -1 to 1
```