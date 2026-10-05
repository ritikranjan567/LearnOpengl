// LearnOpengl.cpp : Defines the entry point for the application.
//

#include "LearnOpengl.h"
#include "Shader.h"
#include <stb_image/stb_image.h>
#include "Texture.h"
#include "io/Keyboard.h"
#include "io/Mouse.h"
#include "io/Joystick.h"

glm::mat4 transform = glm::mat4(1.0f);
Joystick mainj(0);

unsigned int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;
float x =0, y=0, z=3.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	SCREEN_HEIGHT = height;
	SCREEN_WIDTH = width;
}

void processInput(GLFWwindow* window) {
	if (Keyboard::keyWentDown(GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, true);
	}

	if (Keyboard::key(GLFW_KEY_W)) {
		// transform = glm::translate(transform, glm::vec3(0.0f, 0.01f, 0.0f));
		y -= 0.1f;
	}

	if (Keyboard::key(GLFW_KEY_S)) {
		// transform = glm::translate(transform, glm::vec3(0.0f, -0.01f, 0.0f));
		y += 0.1f;
	}

	if (Keyboard::key(GLFW_KEY_A)) {
		// transform = glm::translate(transform, glm::vec3(-0.01f, 0.0f, 0.0f));
		x += 0.1f;
	}

	if (Keyboard::key(GLFW_KEY_D)) {
		// transform = glm::translate(transform, glm::vec3(0.01f, 0.0f, 0.0f));
		x -= 0.1f;
	}

	if (Keyboard::key(GLFW_KEY_SPACE)) {
		z -= 0.1f;
	}

	if (Keyboard::key(GLFW_KEY_C)) {
		z += 0.1f;
	}


	mainj.update();

	float lx = mainj.axesState(GLFW_JOYSTICK_AXES_LEFT_STICK_X);
	float ly = mainj.axesState(GLFW_JOYSTICK_AXES_LEFT_STICK_Y);

	// CHECK for dead zone and apply logic
	if (std::abs(lx) > 0.5f) {
		transform = glm::translate(transform, glm::vec3(lx/100, 0.0f, 0.0f));
	}
	if (std::abs(ly) > 0.5f) {
		transform = glm::translate(transform, glm::vec3(0.0f, -ly/100, 0.0f));
	}

	// float rt = mainj.axesState(GLFW_JOYSTICK_AXES_RIGHT_TRIGGER) / 2 + 0.5f;

	// if (rt > 0.5f) {
	// 	transform = glm::scale(transform, glm::vec3(1 + rt/10, 1 + rt/10, 0.0f));
	// }

	// float lt = mainj.axesState(GLFW_JOYSTICK_AXES_LEFT_TRIGGER) / 2 + 0.5f;

	// if (lt > 0.5f) {
	// 	transform = glm::scale(transform, glm::vec3(1 - lt/10, 1 - lt/10, 0.0f));
	// }

}

int main()
{
	std::cout << "Hello CMake." << std::endl;
	int success;
	char infoLog[512];

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// set key callbacks
	glfwSetKeyCallback(window, Keyboard::keyCallback);

	glfwSetCursorPosCallback(window, Mouse::cursorPosCallback);

	glfwSetMouseButtonCallback(window, Mouse::mouseButtonCallback);

	glfwSetScrollCallback(window, Mouse::mouseWheelCallback);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// -------------

	Shader shader("assets/vertex_core.glsl", "assets/fragment_core.glsl");
	Shader shader2("assets/vertex_core.glsl", "assets/fragment_core2.glsl");
	
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
	
	// rectangle/square
	// float vertices[] = {
	// 	//triangle 1
	// 	-0.5f, 0.5f, 0.0f,  /*color*/ 1.0f, 1.0f, 0.5f, /*texture-map*/ 0.0f, 1.0f, // left-top
	// 	0.5f, 0.5f, 0.0f,   /*color*/ 0.5f, 1.0f, 0.75f, /*texture-map*/ 1.0f, 1.0f, // right-top
	// 	-0.5f, -0.5f, 0.0f, /*color*/ 0.6f, 1.0f, 0.2f, /*texture-map*/ 0.0f, 0.0f,  // left-bottom

	// 	// triagnle 2
	// 	// 0.5f, 0.5f, 0.0f, // right-top (commented-duplicate)
	// 	// -0.5f, -0.5f, 0.0f, // left-bottom (commented-duplicate)
	// 	0.5f, -0.5f, 0.0f,  /*color*/ 1.0f, 0.2f, 1.0f, /*texture-map*/ 1.0f, 0.0f // right-bottom
	// }; // see there is two share vertices which can be optimized

	//transformation for screen
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);


	// cube vertices
	float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
	glEnable(GL_DEPTH_TEST); // only shows outside of the cube
	
	// to eliminate this copy data, use concept of element buffer object array
	// From 4 unique vertices mention which triangle have which vertices
	unsigned int indices[] = {
		0, 1, 2, // triangle 1
		1, 2, 3 // triangle 2
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// now explain the data stream/array to the opengl
	// to do that set attribute pointer
	glVertexAttribPointer(0, // index starts from where
		3, // here 3d if 2D it size of vertex should be 2
		GL_FLOAT, // type of each coordinate
		GL_FALSE, // wheather to normalize
		sizeof(float) * 5, // size of each vertex
		nullptr // void/nullptr
	);
	// now tell opengGL shader input data is at location = 0
	glEnableVertexAttribArray(0);

	// lets define attribute for color in vertices
	// glVertexAttribPointer(
	// 	1, // as location = 1,
	// 	3, // still 3 as rgb
	// 	GL_FLOAT,
	// 	GL_FALSE,
	// 	sizeof(GL_FLOAT) * 5,
	// 	(void*)(3 * sizeof(GL_FLOAT))
	// );
	// glEnableVertexAttribArray(1);
	// texture coordinates attribute
	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(GL_FLOAT) * 5,
		(void*)(3 * sizeof(GL_FLOAT))
	);
	glEnableVertexAttribArray(2);
	// now in main loop can draw

	// unsigned int texture1, texture2;

	// glGenTextures(1, &texture1);
	// glBindTexture(GL_TEXTURE_2D, texture1);

	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// // now set image interpolation/filtering
	// glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// //load image
	// int width, height, nChannels;
	// stbi_set_flip_vertically_on_load(true);
	// unsigned char* data = stbi_load("assets/texture/obama10.jpg", &width, &height, &nChannels, 0);

	// if (data) {
	// 	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	// 	glGenerateMipmap(GL_TEXTURE_2D);
	// }
	// else {
	// 	std::cout << "Failed to load image texture" << std::endl;
	// }

	// stbi_image_free(data);

	Texture texture1, texture2;
	texture1.loadImage(GL_RGB, "assets/texture/obama10.jpg");
	texture2.loadImage(GL_RGBA, "assets/texture/americanflag1__1_.png");
	
	// glGenTextures(1, &texture2);
	// glBindTexture(GL_TEXTURE_2D, texture2);

	// data = stbi_load("assets/texture/americanflag1__1_.png",
	// 	&width, &height, &nChannels, 0
	// );

	// if (data) {
	// 	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	// 	glGenerateMipmap(GL_TEXTURE_2D);
	// }
	// else {
	// 	std::cout << "Unable to load american flag" << std::endl;
	// }
	// stbi_image_free(data);
	
	shader.activate();
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);



	// here using element buffer object
	// glGenBuffers(1, &elementBufferArrayObj);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferArrayObj);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// define transform matrix to pass it to shader
	glm::mat4 trans = glm::mat4(1.0f); // unity 4x4 matrix
	trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
	shader.activate();
	texture1.bindTexture();
	texture2.bindTexture();
	// glBindTexture(GL_TEXTURE_2D, texture1);
	// shader.setMat4("transform", trans);
	// shader2.activate();
	// shader2.setMat4("transform", trans);
	// to pass it
	// glUseProgram(shaderPrograms[0]);
	// glUniformMatrix4fv(glGetUniformLocation(shaderPrograms[0], "transform"), 1, GL_FALSE, glm::value_ptr(trans));
	// glUseProgram(shaderPrograms[1]);
	// glUniformMatrix4fv(glGetUniformLocation(shaderPrograms[1], "transform"), 1, GL_FALSE, glm::value_ptr(trans));


	mainj.update();
	if (mainj.isPresent()) {
		std::cout << "Controller connected. Name: " << mainj.getName() << std::endl;
	} else {
		std::cout << "No controller added" << std::endl;
	}


	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		if (Mouse::button(GLFW_MOUSE_BUTTON_LEFT)) {
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		}
		else {
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		}

		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		texture1.bindAndActivate(GL_TEXTURE0);
		texture2.activateTexFromUnit(GL_TEXTURE1);
		texture2.bindTexture();
		
		// glActiveTexture(GL_TEXTURE0);
		// glActiveTexture(GL_TEXTURE1);
		// glBindTexture(GL_TEXTURE_2D, texture2);

		// lets rotate the square
		// for (int i = 0; i < 2; i++) {
		// 	trans = glm::rotate(trans, glm::radians((float)(glfwGetTime() / 100.0f)), glm::vec3(0.0f, 0.0f, 1.0f));
		// 	glUseProgram(shaderPrograms[i]);
		// 	glUniformMatrix4fv(glGetUniformLocation(shaderPrograms[i], "transform"), 1, GL_FALSE, glm::value_ptr(trans));
		// }
		// transform = glm::rotate(trans, glm::radians((float)(glfwGetTime() / 10.0f)), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-0.3f), glm::vec3(0.5f));
		view = glm::translate(glm::mat4(1.0f), glm::vec3(-x, -y, -z));
		projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
		shader.activate();

		// shader.setMat4("transform", trans);
		shader.setMat4("model", model);
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		
		// draw shapes
		glBindVertexArray(vertexArrayObj); // optional if only single VAO
		// glUseProgram(shaderPrograms[0]);
		// glDrawArrays(GL_TRIANGLES, 
		// 	0, // first index
		// 	3 // number of vertices to draw
		// );

		// draw rectangle
		glDrawArrays(GL_TRIANGLES, 
			0, // first index
			36 // number of vertices to draw
		);
		//draw rectangle with shared vertices
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// shader2.activate();
		// shader2.setMat4("transform", trans);
		// glUseProgram(shaderPrograms[1]);
		// glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int)));



		// sends new frames to window
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &vertexArrayObj);
	glDeleteBuffers(1, &vertexArrayObj);
	glDeleteBuffers(1, &elementBufferArrayObj);

	glfwTerminate();
	return 0;
}
