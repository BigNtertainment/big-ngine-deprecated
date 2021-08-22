//#define GLFW_DLL

// REALLY IMPORTANT STUFF
// DO NOT REMOVE GLAD
#include "GLAD/glad.h"
#include <GLFW/glfw3.h>


#include <iostream>
// resizing the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// processing inputs
void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main()
{

//	setting up GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	APPLE stuff (get this out of here)
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	
	// setting up window
	GLFWwindow* window = glfwCreateWindow(800, 600, "I WILL LEARN OPENGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
//	making context for opengl
	glfwMakeContextCurrent(window);
//	window resize stuff
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
//	loading in GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
//	VIEWPORT!!
	glViewport(0, 0, 800, 600);
	
//	main game loop
//	this should be handled by sdl to this point
	while(!glfwWindowShouldClose(window))
	{
//		input process
		processInput(window);
		
//		RENDERING HERE

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


//		swapping buffers and getting inputs
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	
	glfwTerminate();
	return 0;
}
//TODO(TYMON): LEARN
// https://learnopengl.com/Getting-started/Hello-Window
