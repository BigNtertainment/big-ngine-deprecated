#include "renderer.h"

#include <utility>


void BigNgine::RendererBehaviour::Start()
{
	float vertices[] = {
			parent->size.x,  0.0f, depth,  // top right
			parent->size.x, parent->size.y, depth,  // bottom right
			0.0f, parent->size.y, depth,  // bottom left
			0.0f, 0.0f, depth   // top left
	};
	unsigned int indices_square[] = {  // note that we start from 0!
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
	};
	
	
	//	shaders
	const char* vertex_shader_source = vertShader.c_str();
	const char* fragment_shader_source = fragShader.c_str();
	
	
	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader_source, nullptr);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	
	
	// fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader_source, nullptr);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	// check for linking errors
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	
	
//	binding all the shit arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_square), indices_square, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);
}

void BigNgine::RendererBehaviour::Update(int deltaTime)
{
//	TODO(tymon): add dynamic depth to vertex shader
	int u_resolution = glGetUniformLocation(program, "u_resolution");
	int u_position = glGetUniformLocation(program, "u_position");
	int u_size = glGetUniformLocation(program, "u_size");
	glUseProgram(program);
	glUniform2f(u_resolution, Game::width, Game::height);
	glUniform2f(u_position, parent->position.x, parent->position.y);
	glUniform2f(u_size, parent->size.x, parent->size.y);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
	
}

void BigNgine::RendererBehaviour::Destroy()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(program);
}

void BigNgine::RendererBehaviour::SetDefaultTexture(std::string path)
{
	BigNgine::RendererBehaviour::file = std::move(path);
}

void BigNgine::RendererBehaviour::SetVertShader(std::string vertexShader)
{
	BigNgine::RendererBehaviour::vertShader = std::move(vertexShader);
}

void BigNgine::RendererBehaviour::SetFragShader(std::string fragmentShader)
{
	BigNgine::RendererBehaviour::fragShader = std::move(fragmentShader);
}

void BigNgine::RendererBehaviour::SetDefaultDepth(float _depth)
{
	BigNgine::RendererBehaviour::depth = _depth;
}
