#include <iostream>
#include <cmath>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
 
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main() {
	//Initializing GLFW
	glfwInit();

	//Telling GLFW which OpenGL version we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Telling GLFW that we are using the core profile (without outdated functions)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
	};

	//Creating a new window of 720p resolution, named "test window" and without fullscreen
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Test Window", NULL, NULL);

	//safety check
	if (window == NULL) {
		std::cerr << "Wait this is not supposed to happen!" << std::endl;
		glfwTerminate();
	}

	//Introduce the window to the current context, so that it can be displayed.
	glfwMakeContextCurrent(window);

	//Load GLAD so that it configures OpenGL
	gladLoadGL();

	//Specify the viewport of OpenGL in the window
	glViewport(0, 0, 1280, 720);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// Create reference containers for the Vertex Array Object and the Vertex Buffer Object
	GLuint VAO, VBO;

	// Generate the VAO and VBO with 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);

	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	//Specify background color
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	//clean the back buffer and assign new color to it
	glClear(GL_COLOR_BUFFER_BIT);

	//swap the back buffer with the front buffer, so that it gets displayed on the screen in the next frame
	glfwSwapBuffers(window);

	//the main while loop, kinda like the Update() function in Unity
	while (!glfwWindowShouldClose(window)) {
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		glUseProgram(shaderProgram);
		// Bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO);
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		
		//handles all GLFW events
		glfwPollEvents();
	}

	//delete window before closing the program
	glfwDestroyWindow(window);
	//terminate glfw before closing the program
	glfwTerminate();

	return 0;
}