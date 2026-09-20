#version 330 core
out vec4 FragColor;
// tells to output 4D vector called FragColor, i.e value of FragColor sets the color of pixel

//lets read from color input and set
// in vec4 color; 
in vec3 ourColor;
in vec2 TextCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

//fragment shadder is used to define color of the pixel
void main() {
    // FragColor = vec4(1.0f, 0.2f, 0.6f, 1.0f);
    // FragColor = color;
    // FragColor = vec4(ourColor, 1.0f);

    // FragColor = vec4(ourColor, 1.0f) * texture(texture2, TextCoord);

    FragColor = mix(texture(texture1, TextCoord), texture(texture2, TextCoord), 0.2);
}

