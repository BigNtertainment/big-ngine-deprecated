#include "renderer.h"


void BigNgine::TextRendererBehaviour::Start()
{
//	FreeType init
	if (FT_Init_FreeType(&ft))
	{
		Logger::Error("Could not initialize FreeType Library");
		return;
	}

//	loading font
	if (FT_New_Face(ft, font.c_str(), 0, &face))
	{
		Logger::Error("Could not load font at: " + font);
		return;
	}

//	setting font size
//	putting 0 sets width to automatic
	FT_Set_Pixel_Sizes(face, 0, font_size);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
	
	
	for (unsigned char i = 0; i < 128; ++i)
	{
//		loading character
		if (FT_Load_Char(face, i, FT_LOAD_RENDER))
		{
			Logger::Error("Failed to load Glyph");
			return;
		}
//		generating texture
		unsigned int t_texture;
		glGenTextures(1, &t_texture);
		glBindTexture(GL_TEXTURE_2D, t_texture);
		glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
		);
//		setting texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


//		storing character
		Character character = {
				t_texture,
				BigNgine::Vector2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				BigNgine::Vector2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
		};
		Characters.insert(std::pair<char, Character>(i, character));
	}




//	freeing FreeTypes resources
	FT_Done_Face(face);
	FT_Done_FreeType(ft);


//======================================================================================================================
	
	
	//	setting up all the relations between points in one entity-square
	float vertices[] = {
//			positions						texture coords
			// top right
			1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f,    // bottom right
			0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f    // top left
	};
	
	//	setting up how the points form triangles
	unsigned int indices_square[] = {
			2, 3, 0,  // first triangle
			2, 0, 1    // second triangle
	};
	
	
	//	loading shaders into char*
	const char *vertex_shader_source = vertShader.c_str();
	const char *fragment_shader_source = fragShader.c_str();
	
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
	if (!success)
	{
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) nullptr);
	glEnableVertexAttribArray(0);
//	texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);
	
	
}

void BigNgine::TextRendererBehaviour::Update(int deltaTime)
{
	auto *game = BigNgine::Game::GetInstance();
	
	int u_resolution = glGetUniformLocation(program, "u_resolution");
	int u_position = glGetUniformLocation(program, "u_position");
	int u_size = glGetUniformLocation(program, "u_size");
	int u_depth = glGetUniformLocation(program, "u_depth");
	int u_rotation = glGetUniformLocation(program, "u_rotation");
	int u_camera_position = glGetUniformLocation(program, "u_camera_position");
	int u_camera_zoom = glGetUniformLocation(program, "u_camera_zoom");
	int u_color = glGetUniformLocation(program, "u_color");
	
	glUseProgram(program);
	
	//	setting all uniforms
	glUniform2f(u_resolution, (float) game->GetWindowWidth(), (float) game->GetWindowHeight());
	
	glUniform1f(u_depth, parent->depth);
	glUniform1f(u_rotation, parent->rotation);
	glUniform2f(u_camera_position, parent->GetParentScene()->Camera->position.x,
				parent->GetParentScene()->Camera->position.y);
	glUniform1f(u_camera_zoom, parent->GetParentScene()->CameraZoom);
	glUniform3f(u_color,text_color.x , text_color.y, text_color.z);
	
	
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);
	
	
	float x = parent->position.x, y = parent->position.y + font_size + margin_top;
//	 iterate through all characters
	for (c = text.begin(); c != text.end(); c++)
	{
		if (*c == '\n')
		{
			y += font_size + margin_top + margin_bottom;
			x = parent->position.x;
			continue;
		}
		Character ch = Characters[*c];
		
		float xPos = x + ch.Bearing.x;
		float yPos = y - ch.Bearing.y;
		
		glUniform2f(u_position, xPos, yPos);
		glUniform2f(u_size, ch.Size.x, ch.Size.y);
		
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		
		
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += ch.Advance >> 6; // bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}


void BigNgine::TextRendererBehaviour::Destroy()
{
	Character ch;
	for (unsigned char i = 0; i < 128; ++i)
	{
		ch = Characters[i];
		glDeleteTextures(1, &ch.TextureID);
	}
	Characters.clear();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(program);
}

void BigNgine::TextRendererBehaviour::setText(const std::string &_text)
{
	TextRendererBehaviour::text = _text;
}

void BigNgine::TextRendererBehaviour::setFontSize(short fontSize)
{
	font_size = fontSize;
}

void BigNgine::TextRendererBehaviour::setMarginTop(short marginTop)
{
	margin_top = marginTop;
}

void BigNgine::TextRendererBehaviour::setMarginBottom(short marginBottom)
{
	margin_bottom = marginBottom;
}

void BigNgine::TextRendererBehaviour::setFont(const std::string &font)
{
	TextRendererBehaviour::font = font;
}

void BigNgine::TextRendererBehaviour::setColor(Vector3 color)
{
	text_color = color;
}

