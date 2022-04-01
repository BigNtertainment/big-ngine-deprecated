#include "renderer.h"

static BigNgine::Game* game = BigNgine::Game::GetInstance();

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
	
	
	if (texturePaths.empty())
	{
		Logger::Error("didn't get any textures to load");
		texture = new Texture("");
		return;
	}
	texture = new Texture(texturePaths[0]);

}

void BigNgine::TextureRendererBehaviour::Update(int deltaTime)
{
	// TODO(imustend): make uniform a object, so user can add how many they want
	//					vector of uniforms

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
	
	texture->Bind();
	
	
	glUseProgram(program);
	
	//	setting all uniforms
	glUniform2f(u_resolution, (float)game->GetWindowWidth(), (float)game->GetWindowHeight());
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

	// this technically can stay, but it should be called for used texture
	// however it won`t really make any difference
	texture->Unbind();
	
}

void BigNgine::TextureRendererBehaviour::Destroy()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(program);
	delete texture;
}

[[maybe_unused]]void BigNgine::TextureRendererBehaviour::SetVertShader(std::string vertexShader)
{
	vertShader = std::move(vertexShader);
}

[[maybe_unused]]void BigNgine::TextureRendererBehaviour::SetFragShader(std::string fragmentShader)
{
	fragShader = std::move(fragmentShader);
}

[[maybe_unused]]void BigNgine::TextureRendererBehaviour::SetTexture(Texture *_texture)
{
	texture = _texture;
}

void BigNgine::TextureRendererBehaviour::AddTexture(const char * _file)
{
	TextureRendererBehaviour::texturePaths.push_back(_file);
}
