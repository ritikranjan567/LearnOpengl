// LearnOpengl.cpp : Defines the entry point for the application.
//

#include "LearnOpengl.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

std::string loadShaderSrc(const char* filename) {
	std::ifstream file;
	std::stringstream buf;

	std::string ret;

	file.open(filename);
	if (file.is_open()) {
		buf << file.rdbuf();
		ret = buf.str();
	}
	else {
		std::cout << "Unable to open shader src file: " << filename << std::endl;
	}

	file.close();
	return ret;
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

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

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

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Running shaders here
	// compile vertex shaders
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	std::string vertShaderSrc = loadShaderSrc("src/assets/vertex_core.glsl");
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
	std::string fragmentShaderSrc = loadShaderSrc("src/assets/fragment_core.glsl");
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
	fragmentShaderSrc = loadShaderSrc("src/assets/fragment_core2.glsl");
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
	
	// rectangle/square
	float vertices[] = {
		//triangle 1
		-0.5f, 0.5f, 0.0f, // left-top
		0.5f, 0.5f, 0.0f, // right-top
		-0.5f, -0.5f, 0.0f, // left-bottom

		// triagnle 2
		// 0.5f, 0.5f, 0.0f, // right-top (commented-duplicate)
		// -0.5f, -0.5f, 0.0f, // left-bottom (commented-duplicate)
		0.5f, -0.5f, 0.0f // right-bottom
	}; // see there is two share vertices which can be optimized
	
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
		sizeof(float) * 3, // size of each vertex
		(void*)0 // void/nullptr
	);
	// now tell opengGL shader input data is at location = 0
	glEnableVertexAttribArray(0); 
	// now in main loop can draw

	// here using element buffer object
	glGenBuffers(1, &elementBufferArrayObj);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferArrayObj);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		}
		else {
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		}

		
		glClear(GL_COLOR_BUFFER_BIT);
		
		// draw shapes
		glBindVertexArray(vertexArrayObj); // optional if only single VAO
		glUseProgram(shaderPrograms[0]);
		// glDrawArrays(GL_TRIANGLES, 
		// 	0, // first index
		// 	3 // number of vertices to draw
		// );

		// draw rectangle
		// glDrawArrays(GL_TRIANGLES, 
		// 	0, // first index
		// 	6 // number of vertices to draw
		// );
		//draw rectangle with shared vertices
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glUseProgram(shaderPrograms[1]);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int)));



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
