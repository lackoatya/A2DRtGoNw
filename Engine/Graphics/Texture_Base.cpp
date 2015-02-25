#include <assert.h>

#include "SOIL\SOIL.h"

#include "Engine\Graphics\Texture_Base.h"

Engine::Graphics::Texture_Base::Texture_Base(const GLchar* _path)
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* image = SOIL_load_image(_path, &width, &height, 0, SOIL_LOAD_RGBA);
	assert(image && "SOIL File loading error: " && _path);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Engine::Graphics::Texture_Base::~Texture_Base()
{
	glDeleteTextures(1, &ID);
}