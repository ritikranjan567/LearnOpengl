#version 330 core
out vec4 FragColor;
// tells to output 4D vector called FragColor, i.e value of FragColor sets the color of pixel

//lets read from color input and set
// in vec4 color; 
in vec3 ourColor;

//fragment shadder is used to define color of the pixel
void main() {
    // FragColor = vec4(1.0f, 0.2f, 0.6f, 1.0f);
    // FragColor = color;
    FragColor = vec4(ourColor, 1.0f);
}

