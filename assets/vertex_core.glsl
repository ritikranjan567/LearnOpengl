#version 330 core //specifies the version of opengl
layout (location = 0) in vec3 aPos;
// Above says for layout/data go to the 0th index get attribute 3D vect name it aPos.
layout (location = 1) in vec3 aColor;
// Receive texture in layout 2
layout (location = 2) in vec2 aTextCoord;

// Now lets set and output a color that will be picked by framentshader
// out vec4 color;
out vec3 ourColor;

// pass to fragment shader
out vec2 TextCoord;

//set transform matrix global
uniform mat4 transform; // set in code [efficient when constant value for multiple loops]

// below program runs every frame

void main() {
    // gl_Position global var must be initialize
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
    TextCoord = aTextCoord;

    // if (aPos.x < 0.0f) {
    //     color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    // } else if (aPos.x == 0.0f) {
    //     color = vec4(0.0f, 1.0f, 0.0f, 1.0f);
    // } else {
    //     color = vec4(vec2(0.0f), vec2(1.0f));
    // }
}
// what program did, get value from data give, set the vertex position using global var gl_Position
// so on 2D screen the vertex is display at gl_Position