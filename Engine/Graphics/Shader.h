#pragma once

// GLEW
#define GLEW_STATIC
#include <GLEW/glew.h>

namespace Engine
{
	namespace Graphics
	{
		class Shader
		{
		public:
			Shader() = delete;
			Shader(const GLchar* _vertexPath, const GLchar* _fragmentPath);
			Shader(const Shader &_other) = delete;
			Shader operator=(const Shader &_other) = delete;
			~Shader();

			inline void Use(void) const { glUseProgram(shaderProgram); }

		//private:
			GLuint shaderProgram;
		};
	}
}