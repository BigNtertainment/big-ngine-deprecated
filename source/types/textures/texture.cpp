#include "texture.h"


// Impement texture class

BigNgine::Texture::Texture(const char* path)
{
	//	generating texture buffers
	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);

	//	setting wrapping method
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	//	setting rasterisation method
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load image, create texture and generate mipmaps
	unsigned char *data = stbi_load(path, &_width, &_height, nullptr, 4);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		Logger::Error("Could not load texture at: " + std::string(path));
	stbi_image_free(data);

	//	unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

BigNgine::Texture::~Texture()
{
	glDeleteTextures(1, &_id);
}

void BigNgine::Texture::Bind(unsigned int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, _id);
}

void BigNgine::Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

int BigNgine::Texture::getWidth() const
{
	return _width;
}

int BigNgine::Texture::getHeight() const
{
	return _height;
}

unsigned int BigNgine::Texture::getID() const
{
	return _id;
}
