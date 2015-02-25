#pragma once

#include <vector>

#include "Engine\Types.h"
#include "Engine\Graphics\Context_Base.h"

namespace Engine
{
	namespace Graphics
	{
		template < class Index >
		class KeyHandler
		{
		public:
			struct KeyBinding
			{
			public:
				const Index index;
				const uint32 key;

				uint8 state = false;

				inline KeyBinding(void) = delete;
				inline KeyBinding(Index const& _index, uint32 const& _key) : index(_index), key(_key) { }
				inline KeyBinding(KeyBinding const& _other) = delete;
				inline KeyBinding(KeyBinding && _other) : index(_other.index), key(_other.key), state(_other.state) { }
				inline KeyBinding & operator=(KeyBinding const& _other) = delete;
				inline ~KeyBinding(void) = default;
			};

		public:
			inline KeyHandler(void) = default;
			KeyHandler(std::vector< KeyBinding > const& _state) : state(_state) { }
			inline KeyHandler(KeyHandler const& _other) = delete;
			inline KeyHandler & operator=(KeyHandler const& _other) = delete;
			inline ~KeyHandler() = default;

			void Process(Engine::Graphics::Context_Base const& _context)
			{
				for (KeyBinding & binding : state)
				{
					binding.state = (glfwGetKey(_context.window, GLFW_KEY_W) == GLFW_PRESS) ? 1 : 0;
				}
			}

			std::vector< KeyBinding > state;
		};
	}
}