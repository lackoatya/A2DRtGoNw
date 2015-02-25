#pragma once

// GLEW
#define GLEW_STATIC
#include "GLEW\glew.h"

#include "Engine\Types.h"

namespace Engine
{
	namespace Graphics
	{
		class Texture_Base
		{
		public:
			Texture_Base() = delete;
			Texture_Base(const GLchar* _path);
			Texture_Base(Texture_Base const& _other) = delete;
			Texture_Base & operator=(Texture_Base const& _other) = delete;
			~Texture_Base();

			//inline GLuint ID(void) const { return Texture_BaseID; }

			void Render(Vector2 const& _center, real32 const& _rotation);

		//private:
			GLuint ID;
			int width;
			int height;
		};
	}
}