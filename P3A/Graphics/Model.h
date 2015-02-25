#pragma once

#include <string>

#include "Engine\Graphics\Model_Base.h"

namespace P3A
{
	namespace Graphics
	{
		class GraphicsContext;

		class Model :
			public Engine::Graphics::Model_Base
		{
		public:
			inline Model(void) = delete;
			inline Model(std::string const& _path, std::string const& _name, Vector2 const& _location) : Engine::Graphics::Model_Base(_path, _name, _location) { }
			inline Model(Model const& _other) = delete;
			inline Model & operator=(Model const& _other) = delete;
			inline virtual ~Model(void) = default;

			void Render(GraphicsContext & _context);

		private:
			void Render_Element(GraphicsContext & _context, Engine::Graphics::Element_Base * _element, Vector2 const& _location, real32 const& _rotation);
		};
	}
}