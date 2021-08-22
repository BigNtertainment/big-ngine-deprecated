//#define GLFW_DLL

// REALLY IMPORTANT STUFF
// DO NOT REMOVE GLAD
#include "GLAD/glad.h"
#include <GLFW/glfw3.h>

// my stuff
#include "global/fileSystem/fileSystem.h"
#include "global/logger/logger.h"

// c stuff
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

// triangle vertices
float vertices[] = {
		-0.5f, -0.5f, 0.0f,	//right
		0.5f, -0.5f, 0.0f,	//left
		0.0f,  0.5f, 0.0f	//up
};

// buffer init
unsigned int VBO;

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
	GLFWwindow* window = glfwCreateWindow(800, 600, "I WILL LEARN OPENGL", nullptr, nullptr);
	if (window == nullptr)
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
	
	
//	VERTEX shaders!!!
	const char* vertexShaderSource = FileSystem::LoadFile("assets/shaders/vert.glsl").c_str();
	
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	
//	VERTEX shader compilation
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	
//	VERTEX compilation error detection
	int  vertSuccess;
	char vertInfoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertSuccess);
	
	if(!vertSuccess)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, vertInfoLog);
		Logger::Error(vertInfoLog);
	}
	
//	FRAGMENT SHADER woo wee
	const char* fragmentShaderSource = FileSystem::LoadFile("assets/shaders/frag.glsl").c_str();

//	same shit different day
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	int  fragSuccess;
	char fragInfoLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragSuccess);
	
	if(!fragSuccess)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, fragInfoLog);
		Logger::Error(fragInfoLog);
	}

//	SHADER PROGRAM
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	
//	TODO(tymon): understand this
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	
	glBindVertexArray(VAO);
//	creating and binding vertex buffer
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
//	sending vertex data to buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	
//	linking vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	
//	main game loop
	while(!glfwWindowShouldClose(window))
	{
		float timeValue = glfwGetTime();
//		input process
		processInput(window);
		
//		RENDERING HERE

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

//		uniform stuff
		int fragmentTime = glGetUniformLocation(shaderProgram, "u_time");
		int fragmentResolution = glGetUniformLocation(shaderProgram, "u_resolution");
		
		
		glUseProgram(shaderProgram);
		glUniform1f(fragmentTime, timeValue);
		glUniform2f(fragmentResolution, 800, 600);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

//		swapping buffers and getting inputs
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	
	glfwTerminate();
	return 0;
}
//TODO(TYMON): LEARN
// https://learnopengl.com/Getting-started/Hello-Window
