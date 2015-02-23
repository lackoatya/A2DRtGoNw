#pragma once

#include <string>

#include "Engine\Types.h"
#include "Engine\Graphics\Shader.h"
#include "Engine\Graphics\Texture.h"
#include "Engine\Graphics\WindowContext.h"

namespace P3A
{
	namespace Graphics
	{
		class GraphicsContext :
			public Engine::Graphics::WindowContext
		{
		public:
			inline GraphicsContext(void) = delete;
			GraphicsContext(uint32 const& _window_width, uint32 const& _window_height, real32 _camera_min_distance = 0.01f, real32 _camera_max_distance = 64.f);
			inline GraphicsContext(GraphicsContext const& _other) = delete;
			inline GraphicsContext & operator=(GraphicsContext const& _other) = delete;
			~GraphicsContext(void);

			enum class StringAlignment
			{
				LEFT = 0,
				MIDDLE,
				RIGHT,

				Count
			};

			void DrawString(Engine::Graphics::Texture const* _font_texture, std::string const& _text, float const& _x, float const& _y, StringAlignment const& _alignment);

		//private:
			// TODO Why are these dynamically allocated?!
			Engine::Graphics::Shader *shader_text;
			Engine::Graphics::Shader *shader_wall;
			Engine::Graphics::Shader *shader_hero;

			Engine::Graphics::Texture *font_arial_black;
		};
	}
}