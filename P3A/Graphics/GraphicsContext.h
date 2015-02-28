#pragma once

#include <string>

#include "Engine\Types.h"
#include "Engine\Graphics\Shader.h"
#include "Engine\Graphics\Texture_Base.h"
#include "Engine\Graphics\Context_Base.h"

namespace P3A
{
	namespace Graphics
	{
		class GraphicsContext :
			public Engine::Graphics::Context_Base
		{
		public:
			inline GraphicsContext(void) = delete;
			GraphicsContext(uint32 const& _window_width, uint32 const& _window_height, real32 _camera_min_distance = 0.01f, real32 _camera_max_distance = 64.f);
			inline GraphicsContext(GraphicsContext && _other) = delete;
			inline GraphicsContext(GraphicsContext const& _other) = delete;
			inline GraphicsContext & operator=(GraphicsContext && _other) = delete;
			inline GraphicsContext & operator=(GraphicsContext const& _other) = delete;
			~GraphicsContext(void);

			enum class StringAlignment
			{
				LEFT = 0,
				MIDDLE,
				RIGHT,

				Count
			};

			void DrawString(Engine::Graphics::Texture_Base const* _font_texture, std::string const& _text, float const& _x, float const& _y, glm::vec4 const& _color, StringAlignment const& _alignment);
			void DrawBox(Engine::Graphics::Texture_Base const* _texture, Vector2 const& _center, real32 const& _rotation);

		//private:
			// TODO Why are these dynamically allocated?!
			Engine::Graphics::Shader * shader_box;
			Engine::Graphics::Shader * shader_text;

			Engine::Graphics::Texture_Base * font_arial_black;
		};
	}
}