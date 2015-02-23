#pragma once

#include <vector>

#include "Engine\Types.h"
#include "Engine\Core\Processable.h"
#include "Engine\Graphics\KeyHandler.hpp"

#include "P3A\Core\State.h"
#include "P3A\Graphics\GraphicsContext.h"

namespace P3A
{
	namespace Graphics
	{
		class Menu :
			public Engine::Core::Processable< P3A::Core::State >
		{
		public:
			inline Menu(void) = delete;
			Menu(P3A::Graphics::GraphicsContext & _context);
			inline Menu(Menu const& _other) = delete;
			inline Menu & operator=(Menu const& _other) = delete;
			inline ~Menu(void) = default;

			void Render(void);
			P3A::Core::State Process();

			void Handle_Keys(void);
			void Handle_Mouse(void);

			enum class Keys
			{
				UP = 0,
				DOWN,
				ESCAPE,

				Count
			};

			Engine::Graphics::KeyHandler< Keys > bindings; //(std::array < Keys, (uint32)Keys::Count > { KeyHandler< Keys, (uint32)Keys::Count >(Keys::UP, GLFW_KEY_W)});

		private:
			uint32 current = 0;

			bool keys[(uint32)Keys::Count];

			P3A::Graphics::GraphicsContext & context;
		};
	}
}