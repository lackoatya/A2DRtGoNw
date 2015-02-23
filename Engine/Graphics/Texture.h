#pragma once

// GLEW
#define GLEW_STATIC
#include "GLEW/glew.h"

namespace Engine
{
	namespace Graphics
	{
		class Texture
		{
		public:
			Texture() = delete;
			Texture(const GLchar* _texturePath);
			Texture(Texture const& _other) = delete;
			Texture & operator=(Texture const& _other) = delete;
			~Texture();

			//inline GLuint ID(void) const { return textureID; }

		//private:
			GLuint textureID;
			int width;
			int height;
		};
	}
}