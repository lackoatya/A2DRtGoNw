#include "Engine\Types.h"
#include "Engine\Core\NonDeterministic.hpp"

#include "P3A\Graphics\Menu.h"
#include "P3A\Graphics\GraphicsContext.h"

int main()
{
	P3A::Graphics::GraphicsContext graphics(1024, 768);

	P3A::Core::State state(P3A::Core::CoreState::MENU);

	do
	{
		switch (state.Value())
		{
		case P3A::Core::CoreState::MENU:
		{
			P3A::Graphics::Menu menu(graphics);
			state = Engine::Core::NonDeterministic < P3A::Graphics::Menu, P3A::Core::State >(menu, 1000 / 60);
		}
		break;


		}
	} while (state.Value() != P3A::Core::CoreState::EXIT);

	//Engine::Core::Interpolated< Engine::Physics::Reality, Engine::
	/*do
	{
	Engine::Core::NonDeterministic<  Game::Graphics::Menu >();

	switch ()
	{
	Engine::Core::Deterministic< Engine::Physics::Reality >(1.0f / 60.0f);
	}
	} while ();*/
	return 0;
}