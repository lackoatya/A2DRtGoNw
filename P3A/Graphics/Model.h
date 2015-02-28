#pragma once

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
			GraphicsContext & context;

			// Constructor
			inline Model(void) = delete;
			inline Model(Engine::Graphics::Mesh * _mesh, Engine::Graphics::Appearance * _appearance, GraphicsContext & _context) : Model_Base(_mesh, _appearance), context(_context) { }
			// Copy Constructor
			inline Model(Model && _other) = delete;
			inline Model(Model const& _other) = delete;
			// Assignment operator
			inline Model & operator=(Model && _other) = delete;
			inline Model & operator=(Model const& _other) = delete;
			// Destructor
			inline virtual ~Model(void) = default;

			void Render(void);
		};
	}
}