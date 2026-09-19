#version 330 core
out vec4 FragColor;
// tells to output 4D vector called FragColor, i.e value of FragColor sets the color of pixel

//lets read from color input and set
in vec4 ourColor; 

//fragment shadder is used to define color of the pixel
void main() {
    // FragColor = vec4(0.9f, 0.4f, 0.3f, 1.0f);
    FragColor = ourColor;
}

