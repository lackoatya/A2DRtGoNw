#pragma once

#include "Engine\Types.h"
#include "Engine\Core\Processable.h"
#include "Engine\Graphics\Mesh.h"
#include "Engine\Graphics\Appearance.h"

#include "P3A\Core\State.h"
#include "P3A\Graphics\Model.h"
#include "P3A\Graphics\GraphicsContext.h"

namespace P3A
{
	namespace Graphics
	{
		class Test :
			public Engine::Core::Processable< P3A::Core::State >
		{
		public:
			Engine::Graphics::Mesh ** meshes = nullptr;
			Engine::Graphics::Appearance ** appearances = nullptr;

			inline Test(void) = delete;
			Test(P3A::Graphics::GraphicsContext & _context);
			inline Test(Test const& _other) = delete;
			inline Test & operator=(Test const& _other) = delete;
			inline ~Test(void) = default;

			P3A::Core::State Process(real32 const& _elapsed_time);

			void Update(real32 const& _elapsed_time);
			void Render();

			void Handle_Keys(void);
			void Handle_Mouse(void);

		private:
			P3A::Graphics::Model * model = nullptr;
			P3A::Graphics::GraphicsContext & context;
		};
	}
}