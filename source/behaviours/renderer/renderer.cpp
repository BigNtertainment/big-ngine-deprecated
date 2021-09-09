#include "renderer.h"


void BigNgine::RendererBehaviour::Start()
{
//	setting up all the relations between points in one entity-square
	float vertices[] = {
//			if position			colours				texture coords
//													Y axis is flipped
			1.0f, 0.0f, 0.0f,	1.0f, 1.0f, 1.0f,	1.0f, 0.0f,	// top right
			1.0f, 1.0f, 0.0f,	1.0f, 1.0f, 1.0f,	1.0f, 1.0f,	// bottom right
			0.0f, 1.0f, 0.0f,	1.0f, 1.0f, 1.0f,	0.0f, 1.0f,	// bottom left
			0.0f, 0.0f, 0.0f,	1.0f, 1.0f, 1.0f,	0.0f, 0.0f	// top left
	};
	
//	setting up how the points form triangles
	unsigned int indices_square[] = {
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
	};
	
	
//	loading shaders into char*
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
	
	
	
//	binding all the arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_square), indices_square, GL_STATIC_DRAW);
	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)nullptr);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);
	
//	TEXTURES
//==============================================================

//	binding textures
	glBindTexture(GL_TEXTURE_2D ,texture);

//	texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
//	texture filtering
//	NOTE: decide which to use
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
//	texture loading
	int textureWidth, textureHeight, textureChannels;
	unsigned char *textureData = stbi_load(file, &textureWidth, &textureHeight, &textureChannels, 0);
	
//	checking for errors and generating GL texture
	if (textureData)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
	else
		Logger::Error(std::string("could not load texture at: ") + file);
	
	stbi_image_free(textureData);
}

void BigNgine::RendererBehaviour::Update(int deltaTime)
{

//	TODO(tymon): https://learnopengl.com/Getting-started/Textures textures units

//	getting all uniform IDs
	int u_resolution = glGetUniformLocation(program, "u_resolution");
	int u_position = glGetUniformLocation(program, "u_position");
	int u_size = glGetUniformLocation(program, "u_size");
	int u_depth = glGetUniformLocation(program, "u_depth");
	
	glUseProgram(program);
	
//	setting all uniforms
	glUniform2f(u_resolution, Game::width, Game::height);
	glUniform2f(u_position, parent->position.x, parent->position.y);
	glUniform2f(u_size, parent->size.x, parent->size.y);
	glUniform1f(u_depth, parent->depth);
	
//	all the opengl binding and actually rendering the points
	
	glBindTexture(GL_TEXTURE_2D, texture);
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

void BigNgine::RendererBehaviour::SetDefaultTexture(const std::string& path)
{
	file = path.c_str();
}

void BigNgine::RendererBehaviour::SetVertShader(std::string vertexShader)
{
	vertShader = std::move(vertexShader);
}

void BigNgine::RendererBehaviour::SetFragShader(std::string fragmentShader)
{
	fragShader = std::move(fragmentShader);
}
