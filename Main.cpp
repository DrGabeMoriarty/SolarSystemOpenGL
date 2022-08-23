#include <iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main()
{
	//Initializing GLFW
	glfwInit();

	//Telling GLFW which OpenGL version we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Telling GLFW that we are using the core profile (without outdated functions)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Creating a new window of 720p resolution, named "test window" and without fullscreen
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Test Window", NULL, NULL);

	//safety check
	if (window == NULL)
	{
		std::cout << "Wait this is not supposed to happen!" << std::endl;
		glfwTerminate();
	}

	//Introduce the window to the current context, so that it can be displayed.
	glfwMakeContextCurrent(window);

	//Load GLAD so that it configures OpenGL
	gladLoadGL();

	//Specify the viewport of OpenGL in the window
	glViewport(0, 0, 800, 600);

	//Specify background color
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	//clean the back buffer and assign new color to it
	glClear(GL_COLOR_BUFFER_BIT);

	//swap the back buffer with the front buffer, so that it gets displayed on the screen in the next frame
	glfwSwapBuffers(window);

	//the main while loop, kinda like the Update() function in Unity
	while (!glfwWindowShouldClose(window))
	{
		//handles all GLFW events
		glfwPollEvents();
	}

	//delete window before closing the program
	glfwDestroyWindow(window);
	//terminate glfw before closing the program
	glfwTerminate();

	return 0;
}