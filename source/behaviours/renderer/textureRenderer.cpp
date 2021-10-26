#include "renderer.h"


void BigNgine::TextureRendererBehaviour::Start()
{
	//	setting up all the relations between points in one entity-square
	float vertices[] = {
//			positions			texture coords
			1.0f, 0.0f, 0.0f,	1.0f, 0.0f,	// top right
			1.0f, 1.0f, 0.0f,	1.0f, 1.0f,	// bottom right
			0.0f, 1.0f, 0.0f,	0.0f, 1.0f,	// bottom left
			0.0f, 0.0f, 0.0f,	0.0f, 0.0f 	// top left
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
	
//	position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)nullptr);
	glEnableVertexAttribArray(0);
//	texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);
	
	
	
//	textures

//	generating texture buffers
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
//	setting wrapping method
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
//	setting rasterisation method
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load image, create texture and generate mipmaps
	int width, height;
	unsigned char *data = stbi_load(file.c_str(), &width, &height, nullptr, 4);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		Logger::Error("Could not load texture at: " + std::string(file));
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	
}

void BigNgine::TextureRendererBehaviour::Update(int deltaTime)
{
	//	getting all uniform IDs
	int u_resolution = glGetUniformLocation(program, "u_resolution");
	int u_position = glGetUniformLocation(program, "u_position");
	int u_size = glGetUniformLocation(program, "u_size");
	int u_depth = glGetUniformLocation(program, "u_depth");
	int u_time = glGetUniformLocation(program, "u_time");
	int u_rotation = glGetUniformLocation(program, "u_rotation");
	int u_camera_position = glGetUniformLocation(program, "u_camera_position");
	int u_camera_zoom = glGetUniformLocation(program, "u_camera_zoom");
	int u_texture_flip = glGetUniformLocation(program, "u_texture_flip");
	
	
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glUseProgram(program);
	
	//	setting all uniforms
	glUniform2f(u_resolution, (float)Game::width, (float)Game::height);
	glUniform2f(u_position, parent->position.x, parent->position.y);
	glUniform2f(u_size, parent->size.x, parent->size.y);
	glUniform1f(u_depth, parent->depth);
	glUniform1f(u_rotation, parent->rotation);
	glUniform1i(u_time, (int)parent->GetParentScene()->GetActiveTime());
	glUniform2f(u_camera_position, parent->GetParentScene()->Camera->position.x, parent->GetParentScene()->Camera->position.y);
	glUniform1f(u_camera_zoom, parent->GetParentScene()->CameraZoom);
	glUniform2f(u_texture_flip, (float)xFlipped, (float)yFlipped);
	
	
	//	all the opengl binding and actually rendering the points
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
}

void BigNgine::TextureRendererBehaviour::Destroy()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteTextures(1, &texture);
	glDeleteProgram(program);
}

[[maybe_unused]]void BigNgine::TextureRendererBehaviour::SetVertShader(std::string vertexShader)
{
	vertShader = std::move(vertexShader);
}

[[maybe_unused]]void BigNgine::TextureRendererBehaviour::SetFragShader(std::string fragmentShader)
{
	fragShader = std::move(fragmentShader);
}

void BigNgine::TextureRendererBehaviour::SetTexture(const std::string &_file)
{
	TextureRendererBehaviour::file = _file;
}
